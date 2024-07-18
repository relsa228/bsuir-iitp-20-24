#ifndef SYNTAXTREENODE_H
#define SYNTAXTREENODE_H

#include <string>
#include <vector>

#include "token.h"

class SyntaxTreeNode {
private:
    Token* data;
    SyntaxTreeNode* pNode;
    std::vector<SyntaxTreeNode*>* chNodes;
public:
    void addChild(SyntaxTreeNode* newChild);
    void setData(Token* data);
    void setParent(SyntaxTreeNode* parent);

    std::vector<SyntaxTreeNode*>* getChildList();
    Token* getData();
    SyntaxTreeNode* getParent();

    SyntaxTreeNode();
    ~SyntaxTreeNode();
};

#endif // !SYNTAXTREENODE_H