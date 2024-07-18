#ifndef SEMANTICANALIZESERVICE_H
#define SEMANTICANALIZESERVICE_H

#include <string>
#include <vector>
#include <algorithm>

#include "../supportingFiles/tokenType.h"
#include "../supportingFiles/semanticBase.h"
#include "../supportingFiles/lexicalBase.h"
#include "../supportingFiles/syntaxBase.h"

#include "../models/token.h"
#include "../models/syntaxTreeNode.h"

class SemanticAnalizeService {
private:
    
public:
    SemanticAnalizeService();
    ~SemanticAnalizeService();

    void initSemanticAnalize(SyntaxTreeNode* syntaxTree);
};


#endif // !SEMANTICANALIZESERVICE_H