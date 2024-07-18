#ifndef LEXANALIZESERVICE_H
#define LEXANALIZESERVICE_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <regex>

#include "../supportingFiles/lexicalBase.h"
#include "../supportingFiles/syntaxBase.h"
#include "../supportingFiles/tokenType.h"

#include "../models/token.h"

class LexAnalizeService {
public:
    LexAnalizeService();
    ~LexAnalizeService();

    std::vector<Token*>* initLexAnalize(std::string filename);

private:
    void checkDataValNames(std::string filename, std::vector<Token*>* tokenList);
    void checkCodeValNames(std::string filename, std::vector<Token*>* tokenList);
    void checkCodeLex(std::string filename, std::vector<Token*>* tokenList);
    void trim(std::string &str);
};

#endif // !LEXANALIZESERVICE_H