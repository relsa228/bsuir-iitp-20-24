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
    return dlin;
}

void print(char* substr)
{
    for (int i = 0; i < schet(substr, 80); i++)
    {
        cout << substr[i];
    }
}

void podstroka(char* str, char isk, int tx, char* substr)
{
    for (int i = 0; i < schet(str, tx); i++)
    {
        if (str[i] == isk)
        {
            cout << str[i];
            print(substr);
        }
        else
        {
            cout << str[i];
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    const int dlin = 80;
    char isk;
    char substr[dlin], str[dlin];
    cout << "Введите текст: ";
    gets_s(str);
    cout << "Введите подстроку: ";
    gets_s(substr);
    cout << "Введите искомый символ: ";
    cin >> isk;
    cout << endl;
    cout << "Исправленный текст: ";
    podstroka(str, isk, dlin, substr);
    cout << endl;
    return 0;
}