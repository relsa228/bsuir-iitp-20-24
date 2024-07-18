// ввод - два двоичных числа в естественной форма (т.е. со знаком, как -101 или +101)
#include <iostream>

using namespace std;

void inputStr(string& str) //ввод с проверкой
{
    for (;;)
    {
        cin >> str;
        int prov = 0;
        for (int i = 1; i < str.size(); i++)
        {
            if (str[i] != '0' && str[i] != '1')
                prov++;
        }
        if (prov == 0)
        {
            if (str[0] == '-' || str[0] == '+')
                break;
            else
                cout << "Ошибка ввода. Повторите попытку (формат ввода - +101 или -101): ";
        }
        else
            cout << "Ошибка ввода. Повторите попытку (формат ввода - +101 или -101): ";
    }
}
void obratnoe(string& str) //перевод в обратный код
{
    if (str[0] == '-')
    {
        for (int i = 1; i < str.size(); i++)
        {
            if (str[i] == '1')
                str[i] = '0';
            else
                str[i] = '1';
        }
        str[0] = '1';
    }
    else
        str[0] = '0';
}
void plusik(string& str, string& str2, string& str3, int pl) //сложение в обратном коде
{
    for (int poz = str.size(); poz >= 0; poz--)
    {
        if (str[poz] == '1' && str2[poz] == '0')
        {
            if (pl == 0)
                str3[poz] = '1';
            else
                str3[poz] = '0';
        }
        else if (str[poz] == '0' && str2[poz] == '1')
        {
            if (pl == 0)
                str3[poz] = '1';
            else
                str3[poz] = '0';
        }
        else if (str[poz] == '1' && str2[poz] == '1')
        {
            if (pl == 1)
                str3[poz] = '1';
            else
            {
                str3[poz] = '0';
                pl++;
            }
        }
        else if (str[poz] == '0' && str2[poz] == '0')
        {
            if (pl == 0)
                str3[poz] = '0';
            else
            {
                str3[poz] = '1';
                pl--;
            }
        }
        if (poz == 0 && pl == 1)
        {
            for (int i = str3.size() - 1;; i--)
            {
                if (str3[i] == '0')
                {
                    str3[i] = '1';
                    break;
                }
                else if (str3[i] == '1')
                {
                    str3[i] = '0';
                }
            }
        }
    }
}
void pryamoe(string& str3) //перевод в прямой код
{
    str3.insert(1, ".");
    for (int i = 2; i < str3.size(); i++)
    {
        if (str3[i] == '1')
            str3[i] = '0';
        else
            str3[i] = '1';
    }
}
void bitty(string& str) //переводит числа в битный формат
{

    if (str.size() % 8 != 0)
    {
        for (int i = 0;; i++)
        {
            str.insert(1, "0");
            if (str.size() % 8 == 0)
                break;
        }
    }
}
void uravn(string& str, string& str1) //делает оба числа равными друг-другу по длине
{
    int a = str.size(), b = str1.size();
    if (a > b)
    {
        int razn = a - b;
        for (int i = 0; i < razn; i++)
        {
            str1.insert(1, "0");
        }
    }
    else if (b > a)
    {
        int razn = b - a;
        for (int i = 0; i < razn; i++)
        {
            str.insert(1, "0");
            int a = str.size(), b = str1.size();
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    string str, str2, str3;
    cout << "Введите первое число: ";
    inputStr(str);
    cout << "Введите второе число: ";
    inputStr(str2);
    bitty(str);
    bitty(str2);
    uravn(str, str2);
    obratnoe(str);
    obratnoe(str2);
    for (int i = 0; i < str.size(); i++)
        str3 += "0";
    plusik(str, str2, str3, 0);
    if (str3[0] == '1')
        pryamoe(str3);
    else
        str3.insert(1, ".");
    cout << "Результат сложения: ";
    for (int i = 0; i < str3.size(); i++)
        cout << str3[i];
    return 0;
}