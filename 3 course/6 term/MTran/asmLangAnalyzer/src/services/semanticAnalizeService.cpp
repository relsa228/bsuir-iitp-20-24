#include "semanticAnalizeService.h"

SemanticAnalizeService::SemanticAnalizeService() {}

SemanticAnalizeService::~SemanticAnalizeService() {}

void SemanticAnalizeService::initSemanticAnalize(SyntaxTreeNode* syntaxTree) {
    for(auto token : *syntaxTree->getChildList()) {
        if(token->getChildList()->size() != 0)
            initSemanticAnalize(token);
        else if (token->getData()->getData() != "RET" && token->getData()->getData() != "ENDP" && 
                    token->getData()->getData() != "LOOP") {
            SyntaxTreeNode* parentNode = token->getParent();
            Token* parentData = parentNode->getData();
            std::string commandName = parentData->getData();

            bool codePointFlag = false;
            for (auto codePoint: codePointNames) {
                std::string buffer = codePoint->getData();
                std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::toupper);
                if (buffer == token->getData()->getData()){
                    codePointFlag = true;
                    break;
                }
            }
            
            if (commandName == "PUSH" && (token->getData()->getTokenType() != TokenType::Name && 
                    (token->getData()->getTokenType() != TokenType::Register || codePointFlag))) 
                printf("TYPE ERROR: at line %d\n", parentData->getPosition());
            else if (commandName == "INT" && (token->getData()->getTokenType() != TokenType::Interruption || codePointFlag)) 
                printf("TYPE ERROR: at line %d\n", parentData->getPosition());
            else if (std::find(regOnlyCommand.begin(), regOnlyCommand.end(), commandName) != regOnlyCommand.end() && 
                        (token->getData()->getTokenType() != TokenType::Register || codePointFlag)) 
                printf("TYPE ERROR: at line %d\n", parentData->getPosition());

            else if (std::find(regDataCommand.begin(), regDataCommand.end(), commandName) != regDataCommand.end() && !codePointFlag) {
                if (parentNode->getChildList()->at(0)->getData()->getTokenType() != TokenType::Register && 
                        parentNode->getChildList()->at(0)->getData()->getTokenType() != TokenType::Name) 
                    printf("TYPE ERROR: at line %d\n", parentData->getPosition());
                
                else if (parentNode->getChildList()->at(1)->getData()->getTokenType() != TokenType::Register && 
                            parentNode->getChildList()->at(1)->getData()->getTokenType() != TokenType::Name &&
                                parentNode->getChildList()->at(1)->getData()->getTokenType() != TokenType::Interruption &&
                                    parentNode->getChildList()->at(1)->getData()->getTokenType() != TokenType::Constant)     
                    printf("TYPE ERROR: at line %d\n", parentData->getPosition());
            }
        }
    }
}
