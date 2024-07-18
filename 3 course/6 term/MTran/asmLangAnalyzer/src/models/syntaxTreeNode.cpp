#include "syntaxTreeNode.h"

SyntaxTreeNode::SyntaxTreeNode() {
    this->chNodes = new std::vector<SyntaxTreeNode*>();
}

SyntaxTreeNode::~SyntaxTreeNode() {}

void SyntaxTreeNode::addChild(SyntaxTreeNode *newChild) {
    newChild->setParent(this);
    this->chNodes->push_back(newChild);
}

void SyntaxTreeNode::setData(Token *data) {
    this->data = data;
}

void SyntaxTreeNode::setParent(SyntaxTreeNode *parent) {
    this->pNode = parent;
}

std::vector<SyntaxTreeNode *> *SyntaxTreeNode::getChildList() {
    return this->chNodes;
}

Token *SyntaxTreeNode::getData() {
    return this->data;
}

SyntaxTreeNode *SyntaxTreeNode::getParent() {
    return this->pNode;
}
