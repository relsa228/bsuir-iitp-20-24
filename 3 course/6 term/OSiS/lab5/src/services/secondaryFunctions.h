#define PID_LIST_FILE "/opt/desulogd/pidlist.txt"
#define CONFIG_FILE "/opt/desulogd/config.json"

#include <list>
#include <string>
#include <fstream>
#include <sys/types.h>
#include <signal.h>
#include "nlohmann/json.hpp"

std::list<std::string>* setConfiguration(); 
void termProccess(int pid);
void termAllProcesses();
std::string getLogFileAddress(); 