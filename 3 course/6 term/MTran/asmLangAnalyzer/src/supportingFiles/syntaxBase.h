#ifndef SYNTAXBASE_H
#define SYNTAXBASE_H

#include <string>
#include <vector>

#include "../models/token.h"

extern std::vector<std::string> zeroTerminalCommands;
extern std::vector<std::string> oneTerminalCommands;
extern std::vector<std::string> twoTerminalCommands;

extern std::vector<Token*> codePointNames;

#endif // !SYNTAXBASE_H