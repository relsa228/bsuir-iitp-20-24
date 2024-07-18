#include "semanticBase.h"

std::vector<std::string> regOnlyCommand = {
    "IMUL",
    "MUL",
    "DIV",
    "IDIV",
    "NEG",
    "INC",
    "DEC",
    "POP"
};

std::vector<std::string> regDataCommand = {
    "MOV",
    "MOVS",
    "OR",
    "SUB",
    "ADD",
    "CMP",
    "TEST",
    "XOR"
};