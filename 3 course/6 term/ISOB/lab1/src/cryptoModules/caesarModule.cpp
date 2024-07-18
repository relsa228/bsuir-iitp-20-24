#include "caesarModule.h"

void caesarEncr(std::string &input, int key) {
    for(int i = 0; i < input.length(); i++)
        input[i] = input[i] + key;  
}

void caesarDecr(std::string &input, int key) {
    for(int i = 0; i < input.length(); i++)
        input[i] = input[i] - key; 
}