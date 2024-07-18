#include "tableCreateService.h"

TableCreateService::TableCreateService() {}

TableCreateService::~TableCreateService() {}

void TableCreateService::createTable(std::vector<Token *> *tokenList) {
    std::string commandTable = "\n\nCommands:\n----------------------------", 
                conditionalCrossingTable = "\n\nConditional crossings:\n----------------------------", 
                nameTable = "\n\nNames:\n----------------------------", 
                signTable = "\n\nSigns:\n----------------------------", 
                registerTable = "\n\nRegisters:\n----------------------------", 
                interruptionsTable = "\n\nInterruptions:\n----------------------------";
    
    for(auto token : *tokenList) {
        switch (token->getTokenType()) {
            case TokenType::Command:
                commandTable += "\nToken name: " + token->getData() + "\nDescription: " + token->getDescription() + "\n-";
                break;

            case TokenType::ConditionalCrossing:
                conditionalCrossingTable += "\nToken name: " + token->getData() + "\nDescription: " + token->getDescription() + "\n-";
                break;

            case TokenType::Interruption:
                interruptionsTable += "\nToken name: " + token->getData() + "\nDescription: " + token->getDescription() + "\n-";
                break;
                
            case TokenType::Name:
                nameTable += "\nToken name: " + token->getData() + "\nDescription: " + token->getDescription() + "\n-";
                break;

            case TokenType::Register:
                registerTable += "\nToken name: " + token->getData() + "\nDescription: " + token->getDescription() + "\n-";
                break;

            case TokenType::Sign:
                signTable += "\nToken name: " + token->getData() + "\nDescription: " + token->getDescription() + "\n-";
                break;

            default:
                break;
        }
    }

    printf("%s", commandTable.c_str());
    printf("%s", conditionalCrossingTable.c_str());
    printf("%s", nameTable.c_str());
    printf("%s", signTable.c_str());
    printf("%s", registerTable.c_str());
    printf("%s", interruptionsTable.c_str());
}