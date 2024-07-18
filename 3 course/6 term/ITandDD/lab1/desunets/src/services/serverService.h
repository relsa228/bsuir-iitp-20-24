#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <vector>

#include "databaseService.h"

void clientAuth(SOCKET newConnection);

void sendListOfUsers(SOCKET newConnection);
void sendChatList(SOCKET newConnection);

void saveMsg(SOCKET newConnection);
void regUser(SOCKET newConnection);