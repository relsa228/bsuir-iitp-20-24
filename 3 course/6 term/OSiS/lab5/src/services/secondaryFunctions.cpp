#include "../headers/secondaryFunctions.h"


nlohmann::json getJsonObject() {
    std::list<std::string> *configSig = new std::list<std::string>;
    std::string jsonResponseStr;
    std::ifstream configFile;
    
    configFile.open(CONFIG_FILE); 
    getline(configFile, jsonResponseStr, '\0'); 
    configFile.close();   

    return nlohmann::json::parse(jsonResponseStr);
}

std::list<std::string>* setConfiguration() {
    std::list<std::string> *configSig = new std::list<std::string>;
    
    nlohmann::json responseJson = getJsonObject();
    nlohmann::json listOfSignals = responseJson["list_of_signals"];
    
    if(listOfSignals["SIGSTOP"])
        configSig->push_front("SIGSTOP");
    if(listOfSignals["SIGCONT"])
        configSig->push_front("SIGCONT");
    if(listOfSignals["SIGHUP"])
        configSig->push_front("SIGHUP");
    if(listOfSignals["SIGINT"])
        configSig->push_front("SIGINT");
    if(listOfSignals["SIGTERM"])
        configSig->push_front("SIGTERM");
    if(listOfSignals["SIGKILL"])
        configSig->push_front("SIGKILL");
    if(listOfSignals["SIGUSR1"])
        configSig->push_front("SIGUSR1");
    if(listOfSignals["SIGUSR2"])
        configSig->push_front("SIGUSR2");

    return configSig;
}

std::string getLogFileAddress() {
    nlohmann::json responseJson = getJsonObject();
    auto object = responseJson["log_file_path"];
    return object;
}

void termProccess(int pid) {
    int inptPid;
    std::list<int> pidList;
    std::ifstream pidFile(PID_LIST_FILE);

    while (pidFile >> inptPid) 
        pidList.push_back((int) inptPid);
    pidFile.close();

    std::ofstream clearFile;
    clearFile.open(PID_LIST_FILE, std::ofstream::out | std::ofstream::trunc);
    clearFile.close();

    std::ofstream inptPidFile(PID_LIST_FILE, std::ios::app);
    for(int outPid : pidList) 
        if (outPid != pid)
            inptPidFile << std::to_string(outPid) << "\n";
    
    kill(pid, SIGKILL);
}

void termAllProcesses() {
    int inptPid;
    std::list<int> pidList;
    std::ifstream pidFile(PID_LIST_FILE);

    while (pidFile >> inptPid) 
        pidList.push_back(inptPid);
    pidFile.close();

    std::ofstream clearFile;
    clearFile.open(PID_LIST_FILE, std::ofstream::out | std::ofstream::trunc);
    clearFile.close();

    for(auto pid : pidList)
        kill(pid, SIGKILL);
}