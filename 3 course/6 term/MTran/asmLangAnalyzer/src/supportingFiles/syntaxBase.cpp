#include "syntaxBase.h"

std::vector<std::string> zeroTerminalCommands = {
    "RET",
    "ENDP"
};

std::vector<std::string> oneTerminalCommands = {
    "IMUL",
    "MUL",
    "DIV",
    "IDIV",
    "INT",
    "NEG",
    "INC",
    "PUSH",
    "POP",
    "CALL",
    "DEC",
    "PROC"
};

std::vector<std::string> twoTerminalCommands = {
    "MOV",
    "MOVS",
    "OR",
    "SUB",
    "ADD",
    "CMP",
    "TEST",
    "XOR"
};

std::vector<Token*> codePointNames;
