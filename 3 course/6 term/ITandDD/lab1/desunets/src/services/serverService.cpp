#include "serverService.h"

void clientAuth(SOCKET newConnection) {
	int credsSize;
	std::string credsStr;
	std::string username = "";
	std::string password = "";
	bool passFlag = false;

	recv(newConnection, (char*)&credsSize, sizeof(int), NULL);
	char* creds = new char[credsSize + 1];
	creds[credsSize] = '\0';
	recv(newConnection, creds, credsSize, NULL);
	credsStr = creds;

	for(auto ch : credsStr) {
		if (ch == '\n') {
			passFlag = true;
			continue;
		}
		
		if (passFlag)
			password += ch;
		else
			username += ch;
	}

	if (auth(username, password)) {
		char authResultFlag[3] = "-0";
		send(newConnection, authResultFlag, sizeof(authResultFlag), NULL);
	}
	else {
		char authResultFlag[3] = "-1";
		send(newConnection, authResultFlag, sizeof(authResultFlag), NULL);
	}
}

void sendListOfUsers(SOCKET newConnection) {
	std::vector<std::string> listOfUsers = getListOfUsers();
	std::string stringOfUsers = "-l\n";

	for(auto uname : listOfUsers) {
		stringOfUsers += uname;
		stringOfUsers += "\n";
	}

	int sizeOfList = stringOfUsers.size();

	send(newConnection, (char*) &sizeOfList, sizeof(int), NULL);
	send(newConnection, stringOfUsers.c_str(), sizeOfList, NULL);
}

void sendChatList(SOCKET newConnection) {
	int chatUsersSize;
	std::string chatUsersStr;
	std::string getter = "";
	std::string sender = "";
	bool inptFlag = true;

	recv(newConnection, (char*)&chatUsersSize, sizeof(int), NULL);
	char* chatUsers = new char[chatUsersSize + 1];
	chatUsers[chatUsersSize] = '\0';
	recv(newConnection, chatUsers, chatUsersSize, NULL);
	chatUsersStr = chatUsers;

	for(auto ch : chatUsersStr) {
		if (ch == '\n')
			inptFlag = false;
		else if (inptFlag)
			getter += ch;
		else 
			sender += ch;
	}

	std::vector<std::string> vectOfMsgs = getChat(getter, sender);
	std::string stringOfMsgs = "-c\n";
	for(auto msg : vectOfMsgs) {
		stringOfMsgs += msg;
		stringOfMsgs += "\n";
	}

	int sizeOfMsgs = stringOfMsgs.size();

	send(newConnection, (char*) &sizeOfMsgs, sizeof(int), NULL);
	send(newConnection, stringOfMsgs.c_str(), sizeOfMsgs, NULL);
}

void saveMsg(SOCKET newConnection) {
	std::string messageStr = "";
	std::string getterName = "";
	std::string senderName = "";
	bool inptFlag = true;
	int messageSize;

	while(true) {
		recv(newConnection, (char*)&messageSize, sizeof(int), NULL);
		char* message = new char[messageSize + 1];
		message[messageSize] = '\0';
		recv(newConnection, message, messageSize, NULL);
		messageStr = message;
		if (message[0] == '-' && message[1] == 'm')
			break;
	}
	messageStr.erase(0, 3);

	while(true) {
		if(messageStr.at(0) == '\n' && !inptFlag)
			break;
		
		if(messageStr.at(0) == '\n') {
			inptFlag = false;
			messageStr.erase(0, 1);
			continue;
		}

		if(inptFlag)
			senderName += messageStr.at(0);
		else
			getterName += messageStr.at(0);
		
		messageStr.erase(0, 1);
	}

	saveMsg(getterName, senderName, messageStr);
}

void regUser(SOCKET newConnection) {
	std::string regCreds = "";
	std::string regUname = "";
	std::string regPass = "";
	bool inptFlag = true;
	int messageSize;

	while(true) {
		recv(newConnection, (char*)&messageSize, sizeof(int), NULL);
		char* message = new char[messageSize + 1];
		message[messageSize] = '\0';
		recv(newConnection, message, messageSize, NULL);
		regCreds = message;
		if (message[0] == '-' && message[1] == 'r')
			break;
	}
	regCreds.erase(0, 3);

	for(auto ch : regCreds) {
		if(ch == '\n') {
			inptFlag = false;
			continue;
		}

		if(inptFlag)
			regUname += ch;
		else
			regPass += ch;
	}

	if (saveUsr(regUname, regPass)) {
		char regResultFlag[3] = "-0";
		send(newConnection, regResultFlag, sizeof(regResultFlag), NULL);
	}
	else {
		char regResultFlag[3] = "-1";
		send(newConnection, regResultFlag, sizeof(regResultFlag), NULL);
	}
}