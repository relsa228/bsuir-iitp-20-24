#include "lexAnalizeService.h"

LexAnalizeService::LexAnalizeService() {}

LexAnalizeService::~LexAnalizeService() {}

std::vector<Token *> *LexAnalizeService::initLexAnalize(std::string filename) {
    std::vector<Token *> *resultVector = new std::vector<Token *>();
    checkDataValNames(filename, resultVector);
    checkCodeValNames(filename, resultVector);
    checkCodeLex(filename, resultVector);
    return resultVector;
}

void LexAnalizeService::trim(std::string &str) {
    size_t comment = str.find(";");
    if (comment != std::string::npos)
        str.erase(comment, str.size());
    str.erase(str.find_last_not_of(' ') + 1);        
    str.erase(0, str.find_first_not_of(' '));
}

void LexAnalizeService::checkDataValNames(std::string filename, std::vector<Token*>* tokenList) {
    std::ifstream codeFile(filename);
    std::string dataRow;
    int lineCounter = 0;

    while(getline(codeFile, dataRow)) {
        auto chkPos = dataRow.find("data");
        lineCounter++;

        if (chkPos != std::string::npos)
            break;
    }

    while(getline(codeFile, dataRow)) {
        auto chkPos = dataRow.find("code");
        lineCounter++;

        if (chkPos != std::string::npos)
            break;

        trim(dataRow);
        bool dataTypeFlag = false;
        std::string valName, dataType;
        for(auto ch : dataRow) {
            if (ch == ' ' && dataTypeFlag )
                break;
            if (ch == ' ' ) {
                dataTypeFlag = true;
                continue;
            }

            if(dataTypeFlag)
                dataType += ch;
            else 
                valName += ch;
        }
        std::transform(dataType.begin(), dataType.end(), dataType.begin(), ::toupper);
        if (std::find(dataTypesList.begin(), dataTypesList.end(), dataType) != dataTypesList.end()) {
            nameList.push_back(valName);
            tokenList->push_back(new Token(TokenType::Name, valName, dataType + " variable", -1));
        }
        else 
            printf("DATATYPE ERROR: at line %d\n", lineCounter);
    }
    
    codeFile.close();
}

void LexAnalizeService::checkCodeValNames(std::string filename, std::vector<Token *> *tokenList) {
    std::ifstream codeFile(filename);
    std::string codeRow;
    int lineCounter = 0;

    while(getline(codeFile, codeRow)) {
        auto chkPos = codeRow.find("code");
        lineCounter++;

        if (chkPos != std::string::npos)
            break;
    }

    while(getline(codeFile, codeRow)) {
        auto chkPos = codeRow.find("data");
        lineCounter++;

        if (chkPos != std::string::npos)
            break;

        trim(codeRow);
        if (!std::regex_match(codeRow, std::regex("^[\\S][^:]+:(.*)")))
            continue;

        std::string pointName;
        for(auto ch : codeRow) {
            if(ch == ':'){
                tokenList->push_back(new Token(TokenType::Name, pointName, "Code point name", lineCounter));
                codePointNames.push_back(new Token(TokenType::Name, pointName, "Code point name", lineCounter));
            }
            pointName += ch;
        }
    }
    
    codeFile.close();
}

void LexAnalizeService::checkCodeLex(std::string filename, std::vector<Token *> *tokenList) {
    std::ifstream codeFile(filename);
    std::string codeRow;
    int lineCounter = 0;

    while(getline(codeFile, codeRow)) {
        auto chkPos = codeRow.find("code");
        lineCounter++;

        if (chkPos != std::string::npos)
            break;
    }

    while(getline(codeFile, codeRow)) {
        auto chkPos = codeRow.find("data");
        lineCounter++;

        if (chkPos != std::string::npos)
            break;

        trim(codeRow);
        codeRow += " ";
        std::string tokenName;
        for(auto ch : codeRow) {
            if(!tokenName.empty() && (ch == ' ' || ch == ',' || ch == ':')) {
                trim(tokenName);
                bool isName = false;

                for(auto token : *tokenList) {
                    if (token->getData() == tokenName) {
                        tokenName.clear();
                        isName = true;
                        break;
                    }
                }

                std::transform(tokenName.begin(), tokenName.end(), tokenName.begin(), ::toupper);
                if (isName || tokenName.empty())
                    continue;
                else if (std::regex_match(tokenName, std::regex("^'[\\w|\\W]+'$")))
                    tokenList->push_back(new Token(TokenType::Constant, tokenName, "Constant string value", lineCounter));
                else if (std::regex_match(tokenName, std::regex("^\\d+$")))
                    tokenList->push_back(new Token(TokenType::Constant, tokenName, "Constant numeric value", lineCounter));
                else if (std::find(commandList.begin(), commandList.end(), tokenName) != commandList.end()) 
                    tokenList->push_back(new Token(TokenType::Command, tokenName, "Command lexem", lineCounter));
                else if (std::find(conditionalCrossing.begin(), conditionalCrossing.end(), tokenName) != conditionalCrossing.end()) 
                    tokenList->push_back(new Token(TokenType::ConditionalCrossing, tokenName, "Conditional crossing lexem", lineCounter));
                else if (std::find(registerList.begin(), registerList.end(), tokenName) != registerList.end()) 
                    tokenList->push_back(new Token(TokenType::Register, tokenName, "Register lexem", lineCounter));
                else if (std::find(interruptionsList.begin(), interruptionsList.end(), tokenName) != interruptionsList.end()) 
                    tokenList->push_back(new Token(TokenType::Interruption, tokenName, "Interruption lexem", lineCounter));
                else if (std::find(signList.begin(), signList.end(), tokenName) != signList.end()) 
                    tokenList->push_back(new Token(TokenType::Sign, tokenName, "Sign lexem", lineCounter));
                else
                    printf("LEXEM ERROR: at line %d lexem: %s\n", lineCounter, tokenName.c_str());
                tokenName.clear();
            }
            else if(ch != ' ' || ch != ',' || ch != ':')
                tokenName += ch;
        }
    }
}
