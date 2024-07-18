#include <bits/stdc++.h>
#include <fstream>

void monoEncrypt(std::string *filestring, const std::string& filename, int key)
{
    std::fstream fmut;

    for (char & i : *filestring)
        i = char(int(i + key));

    fmut.open(filename, std::fstream::out);
    fmut << *filestring;
    fmut.close();
}

void monoDecrypt(const std::string& filename, int key)
{
    std::fstream fin;
    std::fstream fout;
    fin.open(filename, std::fstream::in);
    fout.open("monodecr.txt", std::fstream::out);

    char c;
    while (fin >> std::noskipws >> c) {
        int temp = (c - key);
        fout << (char)temp;
    }

    fin.close();
    fout.close();
}
