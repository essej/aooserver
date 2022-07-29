/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include "JuceHeader.h"

#include "aoo/aoo_net.h"
#include "aoo/aoo_server.hpp"
#include "common/net_utils.hpp"
#include "common/udp_server.hpp"
#include "common/tcp_server.hpp"
#include "common/sync.hpp"

#include <unistd.h>

#include <iostream>
#include <signal.h>

using namespace std;

class AooConsoleServer;

class AooUdpServerThread : public juce::Thread
{
public:
    AooUdpServerThread(AooConsoleServer * server) : Thread("AooUdpServerThread") , mServer(server)
    {}
    
    void run() override;
    
    AooConsoleServer * mServer;
    volatile bool pendingStop = false;
};

class AooTcpServerThread : public juce::Thread
{
public:
    AooTcpServerThread(AooConsoleServer * server) : Thread("AooTcpServerThread") , mServer(server)
    {}
    
    void run() override;
    
    AooConsoleServer * mServer;
    volatile bool pendingStop = false;
};

class AooEventThread : public juce::Thread
{
public:
    AooEventThread(AooConsoleServer * server) : Thread("AooEventThread") , mServer(server)
    {}
    
    void run() override;
    
protected:
    
    AooConsoleServer * mServer;
};


class AooConsoleServer
{
public:
    AooConsoleServer(int port=10998) : mPort(port) {
        
    }
    
    int getPort() const { return mPort; }
    void setPort(int port) {
        mPort = port;
    }

    bool getAllowRelay() const { return mAllowRelay; }
    void setAllowRelay(bool allow) {
        mAllowRelay = allow;
        
        if (mServer) {
            mServer->setServerRelay(mAllowRelay);
        }
    }

    
    void setLoggingEnabled(bool flag, const String & logdir = "") {
        mLoggingEnabled = flag;
        mUseLogDir = logdir;
        updateLogging();
    }
    
    
    bool startServer() 
    {
        stopServer();

        const ScopedLock sl (mLock); 

        int32_t err = 0;

        // setup UDP server
        udpserver_.start(mPort,
                         [this](auto&&... args) { handleUdpReceive(args...); });
        
        // setup TCP server
        tcpserver_.start(mPort,
                         [this](auto&&... args) { return handleAccept(args...); },
                         [this](auto&&... args) { return handleReceive(args...); });

        
        mServer = AooServer::create(0, &err);

        if (!mServer || err != 0) {
            String errstr;
            errstr << "ServerStartError," << err;
            logEvent(errstr);
            mServer.reset();
            return false;
        }
        
        mServer->setServerRelay(mAllowRelay);
        
        mServer->setEventHandler(
            [](void *user, const AooEvent *event, int32_t level) {
                static_cast<AooConsoleServer*>(user)->handleServerEvent(event, level);
            }, this, kAooEventModeCallback);
        
            
        String msg; msg << "ServerStart," << mPort;
        if (mAllowRelay)
            msg << ",AllowRelay";
        logEvent(msg);

        startTimeMs = Time::getMillisecondCounterHiRes();
        
        if (mServer) {
            mUdpServerThread = std::make_unique<AooUdpServerThread>(this);
            mUdpServerThread->startThread();

            mTcpServerThread = std::make_unique<AooTcpServerThread>(this);
            mTcpServerThread->startThread();

            //mEventThread = std::make_unique<AooEventThread>(*this);    
            //mEventThread->startThread();
            
            //DebugLogC("Started server, ready to go.");
            
            return true;
        }
        return false;
    }
    
    void stopServer() {

        
        //mEventThread->stopThread(400);
        
        const ScopedLock sl (mLock); 

        
        if (mServer) {
            DBG("waiting on server thread to die");
            //mServer->quit();

            mUdpServerThread->pendingStop = mTcpServerThread->pendingStop = true;

            udpserver_.stop();
            tcpserver_.stop();

            Thread::sleep(800);
            //DBG("stopping thread");
            mUdpServerThread->stopThread(400);
            mTcpServerThread->stopThread(400);

            //DBG("thread stopped");
            Thread::sleep(200);
            mServer.reset();
            
            String msg; msg << "ServerStop";
            logEvent(msg);

            double runTime = (Time::getMillisecondCounterHiRes() - startTimeMs) * 1e-3;
            runTime = runTime < 0.1 ? 0.1 : runTime;
            int hours = (int) (runTime/3600.0);
            int minutes = (int) (runTime/60.0) % 60;
            float secs =  fmodf(runTime, 60.0);

            msg.clear();
            msg << String::formatted("runtime duration: %02d:%02d:%02d", hours, minutes, (int)secs) << "\n";
            msg << "total traffic: " << totIncomingBytes.load() / 1048576.f << " MB in, " << totOutgoingBytes.load() / 1048576.f << " MB out" << "\n";
            msg << "average bandwidth: " << totIncomingBytes.load() / runTime << " BPS in, " << totOutgoingBytes.load() / runTime << " BPS out" << "\n";
            msg << "peak bandwidth: " << peakIncomingRate  << " BPS in, " << peakOutgoingRate  << " BPS out" << "\n";

            if (mLogger) {
                mLogger->logMessage(msg);
            }
            else {
                cerr << msg << endl;
            }
        }
    }
    
    void runUdpServer()
    {
        udpserver_.run(-1);
    }

    void runTcpServer()
    {
        tcpserver_.run();
    }

    
    virtual ~AooConsoleServer() {
        //DBG("Destructor");

        stopServer();
    }
    
    void logEvent(const String & evstr) {
        
        // log format is
        // timestamp,currgroups,currusers,evstr
        
        String timestamp = Time::getCurrentTime().formatted ("%Y-%m-%d %H:%M:%S");
        String message;
        message << timestamp << ",";
        if (mServer) {
            message << mGroups.size() << ","
                    << mUsers.size() << ",";
        }
        else {
            message << "0,0,"; 
        }
        
        message << evstr;

        if (mLogger) {                
            mLogger->logMessage(message);
        }
        else {
            cerr << message << endl;
        }
    }
    
    
    
    void handleEvents() {
        const ScopedLock sl (mLock); 
        if (mServer) {
            mServer->pollEvents();

            possiblyCheckDataRate();
        }
    }

    void possiblyCheckDataRate() {
        // data rate logging
        const double nowtime = Time::getMillisecondCounterHiRes() * 1e-3;
        if (nowtime > lastCheckTimestamp + dataRateLogInterval) {
            auto incoming = totIncomingBytes.load(); //  mServer->getIncomingUdpBytes();
            auto outgoing = totOutgoingBytes.load(); // mServer->getOutgoingUdpBytes();

            double deltatime = nowtime - lastCheckTimestamp;
            auto inrate = (incoming - lastIncomingBytes) / deltatime;
            auto outrate = (outgoing - lastOutgoingBytes) / deltatime;

            bool iszero = inrate == 0.0 && outrate == 0.0;

            if (!iszero || !lastRateZero) {
                String msg; msg << "UDPDataRate_In_Out," << inrate << "," << outrate;
                logEvent(msg);

                peakOutgoingRate = outrate > peakOutgoingRate ? outrate : peakOutgoingRate;
                peakIncomingRate = inrate > peakIncomingRate ? inrate : peakIncomingRate;
            }

            lastCheckTimestamp = nowtime;
            
            lastOutgoingBytes = outgoing;
            lastIncomingBytes = incoming;
            
            lastRateZero = iszero;
        }
    }

    AooId handleAccept(int e, const aoo::ip_address& addr, AooSocket sock)
    {
        if (e == 0) {
            // reply function
            auto replyfn = [](void *x, AooId client,
                              const AooByte *data, AooSize size) -> AooInt32 {
                return static_cast<aoo::tcp_server *>(x)->send(client, data, size);
            };
            AooId client;
            mServer->addClient(replyfn, &tcpserver_, sock, &client); // doesn't fail

            String msg;
            msg << "ClientAccept," << addr.name_unmapped();
            logEvent(msg);

            return client;
        } else {
            String msg;
            msg << "Error,Accept failed," << aoo::socket_strerror(e);
            logEvent(msg);
            // TODO handle error?
            return kAooIdInvalid;
        }
    }
    

    void handleReceive(AooId client, int e, const AooByte *data, AooSize size)
    {
        if (e == 0 && size > 0) {
            if (mServer->handleClientMessage(client, data, (AooInt32)size) != kAooOk) {
                mServer->removeClient(client);
                tcpserver_.close(client);
            }
        } else {
            // remove client!
            mServer->removeClient(client);
            if (e == 0) {
                DBG("AooServer: client " << client << " disconnected");
            } else {
                DBG("AooServer: TCP error in client "
                          << client << ": " << aoo::socket_strerror(e));
            }
        }
    }
    

    void handleUdpReceive(int e, const aoo::ip_address& addr,
                          const AooByte *data, AooSize size)
    {
        if (e == 0) {
            // reply function
            auto replyfn = [](void *x, const AooByte *data, AooInt32 size,
                              const void *address, AooAddrSize addrlen, AooFlag) -> AooInt32 {
                aoo::ip_address addr((const struct sockaddr *)address, addrlen);
                auto serv = static_cast<AooConsoleServer *>(x);
                serv->totOutgoingBytes = serv->totOutgoingBytes.load() + size;
                return serv->udpserver_.send(addr, data, size);
            };
            mServer->handleUdpMessage(data, (AooInt32)size, addr.address(), addr.length(),
                                      replyfn, this);
            
            totIncomingBytes = totIncomingBytes.load() + size;
        } else {
            DBG("AooServer: UDP error: " << aoo::socket_strerror(e));
            // TODO handle error?
        }
    }
    
    int32_t handleServerEvent(const AooEvent *event, int32_t level)
    {
        switch (event->type){
            case kAooNetEventServerClientLogin:
            {
                auto *e = (const AooNetEventServerClientLogin *)event;

                String msg;
                msg << "ClientLogin," << e->id;
                logEvent(msg);
                
                mClients[e->id] = ClientInfo(e->id, e->sockfd);
                
                break;
            }
            case kAooNetEventServerClientRemove:
            {
                auto *e = (const AooNetEventServerClientRemove *)event;

                String msg;
                msg << "ClientRemove," << e->id;
                logEvent(msg);
                
                mClients.erase(e->id);

                break;
            }
            case kAooNetEventServerGroupAdd:
            {
                auto e = (const AooNetEventServerGroupAdd *)event;

                mGroups[e->id] = GroupInfo(e->id, e->name);

                break;
            }
            case kAooNetEventServerGroupRemove:
            {
                auto e = (const AooNetEventServerGroupRemove *)event;

                mGroups.erase(e->id);

                break;
            }
            case kAooNetEventServerGroupJoin:
            {
                auto *e = (const AooNetEventServerGroupJoin *)event;
                
                String msg;
                msg << "UserGroupJoin," << e->groupName << "," << e->userName;
                logEvent(msg);

                mUsers[{e->groupId, e->userId}] = UserInfo(e->groupId, e->userId, e->userName, e->clientId);

                break;
            }
            case kAooNetEventServerGroupLeave:
            {
                auto *e = (const AooNetEventServerGroupLeave *)event;

                String msg;
                msg << "UserGroupLeave," << e->groupName << "," << e->userName;
                logEvent(msg);
                
                mUsers.erase({e->groupId, e->userId});
                
                break;
            }
            case kAooNetEventError:
            {
                auto *e = (const AooNetEventError *)event;
                
                String msg;
                msg << "Error," << e->errorMessage;
                logEvent(msg);
                
                break;
            }
            default:
                String msg;
                msg << "Unknown," << event->type;
                logEvent(msg);
                break;
        }

        return kAooOk;
    }
    
    
    
protected:
    
    void updateLogging() {
        
        if (!mLoggingEnabled && mLogger) {
            const ScopedLock sl (mLock); 
            // stop logger
            mLogger.reset();
        }
        else if (mLoggingEnabled && !mLogger) {
            // create logfile
            const ScopedLock sl (mLock); 
            String message("SonoBus AOO Server");
            
            if (mUseLogDir.isEmpty()) {
                mLogger.reset(FileLogger::createDateStampedLogger("aooserver", "aooserver_log_", ".txt", message));
            }
            else {
                File logdir(File::getCurrentWorkingDirectory().getChildFile(mUseLogDir));
                mLogger.reset(new FileLogger (logdir.getChildFile ("aooserver_log_" + Time::getCurrentTime().formatted ("%Y-%m-%d_%H-%M-%S"))
                                              .withFileExtension (".txt")
                                              .getNonexistentSibling(),
                                              message, 0));                
            }
            
            DBG("Created logfile: " << mLogger->getLogFile().getFullPathName());
        }
        
    }

    
    int mPort = 10998;
    
    bool mLoggingEnabled = false;
    bool mAllowRelay = false;
    String mUseLogDir;
    
    CriticalSection mLock;
    
    std::unique_ptr<AooUdpServerThread> mUdpServerThread;
    std::unique_ptr<AooTcpServerThread> mTcpServerThread;
    //std::unique_ptr<AooEventThread> mEventThread;
    
    std::unique_ptr<FileLogger> mLogger;
    
    AooServer::Ptr mServer;

    aoo::udp_server udpserver_;
    aoo::tcp_server tcpserver_;
    
    struct GroupInfo {
        GroupInfo(AooId gid_=kAooIdInvalid, const std::string & name_="") : gid(gid_), name(name_) {}
        AooId gid;
        std::string name;
    };

    struct UserInfo {
        UserInfo(AooId gid_=kAooIdInvalid, AooId uid_=kAooIdInvalid, const std::string & name_="", AooId cid_=kAooIdInvalid) : gid(gid_), uid(uid_), name(name_), cid(cid_) {}
        AooId gid;
        AooId uid;
        std::string name;
        AooId cid;
    };

    struct ClientInfo {
        ClientInfo(AooId id_=kAooIdInvalid, AooSocket sock_=-1) : cid(id_), sockfd(sock_) {}
        AooId cid;
        AooSocket sockfd;
    };

    
    // key is groupid
    std::map<AooId,GroupInfo> mGroups;

    // key is gid/uid
    std::map<std::pair<AooId,AooId>, UserInfo> mUsers;

    // key is client id
    std::map<AooId,ClientInfo> mClients;

    aoo::sync::relaxed_atomic<uint64_t> totIncomingBytes = { 0 };
    aoo::sync::relaxed_atomic<uint64_t> totOutgoingBytes = { 0 };
    //std::atomic<uint64_t> totIncomingBytes = { 0 };
    //std::atomic<uint64_t> totOutgoingBytes = { 0 };
    
    uint64_t peakIncomingRate = 0;
    uint64_t peakOutgoingRate = 0;

    uint64_t lastIncomingBytes = 0;
    uint64_t lastOutgoingBytes = 0;
    double   lastCheckTimestamp = 0.0;
    const double dataRateLogInterval = 10.0;
    bool lastRateZero = false;
    double startTimeMs = 0.0;

};



void AooUdpServerThread::run()  {

    double startTimeMs = Time::getMillisecondCounterHiRes();

    while (!threadShouldExit() && !pendingStop) {
     
        mServer->runUdpServer();
        
    }
   
    DBG("UDP Server thread finishing");
}

void AooTcpServerThread::run()  {

    double startTimeMs = Time::getMillisecondCounterHiRes();

    while (!threadShouldExit() && !pendingStop) {
     
        mServer->runTcpServer();
        
    }
   
    DBG("TCP Server thread finishing");
}


static bool keyboardBreakOccurred = false;

//==============================================================================
static void keyboardBreakSignalHandler (int sig)
{
    if (sig == SIGINT) {
        keyboardBreakOccurred = true;
        DBG("KEYBOARD BREAK!");
    }
}

static void installKeyboardBreakHandler()
{
    struct sigaction saction;
    sigset_t maskSet;
    sigemptyset (&maskSet);
    saction.sa_handler = keyboardBreakSignalHandler;
    saction.sa_mask = maskSet;
    saction.sa_flags = 0;
    sigaction (SIGINT, &saction, 0);
}

#if 1
class AooServerApplication : public JUCEApplicationBase, public juce::Timer
{
public:
    const String getApplicationName() override    { return ProjectInfo::projectName; }
    const String getApplicationVersion() override { return ProjectInfo::versionString; }
    
    void initialise (const String& /*commandLineParameters*/) override
    {
        // Start your app here
        installKeyboardBreakHandler();
        
        
        ConsoleApplication app;
        app.addHelpCommand ("-h|--help", "Usage:", false);
        //app.addVersionCommand ("--version|-v", "aooserver version 1.2.3");
        
        auto params = getCommandLineParameterArray();
        ArgumentList arglist(getApplicationName(), params);
        
        app.addCommand ({ "-l|--logdir",
            "-l|--logdir logdirectory",
            "Enables logging to file",
            "Enables logging to file in the specified directory",
            [this] (const auto& args) { 
                //String logdir = args.getValueForOption("-l");
                //this->server.setLoggingEnabled(true, logdir);
                //DBG("Set logging to: " << logdir);
            }
        });

        app.addCommand ({ "-p|--port",
            "-p|--port <server_port> ",
            "Specify the server port (default 10998)",
            "Specify the server port (UDP and TCP) (default 10998)",
            [this] (const auto& args) { 
                //int port = args.getValueForOption("-p").getIntValue();
                //if (port > 0) {
                //    this->server.setPort(port);
                //    DBG("Set port to: " << port);
                //}
            }
        });

        app.addCommand ({ "-r|--relay",
            "-r|--relay",
            "Allow server to relay packets between clients",
            "Allow server to relay packets between clients when necessary when peer-to-peer can't be done",
            [this] (const auto& args) {}
        });

        

        auto logdir = arglist.removeValueForOption("-l|--logdir"); 
        if (logdir.isNotEmpty()) {        
            server.setLoggingEnabled(true, logdir);
        }

        auto portstr = arglist.removeValueForOption("-p|--port");   
        if (portstr.isNotEmpty()) {                
            int port = portstr.getIntValue();
            if (port > 0) {
                server.setPort(port);
            }
        }
        
        bool relay = arglist.containsOption("-r|--relay");
        server.setAllowRelay(relay);

        if (arglist.containsOption("-h|--help")) {
            app.printCommandList(arglist);
            quit();
        }
        else {
            
            //int ret = app.findAndRunCommand(arglist);
            //DBG("find command: " << ret);
            
            if (!server.startServer()) {
                quit();
            }
            
            startTimer(20);
        }
    }
    
    void shutdown() override {}

    void anotherInstanceStarted (const String& commandLine) override {
        
    }

    bool moreThanOneInstanceAllowed() override { return true; }

   
    void systemRequestedQuit() override {
        
    }

    void suspended() override {
        
    }

    void resumed() override {
        
    }
    
    void unhandledException (const std::exception*,
                                     const String& sourceFilename,
                                     int lineNumber) override {
        
    }
    
    void timerCallback() override
    {
        if (keyboardBreakOccurred) {
            quit();
        }
        server.handleEvents();
    }


    AooConsoleServer server;

};

START_JUCE_APPLICATION (AooServerApplication)

#else

//==============================================================================
int main (int argc, char* argv[])
{
    installKeyboardBreakHandler();

    AooServer server;
    
    if (server.startServer()) {
        
        cerr << "AOO Server started on port " <<  server.getPort() << endl;
    }
    else {
        exit(1);
    }

    
    while (!keyboardBreakOccurred) {
     
        usleep(20000);
        
        server.handleEvents();                       
    }
    
    return 0;
}
#endif
