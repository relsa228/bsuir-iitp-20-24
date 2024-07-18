#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "services/clientServices.h"


int main(int argc, char* argv[]) {
	SOCKET openConnection = clientStartUp();
	if(openConnection == NULL) 
		return 1;

	std::string username;
	std::string password;

	if (argc == 2 && strcmp(argv[1], "-h") == 0) {
		std::string helpMsg = "Welcome to desunet chat:3\nFor get connection to network use this commands:\n \
		\n-r : if you have not account use this command > The syntax -- desunetc -r <uniq_username> <password>\
		\n-u : if you have account use this command > The syntax -- desunetc -u <your_username> -- after this you need to input your password in opened field \
		\n-h : if you need help use this command\
		\n\nUwU Enjoy you use ^_^"; 
		std::cout << helpMsg;
		return 0;
	}

	if (argc == 4 && strcmp(argv[1], "-r") == 0) {
		username = argv[2];
		password = argv[3];

		char commandFlag[3] = "-r";
		send(openConnection, commandFlag, sizeof(commandFlag), NULL);

		if(reg(username, password, openConnection)) {
			std::cout << "Registration complete" << std::endl;
			return 0;
		}
		std::cout << "Registration error" << std::endl;
		return 1;
	}

    if (argc == 3 && strcmp(argv[1], "-u") == 0) {       
        username = argv[2];
		std::cout << "Enter password for " << username << " : ";
		getline(std::cin, password);
    }
	else {
		std::cout << "Command error > use -h for get help" << std::endl;
		return 1;
	}

	char commandFlag[3] = "-a";
	send(openConnection, commandFlag, sizeof(commandFlag), NULL);
	if (auth(username, password, openConnection)) {	
		while (true) {
			system("cls");

			char commandFlag[3] = "-l";
			send(openConnection, commandFlag, sizeof(commandFlag), NULL);
			
			int listOfUsersSize;
			std::string lsUser = "";
			std::string buffer = "";

			while(true) {
				recv(openConnection, (char*)&listOfUsersSize, sizeof(int), NULL);
				char* lsOfUsers = new char[listOfUsersSize + 1];
				lsOfUsers[listOfUsersSize] = '\0';
				recv(openConnection, lsOfUsers, listOfUsersSize, NULL);
				lsUser = lsOfUsers;
				buffer = "";
				if (lsUser[0] == '-' && lsUser[1] == 'l')
					break;
			}
			lsUser.erase(0, 3);
		
			int counter = 0;
			std::cout << "Welcome, " + username + "!\n" << "\n---------------\n" 
				<< + "Chat users:" << "\n---------------\n" << std::endl;
			std::vector<std::string> users;
			for(auto ch : lsUser) {
				if (ch == '\n'){
					std::cout << counter << " - " << buffer << std::endl;
					users.push_back(buffer);
					buffer = "";
					counter++;
					continue;
				}
				buffer += ch;
			}
			std::cout << "\n> ";

			std::string chatNumber;
			std::getline (std::cin, chatNumber);
			
			if (is_number(chatNumber)) 
				openChat(users.at(stoi(chatNumber)), username, openConnection);
			else if (chatNumber == "/update") {}
			else if (chatNumber == "/out")
				break;
		}
	}
	else 
		std::cout << "Auth error" << std::endl;
	return 0;
}