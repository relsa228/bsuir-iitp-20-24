#include "../headers/morseCoder.h"

#include "../headers/morseCodeMap.h"
#include "../headers/secondaryFunctions.h"

std::string codeMorse(std::string inptText) {
    std::string code;
    std::map <char, std::string> MORSE_CODE;

    trim(inptText);
    loadMorseCodeTable(MORSE_CODE);

    for(auto symb : inptText) 
        code += MORSE_CODE[symb] + " ";
  
    return code;
}