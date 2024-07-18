#include "../headers/morseDecoder.h"

#include "../headers/morseCodeMap.h"
#include "../headers/secondaryFunctions.h"

std::string decodeMorse(std::string morseCode) {
    std::string decoded;
    std::string code;
    std::map <std::string, std::string> MORSE_CODE;

    trim(morseCode);
    loadMorseDecodeTable(MORSE_CODE);
  
    for(int i = 0; i <= morseCode.length(); i++) {
        char symb = morseCode[i];
    
        if(symb == '.')
            code += '.';
        else if(symb == '-')
            code += '-';
        else if (symb == ' ' && morseCode[i+1] == ' ') {
            decoded += MORSE_CODE[code];
            code.clear();
            decoded += ' ';
            i=i+2;
        }
        else if (symb == ' ' || i == morseCode.length()) { 
            decoded += MORSE_CODE[code];
            code.clear();
        }
    }
    return decoded;
}