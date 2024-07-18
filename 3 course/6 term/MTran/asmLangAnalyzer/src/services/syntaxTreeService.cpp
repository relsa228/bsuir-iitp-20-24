#include "syntaxTreeService.h"

SyntaxTreeService::SyntaxTreeService() {}

SyntaxTreeService::~SyntaxTreeService() {}

void SyntaxTreeService::trim(std::string &str) {
    size_t comment = str.find(";");
    if (comment != std::string::npos)
        str.erase(comment, str.size());
    str.erase(str.find_last_not_of(' ') + 1);        
    str.erase(0, str.find_first_not_of(' '));
}

void SyntaxTreeService::includeCommand(int lineCounter, std::string tokenName, std::vector<std::string> *terminals, SyntaxTreeNode *currentParent) {
    if(std::find(zeroTerminalCommands.begin(), zeroTerminalCommands.end(), tokenName) != zeroTerminalCommands.end()) {
        SyntaxTreeNode *node = new SyntaxTreeNode();
        currentParent->addChild(node);
        node->setData(new Token(TokenType::Command, tokenName, "Command lexem", lineCounter));
    }
    else if (std::find(oneTerminalCommands.begin(), oneTerminalCommands.end(), tokenName) != oneTerminalCommands.end()) {
        if(terminals->size() != 1)
            printf("ARG COUNT ERROR: at line %d\n", lineCounter);
        else {
            TokenType tokenType = TokenType::Command;
            
            if (std::find(nameList.begin(), nameList.end(), terminals->at(0)) == nameList.end()) {
                std::transform(terminals->at(0).begin(), terminals->at(0).end(), terminals->at(0).begin(), ::toupper);

                if (std::find(registerList.begin(), registerList.end(), terminals->at(0)) != registerList.end())
                    tokenType = TokenType::Register;
                else if (std::find(interruptionsList.begin(), interruptionsList.end(), terminals->at(0)) != interruptionsList.end())
                    tokenType = TokenType::Interruption;
                else if (std::regex_match(terminals->at(0), std::regex("^'[\\w|\\W]+'$")) || std::regex_match(terminals->at(0), std::regex("^\\d+$")))        
                    tokenType = TokenType::Constant;
            }

            SyntaxTreeNode *node = new SyntaxTreeNode();
            currentParent->addChild(node);
            node->setData(new Token(TokenType::Command, tokenName, "Command lexem", lineCounter));

            SyntaxTreeNode *childNode = new SyntaxTreeNode();
            node->addChild(childNode);
            childNode->setData(new Token(tokenType, terminals->at(0), "Terminal", lineCounter));
        }
    } else if (std::find(twoTerminalCommands.begin(), twoTerminalCommands.end(), tokenName) != twoTerminalCommands.end()) {
        if(terminals->size() != 2)
            printf("ARG COUNT ERROR: at line %d\n", lineCounter);
        else {
            TokenType tokenTypeF = TokenType::Command;
            TokenType tokenTypeS = TokenType::Command;

            if (std::find(nameList.begin(), nameList.end(), terminals->at(0)) == nameList.end()) {
                std::transform(terminals->at(0).begin(), terminals->at(0).end(), terminals->at(0).begin(), ::toupper);

                if (std::find(registerList.begin(), registerList.end(), terminals->at(0)) != registerList.end())
                    tokenTypeF = TokenType::Register;
                else if (std::find(interruptionsList.begin(), interruptionsList.end(), terminals->at(0)) != interruptionsList.end())
                    tokenTypeF = TokenType::Interruption;
                else if (std::regex_match(terminals->at(0), std::regex("^'[\\w|\\W]+'$")) || std::regex_match(terminals->at(0), std::regex("^\\d+$")))        
                    tokenTypeF = TokenType::Constant;
            }
            else
                tokenTypeF = TokenType::Name;
           
            if (std::find(nameList.begin(), nameList.end(), terminals->at(1)) == nameList.end()) {
                std::transform(terminals->at(1).begin(), terminals->at(1).end(), terminals->at(1).begin(), ::toupper);

                if (std::find(registerList.begin(), registerList.end(), terminals->at(1)) != registerList.end())
                    tokenTypeS = TokenType::Register;
                else if (std::find(interruptionsList.begin(), interruptionsList.end(), terminals->at(1)) != interruptionsList.end())
                    tokenTypeS = TokenType::Interruption;
                else if (std::regex_match(terminals->at(1), std::regex("^'[\\w|\\W]+'$")) || std::regex_match(terminals->at(1), std::regex("^\\d+$")))        
                    tokenTypeS = TokenType::Constant;
            }
            else
                tokenTypeS = TokenType::Name;

            SyntaxTreeNode *node = new SyntaxTreeNode();
            currentParent->addChild(node);
            node->setData(new Token(TokenType::Command, tokenName, "Command lexem", lineCounter));

            SyntaxTreeNode *childNode = new SyntaxTreeNode();
            node->addChild(childNode);
            childNode->setData(new Token(tokenTypeF, terminals->at(0), "Terminal", lineCounter));

            SyntaxTreeNode *childNodeSec = new SyntaxTreeNode();
            node->addChild(childNodeSec);
            childNodeSec->setData(new Token(tokenTypeS, terminals->at(1), "Terminal", lineCounter));
        }
    }
}

void SyntaxTreeService::jumpCommand(int lineCounter, std::string tokenName, std::vector<std::string> *terminals, SyntaxTreeNode *currentParent, std::string filename) {
    SyntaxTreeNode *node = new SyntaxTreeNode();
    currentParent->addChild(node);
    node->setData(new Token(TokenType::Command, tokenName, "Command lexem", lineCounter));

    int codePointLine = 0;

    if(terminals->size() != 1)
        printf("ARG COUNT ERROR: at line %d\n", lineCounter);
    else {
        SyntaxTreeNode *childNode = new SyntaxTreeNode();
        node->addChild(childNode);
        for(auto codePoint : codePointNames) {
            if(codePoint->getData() == terminals->at(0)) {
                codePointLine = codePoint->getPosition();
                childNode->setData(codePoint);
                break;
            }
        }
        buildTree(filename, node, codePointLine, lineCounter - 1);
        return;
    }
}

void SyntaxTreeService::buildTree(std::string filename, SyntaxTreeNode *root, int startPosition, int endPosition) {
    SyntaxTreeNode *currentParent = root;
    std::ifstream codeFile(filename);
    std::string codeRow;
    int lineCounter = 0;

    while(getline(codeFile, codeRow)) {
        auto chkPos = codeRow.find("code");
        lineCounter++;
        if (chkPos != std::string::npos)
            break;
    }

    while(lineCounter < startPosition) {
        getline(codeFile, codeRow);
        lineCounter++;
    }

    while(getline(codeFile, codeRow)) {
        auto chkPos = codeRow.find("data");
        if (chkPos != std::string::npos || lineCounter == endPosition)
            break;

        lineCounter++;
        trim(codeRow);
        std::string tokenName;

        while (codeRow[0] != ' ') {
            tokenName += codeRow[0];
            codeRow.erase(0, 1);
            if(codeRow.empty())
                break;
        }

        trim(codeRow);
        codeRow += " ";

        std::vector<std::string> *terminals = new std::vector<std::string>();
        std::string terminal;

        for(auto ch : codeRow) {
            if(!terminal.empty() && (ch == ' ' || ch == ',' || ch == ':')) {
                trim(terminal);
                terminals->push_back(terminal);
                terminal.clear();
            }
            else if (ch != ' ' || ch != ',' || ch != ':')
                terminal += ch;
        }

        std::transform(tokenName.begin(), tokenName.end(), tokenName.begin(), ::toupper);
        
        includeCommand(lineCounter, tokenName, terminals, currentParent);

        if(std::find(conditionalCrossing.begin(), conditionalCrossing.end(), tokenName) != conditionalCrossing.end() || tokenName == "LOOP") {
            SyntaxTreeNode *node = new SyntaxTreeNode();
            currentParent->addChild(node);
            node->setData(new Token(TokenType::ConditionalCrossing, tokenName, "Conditional Crossing", lineCounter));

            SyntaxTreeNode *ifNode = new SyntaxTreeNode();
            node->addChild(ifNode);
            ifNode->setData(new Token(TokenType::Name, "IF", "Conditional crossing", lineCounter));

            SyntaxTreeNode *elseNode = new SyntaxTreeNode();
            node->addChild(elseNode);
            elseNode->setData(new Token(TokenType::Name, "ELSE", "Conditional crossing", lineCounter));

            if(tokenName == "LOOP") {
                SyntaxTreeNode *decNode = new SyntaxTreeNode();
                ifNode->addChild(decNode);
                decNode->setData(new Token(TokenType::Command, "DEC", "Command", lineCounter));

                SyntaxTreeNode *cxNode = new SyntaxTreeNode();
                decNode->addChild(cxNode);
                cxNode->setData(new Token(TokenType::Register, "CX", "Terminal", lineCounter));
            }

            jumpCommand(lineCounter, "JMP", terminals, ifNode, filename);

            currentParent = elseNode;
        }

        if(tokenName == "JMP") {
            jumpCommand(lineCounter, tokenName, terminals, currentParent, filename);
            return;
        }
    }
}
