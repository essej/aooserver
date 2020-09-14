/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

#include "aoo/aoo_net.hpp"
#include <unistd.h>

#include <iostream>
#include <signal.h>

using namespace std;

class AooServer;

class AooServerThread : public juce::Thread
{
public:
    AooServerThread(AooServer * server) : Thread("AooServerThread") , mServer(server) 
    {}
    
    void run() override;
    
    AooServer * mServer;
    
};

class AooEventThread : public juce::Thread
{
public:
    AooEventThread(AooServer * server) : Thread("AooEventThread") , mServer(server) 
    {}
    
    void run() override;
    
protected:
    
    AooServer * mServer;
};


class AooServer
{
public:
    AooServer(int port=10998) : mPort(port) {
        
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

        mServer.reset(aoo::net::iserver::create(mPort, &err));
        
        if (err != 0) {
            String errstr;
            errstr << "ServerStartError," << err;
            logEvent(errstr);
            return false;
        }
        
            
        String msg; msg << "ServerStart," << mPort;
        logEvent(msg);
        
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
        }
    }
    
    void runServer()
    {
        if (mServer) {
            mServer->run(); // doesn't return until it is quit
        }
    }
    
    virtual ~AooServer() {
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
            message << mServer->get_group_count() << "," 
                    << mServer->get_user_count() << ",";
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
    
    
    static int32_t gHandleServerEvents(void * user, const aoo_event ** events, int32_t n)
    {
        AooServer * pp = static_cast<AooServer*> (user);
        return pp->handleServerEvents(events, n);
    }
    
    void handleEvents() {
        const ScopedLock sl (mLock); 

        mServer->handle_events(gHandleServerEvents, this);
    }
    
    int32_t handleServerEvents(const aoo_event ** events, int32_t n)
    {
        for (int i = 0; i < n; ++i){
            switch (events[i]->type){
                case AOONET_SERVER_USER_JOIN_EVENT:
                {
                    aoonet_server_user_event *e = (aoonet_server_user_event *)events[i];

                    String msg;
                    msg << "UserJoin," << e->name;
                    logEvent(msg);
                    
                    break;
                }
                case AOONET_SERVER_USER_LEAVE_EVENT:
                {
                    aoonet_server_user_event *e = (aoonet_server_user_event *)events[i];

                    String msg;
                    msg << "UserLeave," << e->name;                    
                    logEvent(msg);
                    
                    
                    break;
                }
                case AOONET_SERVER_GROUP_JOIN_EVENT:
                {
                    aoonet_server_group_event *e = (aoonet_server_group_event *)events[i];
                    
                    String msg;
                    msg << "GroupJoin," << e->group << "," << e->user;
                    logEvent(msg);
                    
                    break;
                }
                case AOONET_SERVER_GROUP_LEAVE_EVENT:
                {
                    aoonet_server_group_event *e = (aoonet_server_group_event *)events[i];

                    String msg;
                    msg << "GroupLeave," << e->group << "," << e->user;
                    logEvent(msg);
                    
                    break;
                }
                case AOONET_SERVER_ERROR_EVENT:
                {
                    aoonet_server_event *e = (aoonet_server_event *)events[i];
                    
                    String msg;
                    msg << "Error," << e->errormsg;
                    logEvent(msg);
                    
                    break;
                }
                default:
                    String msg;
                    msg << "Unknown," << events[i]->type;
                    logEvent(msg);
                    break;
            }
        }
        return 1;
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
    
    aoo::net::iserver::pointer mServer;
};



void AooServerThread::run()  {

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
class AooServerApplication : public JUCEApplicationBase, public Timer
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
            
            server.startServer();
            
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


    
    
    AooServer server;

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
