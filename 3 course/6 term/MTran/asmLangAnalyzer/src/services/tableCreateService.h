#ifndef TABLECREATESERVICE_H
#define TABLECREATESERVICE_H

#include <vector>
#include <string>

#include "../supportingFiles/tokenType.h"

#include "../models/token.h"

class TableCreateService
{
public:
    TableCreateService();
    ~TableCreateService();

    void createTable(std::vector<Token*>* tokenList);
};

#endif // !TABLECREATESERVICE_H