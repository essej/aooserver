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

#include <unistd.h>

#include <iostream>
#include <signal.h>

using namespace std;

class AooConsoleServer;

class AooServerThread : public juce::Thread
{
public:
    AooServerThread(AooConsoleServer * server) : Thread("AooServerThread") , mServer(server)
    {}
    
    void run() override;
    
    AooConsoleServer * mServer;
    
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

        mServer = AooServer::create(mPort, 0, &err);

        if (!mServer || err != 0) {
            String errstr;
            errstr << "ServerStartError," << err;
            logEvent(errstr);
            mServer.reset();
            return false;
        }
        
        mServer->setEventHandler(
            [](void *user, const AooEvent *event, int32_t level) {
                static_cast<AooConsoleServer*>(user)->handleServerEvent(event, level);
            }, this, kAooEventModeCallback);
        
            
        String msg; msg << "ServerStart," << mPort;
        logEvent(msg);

        startTimeMs = Time::getMillisecondCounterHiRes();
        
        if (mServer) {
            mServerThread = std::make_unique<AooServerThread>(this);    
            mServerThread->startThread();

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
            mServer->quit();
            Thread::sleep(800);
            //DBG("stopping thread");
            mServerThread->stopThread(400);
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
            msg << "total traffic: " << totIncomingBytes / 1048576.f << " MB in, " << totOutgoingBytes / 1048576.f << " MB out" << "\n";
            msg << "average bandwidth: " << totIncomingBytes / runTime << " BPS in, " << totOutgoingBytes / runTime << " BPS out" << "\n";
            msg << "peak bandwidth: " << peakIncomingRate  << " BPS in, " << peakOutgoingRate  << " BPS out" << "\n";

            if (mLogger) {
                mLogger->logMessage(msg);
            }
            else {
                cerr << msg << endl;
            }
        }
    }
    
    void runServer()
    {
        if (mServer) {
            mServer->run(); // doesn't return until it is quit
        }
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
            message << mServer->getGroupCount() << ","
                    << mServer->getUserCount() << ",";
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
            auto incoming = mServer->getIncomingUdpBytes();
            auto outgoing = mServer->getOutgoingUdpBytes();

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

            totOutgoingBytes += outgoing;
            totIncomingBytes += incoming;

            lastCheckTimestamp = nowtime;
            
            lastOutgoingBytes = outgoing;
            lastIncomingBytes = incoming;
            
            lastRateZero = iszero;
        }
    }

    int32_t handleServerEvent(const AooEvent *event, int32_t level)
    {
        switch (event->type){
            case kAooNetEventUserJoin:
            {
                auto *e = (const AooNetEventUser *)event;

                String msg;
                msg << "UserJoin," << e->userName;
                logEvent(msg);
                
                break;
            }
            case kAooNetEventUserLeave:
            {
                auto *e = (const AooNetEventUser *)event;

                String msg;
                msg << "UserLeave," << e->userName;
                logEvent(msg);
                
                
                break;
            }
            case kAooNetEventUserGroupJoin:
            {
                auto *e = (const AooNetEventUserGroup *)event;
                
                String msg;
                msg << "GroupJoin," << e->groupName << "," << e->userName;
                logEvent(msg);
                
                break;
            }
            case kAooNetEventUserGroupLeave:
            {
                auto *e = (const AooNetEventUserGroup *)event;

                String msg;
                msg << "GroupLeave," << e->groupName << "," << e->userName;
                logEvent(msg);
                
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
    String mUseLogDir;
    
    CriticalSection mLock;
    
    std::unique_ptr<AooServerThread> mServerThread;
    //std::unique_ptr<AooEventThread> mEventThread;
    
    std::unique_ptr<FileLogger> mLogger;
    
    AooServer::Ptr mServer;

    uint64_t totIncomingBytes = 0;
    uint64_t totOutgoingBytes = 0;
    uint64_t peakIncomingRate = 0;
    uint64_t peakOutgoingRate = 0;

    uint64_t lastIncomingBytes = 0;
    uint64_t lastOutgoingBytes = 0;
    double   lastCheckTimestamp = 0.0;
    const double dataRateLogInterval = 10.0;
    bool lastRateZero = false;
    double startTimeMs = 0.0;

};



void AooServerThread::run()  {

    double startTimeMs = Time::getMillisecondCounterHiRes();

    while (!threadShouldExit()) {
     
        mServer->runServer();
        
    }
   
    DBG("Server thread finishing");
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
