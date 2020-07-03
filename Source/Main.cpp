/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

#include "aoo/aoo_net.hpp"
#include "DebugLogC.h"
#include <unistd.h>

#include <iostream>

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
    AooServer() {
        
    }
    
    bool startServer() 
    {
        stopServer();

        const ScopedLock sl (mLock); 

        int32_t err = 0;

        mServer.reset(aoo::net::iserver::create(10998, &err));
        
        if (err != 0) {
            DebugLogC("Error creating Aoo Server: %d ", err);
        }
        
        if (mServer) {
            mServerThread = std::make_unique<AooServerThread>(this);    
            mServerThread->startThread();

            //mEventThread = std::make_unique<AooEventThread>(*this);    
            //mEventThread->startThread();
            
            DebugLogC("Started server, ready to go.");
            
            return true;
        }
        return false;
    }
    
    void stopServer() {

        
        //mEventThread->stopThread(400);
        
        const ScopedLock sl (mLock); 

        
        if (mServer) {
           DebugLogC("waiting on server thread to die");
           mServer->quit();
           mServerThread->stopThread(400);    
           Thread::sleep(200);
           mServer.reset();
        }
    }
    
    void runServer()
    {
        if (mServer) {
            mServer->run(); // doesn't return until it is quit
        }
    }
    
    virtual ~AooServer() {
        DebugLogC("Destructor");

        stopServer();
    }
    
    static int32_t gHandleServerEvents(void * user, const aoo_event ** events, int32_t n)
    {
        AooServer * pp = static_cast<AooServer*> (user);
        return pp->handleServerEvents(events, n);
    }
    
    void handleEvents() {
        const ScopedLock sl (mLock); 

        if (mServer->events_available()) {
            mServer->handle_events(gHandleServerEvents, this);
        }        
    }
    
    int32_t handleServerEvents(const aoo_event ** events, int32_t n)
    {
        for (int i = 0; i < n; ++i){
            switch (events[i]->type){
                case AOONET_SERVER_USER_JOIN_EVENT:
                {
                    aoonet_server_user_event *e = (aoonet_server_user_event *)events[i];
                    
                    DebugLogC("User joined: %s", e->name);
                    
                    break;
                }
                case AOONET_SERVER_USER_LEAVE_EVENT:
                {
                    aoonet_server_user_event *e = (aoonet_server_user_event *)events[i];
                    
                    DebugLogC("User left: %s", e->name);
                    
                    
                    break;
                }
                case AOONET_SERVER_GROUP_JOIN_EVENT:
                {
                    aoonet_server_group_event *e = (aoonet_server_group_event *)events[i];
                    
                    DebugLogC("Group Joined: %s  by user: %s", e->group, e->user);
                    
                    break;
                }
                case AOONET_SERVER_GROUP_LEAVE_EVENT:
                {
                    aoonet_server_group_event *e = (aoonet_server_group_event *)events[i];
                    
                    DebugLogC("Group Left: %s  by user: %s", e->group, e->user);
                    
                    break;
                }
                case AOONET_SERVER_ERROR_EVENT:
                {
                    aoonet_server_event *e = (aoonet_server_event *)events[i];
                    
                    DebugLogC("Server error: %s", e->errormsg);
                    
                    break;
                }
                default:
                    DebugLogC("Got unknown server event: %d", events[i]->type);
                    break;
            }
        }
        return 1;
    }
    
protected:
    
    CriticalSection mLock;
    
    std::unique_ptr<AooServerThread> mServerThread;
    std::unique_ptr<AooEventThread> mEventThread;
    
    aoo::net::iserver::pointer mServer;
};



void AooServerThread::run()  {

    while (!threadShouldExit()) {
     
        mServer->runServer();
        
    }
    
    DebugLogC("Event thread finishing");
}


static bool keyboardBreakOccurred = false;

//==============================================================================
static void keyboardBreakSignalHandler (int sig)
{
    if (sig == SIGINT) {
        keyboardBreakOccurred = true;
        //DebugLogC("KEYBOARD BREAK!");
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

#if 0
class AooServerApplication : public JUCEApplication, public Timer
{
public:
    const String getApplicationName() override    { return "aooserver"; }
    const String getApplicationVersion() override { return "1.0.0"; }
    
    void initialise (const String& /*commandLineParameters*/) override
    {
        // Start your app here
        installKeyboardBreakHandler();
        
        server.startServer();

        startTimer(20);
    }
    
    void shutdown() override {}

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
    // ..your code goes here!    
    cerr << "Hello AOO world!" << endl;

    installKeyboardBreakHandler();

    AooServer server;
    
    server.startServer();
    
    while (!keyboardBreakOccurred) {
     
        usleep(20000);
        
        server.handleEvents();                       
    }
    
    return 0;
}
#endif
