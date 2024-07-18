#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

void zam(string& str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == 'c')
        {
            if (str[i + 1] == 'e' || str[i + 1] == 'i' || str[i + 1] == 'y')
            {
                str[i] = 's';
            }
            else
            {
                str[i] = 'k';
            }
        }
        else if (str[i] == 'q')
        {
            if (str[i + 1] == 'u')
            {
                str[i] = 'k';
                str[i + 1] = 'v';
            }
            else
                str[i] = 'k';
        }
        else if (str[i] == 'x')
        {
            str[i] = 'k';
            str.insert(i+1, 1, 's');
        }
        else if (str[i] == 'w')
            str[i] = 'v';
        else if (str[i] == 'p' && str[i + 1] == 'h')
        {
            str[i] = 'f';
            str.erase(i+1, 1); 
        }
        else if (str[i] == 'y' && str[i + 1] == 'o' && str[i + 2] == 'u')
        {
            str[i] = 'u';
            str.erase(i + 1, 2);
        }
        else if (str[i] == 'o' && str[i + 1] == 'o')
        {
            str[i] = 'u';
            str.erase(i + 1, 1);
        }
        else if (str[i] == 'e' && str[i + 1] == 'e')
        {
            str[i] = 'i';
            str.erase(i + 1, 1);
        }
        else if (str[i] == 't' && str[i + 1] == 'h')
        {
            str[i] = 'z';
            str.erase(i + 1, 1);
        }
    }
}

void zamena2(string& str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == str[i + 1])
        {
            str.erase(i + 1, 1);
        }
    }
}

int main()
{
    string str;
    setlocale(LC_ALL, "Russian");
    for (;;)
    {
        cout << "Введите текст (не длинее 100 символов): ";
        getline(cin, str);
        if (str.size() > 100)
        {
            cout << "\nОшибка. Длина превышает 100 символов. Повторите попытку." << endl;
        }
        else
        {
            break;
        }
    }
    zam(str);
    zamena2(str);
    cout << str;
    return 0;
}
