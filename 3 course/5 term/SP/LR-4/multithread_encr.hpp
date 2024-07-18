#include <iostream>
#include <thread>
#include <fstream>


void encrypt(std::string *filestring, int key, unsigned long long position, unsigned long long incr)
{
    for (size_t i = position; i < position + incr; i++)
        (*filestring)[i] = char(int((*filestring)[i] + key));
}

void initMultiEncrypt(std::string *filestring, const std::string& filename,  int key, int threadCount)
{
    std::fstream fmut;
    std::thread threadEncr[threadCount];

    unsigned long long position = 0;
    unsigned long long incr = filestring->length() / threadCount;
    unsigned long long mod = filestring->length() % threadCount;

    for (int i = 0; i < threadCount; i++) {
        if (mod == 0 || i != threadCount - 1)
            threadEncr[i] = std::thread(encrypt, filestring, key, position, incr);
        else
            threadEncr[i] = std::thread(encrypt, filestring, key, position, incr + mod);
        position += incr;
    }

    for (auto & i : threadEncr)
        i.join();

    fmut.open(filename, std::fstream::out);
    fmut << *filestring;
    fmut.close();
}

void initMultiDecrypt(const std::string& filename, int key)
{
    std::fstream fin;
    std::fstream fout;
    fin.open(filename, std::fstream::in);
    fout.open("multidecr.txt", std::fstream::out);

    char c;
    while (fin >> std::noskipws >> c) {
        int temp = (c - key);
        fout << (char)temp;
    }

    fin.close();
    fout.close();
}