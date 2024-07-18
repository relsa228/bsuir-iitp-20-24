#include "../headers/controllers.h"
#include "../headers/secondaryFunctions.h"

void writeLog(std::string sigName) {
    std::time_t ct = std::time(0);
    std::string cc = ctime(&ct);
    std::ofstream out(getLogFileAddress(), std::ios::app);
    cc.pop_back();
    if (out.is_open())
        out << cc + ": signal " + sigName + " is send to desulogd:3" << std::endl;
}

void stopController(int sigNum) {
    writeLog("SIGSTOP");
    (void)signal(SIGSTOP, stopController);
}   

void contController(int sigNum) {
    writeLog("SIGCONT");
    (void)signal(SIGCONT, contController);
}

void hupController(int sigNum) {
    writeLog("SIGHUP");
    controllerExposer(setConfiguration());
    (void)signal(SIGHUP, hupController);
}

void intController(int sigNum) {
    writeLog("SIGINT");
    (void)signal(SIGINT, SIG_DFL);
    kill(getpid(), SIGINT);
}

void termController(int sigNum) {
    writeLog("SIGTERM");
    (void)signal(SIGTERM, SIG_DFL);
    kill(getpid(), SIGTERM);
}

void killController(int sigNum) {  
    writeLog("SIGKILL");
    (void)signal(SIGKILL, SIG_DFL);
    kill(getpid(), SIGKILL);
}

void usr1Controller(int sigNum) {
    writeLog("SIGUSR1");
    (void)signal(SIGUSR1, usr1Controller);
}

void usr2Controller(int sigNum) {    
    writeLog("SIGUSR2");
    (void)signal(SIGUSR2, usr2Controller);
}

void controllerExposer(std::list<std::string> *listOfSignals) {
    (void)signal(SIGSTOP, SIG_DFL); 
    (void)signal(SIGCONT, SIG_DFL); 
    (void)signal(SIGHUP, SIG_DFL); 
    (void)signal(SIGINT, SIG_DFL); 
    (void)signal(SIGTERM, SIG_DFL); 
    (void)signal(SIGKILL, SIG_DFL); 
    (void)signal(SIGUSR1, SIG_IGN); 
    (void)signal(SIGUSR1, SIG_IGN);

    for(auto signalId : *listOfSignals) {
        if (signalId == "SIGSTOP")
            (void)signal(SIGSTOP, stopController); 
        if (signalId == "SIGCONT")
            (void)signal(SIGCONT,contController);
        if (signalId == "SIGHUP")
            (void)signal(SIGHUP,hupController);
        if (signalId == "SIGINT")
            (void)signal(SIGINT,intController);
        if (signalId == "SIGTERM")
            (void)signal(SIGTERM,termController);
        if (signalId == "SIGKILL")
            (void)signal(SIGKILL,killController);
        if (signalId == "SIGUSR1")
            (void)signal(SIGUSR1,usr1Controller);
        if (signalId == "SIGUSR2")
            (void)signal(SIGUSR2,usr2Controller);
    }
}