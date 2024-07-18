#include "clientServices.h"

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

bool auth(std::string uname, std::string password, SOCKET Connection) {
	std::string creds = uname + "\n" + password;
	int credsSize = creds.size();

	send(Connection, (char*) &credsSize, sizeof(int), NULL);
	send(Connection, creds.c_str(), sizeof(creds), NULL);

	char authResult[3];
	while(authResult[1] != '0' && authResult[1] != '1')
		recv(Connection, authResult, sizeof(authResult), NULL);
	
	if(strcmp(authResult, "-0") == 0) 
		return true;
		
	return false;
}

void openChat(std::string contrAgentName, std::string username, SOCKET Connection) {
	while(true)	{
		system("cls");
		char commandFlag[3] = "-c";
		send(Connection, commandFlag, sizeof(commandFlag), NULL);

		std::string chatAgents = username + "\n" + contrAgentName + "\n";

		int sizeOfAgents = chatAgents.size();
		send(Connection, (char*) &sizeOfAgents, sizeof(int), NULL);
		send(Connection, chatAgents.c_str(), sizeOfAgents, NULL);

		int chatSize;
		std::string msgStr = "";
		std::string buffer = "";

		while(true) {
			recv(Connection, (char*)&chatSize, sizeof(int), NULL);
			char* chat = new char[chatSize + 1];
			chat[chatSize] = '\0';
			recv(Connection, chat, chatSize, NULL);
			msgStr = chat;
			buffer = "";
			if (msgStr[0] == '-' && msgStr[1] == 'c')
				break;
		}
		
		msgStr.erase(0, 3);
		for(auto ch : msgStr) {
			if (ch == '\n') {
				std::cout << buffer << std::endl;
				buffer.clear();
				continue;
			}
			buffer += ch;
		}
		std::cout << "\n" + username + "> ";

		std::string outMsg = "";
		std::getline (std::cin, outMsg);

		if (outMsg == "/out") {
			return;
        }
		else if (outMsg == "/update") {}
		else {
			char commandFlag[3] = "-m";
			send(Connection, commandFlag, sizeof(commandFlag), NULL);

			std::string sendMessage = "-m\n" + chatAgents + outMsg;
			int sizeOfSendMessage = sendMessage.size();
			send(Connection, (char*) &sizeOfSendMessage, sizeof(int), NULL);
			send(Connection, sendMessage.c_str(), sizeOfSendMessage, NULL);
		}
	}
}

SOCKET clientStartUp() {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if(WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if(connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return NULL;
	}
	std::cout << "Connected!\n";

	return Connection;
}

bool reg(std::string uname, std::string password, SOCKET Connection) {
	std::string sendCreds = "-r\n" + uname + "\n" + password;
	
	int sizeOfRegCreds = sendCreds.size();
	send(Connection, (char*) &sizeOfRegCreds, sizeof(int), NULL);
	send(Connection, sendCreds.c_str(), sizeOfRegCreds, NULL);

	char regResult[3];
	while(regResult[1] != '0' && regResult[1] != '1')
		recv(Connection, regResult, sizeof(regResult), NULL);
	
	if(strcmp(regResult, "-0") == 0) 
		return true;
		
	return false;
}