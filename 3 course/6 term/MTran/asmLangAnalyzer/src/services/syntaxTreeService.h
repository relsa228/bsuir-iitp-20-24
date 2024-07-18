#ifndef SYNTAXTREESERVICE_H
#define SYNTAXTREESERVICE_H

#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>

#include "../supportingFiles/lexicalBase.h"
#include "../supportingFiles/syntaxBase.h"
#include "../supportingFiles/tokenType.h"

#include "../models/syntaxTreeNode.h"

class SyntaxTreeService {
private:
    void trim(std::string &str);
    void includeCommand(int lineCounter, std::string tokenName, std::vector<std::string> *terminals, SyntaxTreeNode *currentParent);
    
public:
    SyntaxTreeService();
    ~SyntaxTreeService();

    void buildTree(std::string filename, SyntaxTreeNode* root, int startPosition, int endPosition);
    void jumpCommand(int lineCounter, std::string tokenName, std::vector<std::string> *terminals, SyntaxTreeNode *currentParent, std::string filename);
    void printTree(SyntaxTreeNode* root);
};

#endif // !SYNTAXTREESERVICE_H