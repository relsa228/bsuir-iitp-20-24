#include <iostream>
#include <string>
#include <string.h>

#include "headers/morseDecoder.h"
#include "headers/morseCoder.h"

int main(int argc, char *argv[]) {
  if (argc == 1)
    printf("Incorrect input. Type -h for help");
  else if (strcmp(argv[1], "-h") == 0)
    printf("---INPUT FORMAT: morsechan [option] [processed text]---\nOPTIONS:\n-h : for call help\n-v : for call version information\n-c : for set code mode\n-d : for set decode mode");
  else if (strcmp(argv[1], "-v") == 0)
    printf("morsechan\nvesion: 0.0.1\ndev by _relsa <3");
  else if (strcmp(argv[1], "-c") == 0 && argc > 2) 
    printf(codeMorse(argv[2]).c_str());
  else if (strcmp(argv[1], "-d") == 0 && argc > 2)
    printf(decodeMorse(argv[2]).c_str());
  else
    printf("Incorrect input. Type -h for help");
  return 0;
}
