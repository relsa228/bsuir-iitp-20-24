//ввод просто первым аргументом 
//ключ передается за ним
//дальше флаги:
//-e / -d -- шифровка/расшифровка (по дефолту шифровка)
//-v /-c -- Виженер/Цезарь (по дефолту Цезарь)
//-fi -- ввод из файла (аргумент ввода будет считаться адресом файла)
//-fo -- вывод в файл (после флага должен идти адрес файла вывода)

#include <string>
#include <fstream>
#include <sstream>

#include "cryptoModules/caesarModule.h"
#include "cryptoModules/vigenerModule.h"

std::string readFile(const std::string& fileName) {
    std::ifstream f(fileName);
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

int main(int argc, const char** argv) {
    std::string crypt = "";
    std::string key = "";
    std::string outputAddress = "";

    bool encrMode = true;
    bool cipherMode = true;
    bool fileInput = false;
    bool fileOutput = false;

    if (argc < 3) {        
        printf("Not enough data\n");
        return 1;
    }

    crypt = argv[1];
    key = argv[2];

    for(int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0)
            encrMode = true;
        else if (strcmp(argv[i], "-d") == 0)
            encrMode = false;
        else if (strcmp(argv[i], "-v") == 0)
            cipherMode = false;
        else if (strcmp(argv[i], "-c") == 0)
            cipherMode = true;
        else if (strcmp(argv[i], "-fi") == 0)
            fileInput = true;
        else if (strcmp(argv[i], "-fo") == 0) {
            fileOutput = true;
            if (i != argc - 1)
                outputAddress = argv[i + 1];
            else {
                printf("Missing output adress\n");
                return 1;
            }
        }
    }

    if (fileInput) 
        crypt = readFile(crypt);

    if (crypt == "") {
        printf("Input is empty\n");
        return 1;
    }

    if (encrMode) {
        if (cipherMode)
            caesarEncr(crypt, stoi(key));
        else if (!vigenerEncr(crypt, key)){
            printf("Incorrect text/key input\n");
            return 1;
        }
    }
    else {
        if (cipherMode)
            caesarDecr(crypt, stoi(key));
        else if (!vigenerDecr(crypt, key)){
            printf("Incorrect text/key input\n");
            return 1;
        }
    }

    if (fileOutput) {
        std::ofstream out;         
        out.open(outputAddress); 
        if (out.is_open()) {
            out << crypt;
        }
        else {
            printf("Can't open target file\n");
            return 1;
        }
    }
    else 
        printf("RESULT: %s", crypt.c_str());

    return 0;
}