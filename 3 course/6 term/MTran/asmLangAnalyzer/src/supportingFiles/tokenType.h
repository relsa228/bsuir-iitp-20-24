#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include <string>

enum class TokenType { 
    Command = 1,
    DataType = 2,
    ConditionalCrossing = 3,
    Name = 4,
    Sign = 5,
    Register = 6,
    Interruption = 7,
    Constant = 8
};

#endif // !TOKENTYPE_H