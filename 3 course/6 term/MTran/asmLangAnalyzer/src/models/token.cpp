#include "token.h"

Token::Token(TokenType tokenType, std::string data, std::string description, int position) :
data(data),
description(description),
tokenType(tokenType),
position(position) {}

Token::~Token() {}

void Token::setTokenType(int tokenType) {
    this->tokenType = TokenType(tokenType);
}

void Token::setData(std::string data) {
    this->data = data;
}

void Token::setDescription(std::string description) {
    this->description = description;
}

TokenType Token::getTokenType() {
    return this->tokenType;
}

std::string Token::getData() {
    return this->data;
}

std::string Token::getDescription() {
    return this->description;
}

int Token::getPosition() {
    return this->position;
}
