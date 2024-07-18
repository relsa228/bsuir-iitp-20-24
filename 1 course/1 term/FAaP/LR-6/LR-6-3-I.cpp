#include <iostream>

using namespace std;

int schet(char* text, int dlin)
{
    int num = 0;
    for (int i = 0; i < dlin; i++)
    {
        if (text[num] != '\0')
        {
            num = num++;
        }
        else
        {
            return num;
        }
    }
}

int probel(char* text, int dlin)
{
    int num = dlin;
    for (int i = 0; i < dlin; i++)
    {
        if (text[num] != ' ')
        {
            num = num--;
        }
        else
        {
            num = num--;
            return num;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    char text[80];
    cout << "Введите строку: ";
    gets_s(text);
    int del = 0;
    /* cout << prob(text, schet(text, 80)) - 1 << "     " << schet(text, 80)<< "     " << schet(text, 80) - prob(text, schet(text, 80));*/
    cout << "Исправленная строка:";
    for (;;)
    {
        int stroka = schet(text, 80) - del + 1;
        int prob = probel(text, (schet(text, 80)) - del) + 1;
        int vivod = stroka - prob;
        //cout << prob << " " << stroka << " " << del << " " << vivod << "       ";
        if (stroka != prob)
        {
            for (int j = 0; j < vivod; j++)
            {
                cout << text[prob];
                prob = prob++;
                del = del++;
            }
        }
        else
        {
            cout << ' ';
            for (int j = 0; j < stroka; j++)
            {
                cout << text[j];
            }
        }
       /* cout << "\n";*/
        if (vivod == 0)
        {
            break;
        }
    }
    delete[] text;
    return 0;
}
