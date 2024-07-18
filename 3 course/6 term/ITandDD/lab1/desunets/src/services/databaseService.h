#include <vector>
#include <string>
#include <stdlib.h>

#include "../sqlite/sqlite3.h"

void dbInit();
bool auth(std::string username, std::string password);

std::vector<std::string> getListOfUsers();
std::vector<std::string> getChat(std::string getterId, std::string senderId);

void saveMsg(std::string getterId, std::string senderId, std::string msg);
bool saveUsr(std::string username, std::string password);