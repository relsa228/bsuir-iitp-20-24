#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "../supportingFiles/tokenType.h"

class Token {
private:
    TokenType tokenType;
    int position;
    std::string data;
    std::string description;
public:
    Token(TokenType tokenType, std::string data, std::string description, int position);
    ~Token();

    void setTokenType(int tokenType);
    void setData(std::string data);
    void setDescription(std::string description);
    void setPosition(int position);

    TokenType getTokenType();
    std::string getData();
    std::string getDescription();
    int getPosition();
};

#endif // !TOKEN_H