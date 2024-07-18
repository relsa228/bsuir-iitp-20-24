#include "../headers/secondaryFunctions.h"

void trim(std::string &str) {
    str.erase(str.find_last_not_of(' ')+1);        
    str.erase(0, str.find_first_not_of(' '));
}