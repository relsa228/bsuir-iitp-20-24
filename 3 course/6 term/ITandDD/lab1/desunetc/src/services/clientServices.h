#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <string>
#include <stdlib.h>
#include <iostream>

#pragma warning(disable: 4996)

bool auth(std::string uname, std::string password, SOCKET Connection);
bool reg(std::string uname, std::string password, SOCKET Connection);
void openChat(std::string contrAgentName, std::string username, SOCKET Connection);
SOCKET clientStartUp();
bool is_number(const std::string& s);