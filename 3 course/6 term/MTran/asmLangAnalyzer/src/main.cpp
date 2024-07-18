#include <string>
#include <vector>

#include "services/lexAnalizeService.h"
#include "services/tableCreateService.h"
#include "services/syntaxTreeService.h"
#include "services/semanticAnalizeService.h"

#include "models/syntaxTreeNode.h"

void printTree(SyntaxTreeNode *syntaxTree, int lvl) {
    std::string stick = "|";
    int i = 0;
    while(i != lvl) {
        stick += "|";
        i++;
    }

    for(auto token : *syntaxTree->getChildList()) {
        std::string printToken = stick + token->getData()->getData();
        printf("%s\n", printToken.c_str());
        if(token->getChildList()->size() != 0)
            printTree(token, lvl + 1);
    }
}

int main(int argc, const char** argv) {
    printf("123456789");
    return 0;
}