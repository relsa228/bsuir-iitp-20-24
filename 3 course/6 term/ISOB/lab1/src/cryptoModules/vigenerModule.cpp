#include "vigenerModule.h"

#include <iostream>

bool containsOnlyLetters(std::string const &str) {
    return std::all_of(str.begin(), str.end(), [](char const &c) {
        return std::isalpha(c);
    });
}

void toUpper(char &ch) {
    ch = toupper(static_cast<unsigned char>(ch));
}

bool validation(std::string &input, std::string &key) {
    if (!containsOnlyLetters(input) || !containsOnlyLetters(key))
        return false;

    for_each(input.begin(), input.end(), toUpper);
    for_each(key.begin(), key.end(), toUpper);
    
    if (input.length() > key.length())
        for (int i = 0; input.length() > key.length(); i++)
            key.push_back(key[i]);
    else if (input.length() < key.length())
        while (input.length() < key.length())
            key.pop_back();
    
    return true;
}

bool vigenerEncr(std::string &input, std::string key) {
    if (!validation(input, key))
        return false;

    for(int i = 0; i < input.length(); i++) {
        int out = (int)input[i] + (int)key[i] - 65;
        if (out > 90)
            out -= 26;
        input[i] = (char)out;
    } 

    return true;
}

bool vigenerDecr(std::string &input, std::string key) {
    if (!validation(input, key))
        return false;

    for(int i = 0; i < input.length(); i++) {
        int out = (int)input[i] - (int)key[i] + 65;
        if (out < 65)
            out += 26;
        input[i] = (char)out;
    } 

    return true;
}