#include <iostream>

using namespace std;

void VInt(string& perv, int* arr, int i, int u)
{
    for (int j = 0; i < perv.size() - u; i++, j++)
    {
        if (perv[i] == '0')
        {
            arr[j] = 0;
        }
        else if (perv[i] == '1')
        {
            arr[j] = 1;
        }
        else if (perv[i] == '2')
        {
            arr[j] = 2;
        }
        else if (perv[i] == '3')
        {
            arr[j] = 3;
        }
        else if (perv[i] == '4')
        {
            arr[j] = 4;
        }
        else if (perv[i] == '5')
        {
            arr[j] = 5;
        }
        else if (perv[i] == '6')
        {
            arr[j] = 6;
        }
        else if (perv[i] == '7')
        {
            arr[j] = 7;
        }
        else if (perv[i] == '8')
        {
            arr[j] = 8;
        }
        else if (perv[i] == '9')
        {
            arr[j] = 9;
        }
        else if (perv[i] == 'A')
        {
            arr[j] = 10;
        }
        else {}
    }
}
char VChar(int i)
{
    char l = 'p';
    if (i == 0)
    {
        l = '0';
    }
    else if (i == 1)
    {
        l = '1';
    }
    else if (i == 2)
    {
        l = '2';
    }
    else if (i == 3)
    {
        l = '3';
    }
    else if (i == 4)
    {
        l = '4';
    }
    else if (i == 5)
    {
        l = '5';
    }
    else if (i == 6)
    {
        l = '6';
    }
    else if (i == 7)
    {
        l = '7';
    }
    else if (i == 8)
    {
        l = '8';
    }
    else if (i == 9)
    {
        l = '9';
    }
    else if (i == 10)
    {
        l = 'A';
    }
    return l;
}
int sravn(int* arr1, int* arr2, int I, int II)
{
    if (I > II)
        return 1;
    else if (I < II)
        return 2;
    else if (I == II)
    {
        for (int i = 0; i < I; i++)
        {
            if (arr1[i] == arr2[i]) {}
            else
            {
                if (arr1[i] > arr2[i])
                    return 1;
                else
                    return 2;
            }
        }
    }
}
void plusik(int* arr1, int* arr2, string& str3, string& str1, string& str2)
{
    int I = str1.size(), II = str2.size();
    for (int sum, razn = 0;; I--, II--)
    {
        sum = arr1[I] + arr2[II] + razn;
        razn = 0;
        if (sum < 11)
        {
            char l = VChar(sum);
            str3 += l;
        }
        else if (sum == 11)
        {
            str3 += "0";
            razn++;
        }
        else if (sum > 11)
        {
            sum = sum - 11;
            char l = VChar(sum);
            str3 += l;
            razn++;
        }
        if (II == 0)
        {
            I--;
            for (; I >= 0; I--)
            {
                sum = arr1[I] + razn;
                razn = 0;
                if (sum < 11)
                {
                    char l = VChar(sum);
                    str3 += l;
                }
                else if (sum == 11)
                {
                    str3 += "0";
                    razn++;
                }
                else if (sum > 11)
                {
                    sum = sum - 11;
                    char l = VChar(sum);
                    str3 += l;
                    razn++;
                }
            }
            break;
        }
        if (I == 0)
        {
            II--;
            for (; II >= 0; II--)
            {
                sum = arr2[II] + razn;
                razn = 0;
                if (sum < 11)
                {
                    char l = VChar(sum);
                    str3 += l;
                }
                else if (sum == 11)
                {
                    str3 += "0";
                    razn++;
                }
                else if (sum > 11)
                {
                    sum = sum - 11;
                    char l = VChar(sum);
                    str3 += l;
                    razn++;
                }
            }
            break;
        }
    }
}
void minusik(int* arr1, int* arr2, string& str3, string& str1, string& str2)
{
    int I = str1.size(), II = str2.size();
    for (int sum, razn = 0;; I--, II--)
    {
        int dlin = sravn(arr1, arr2, str1.size(), str2.size());
        if (dlin == 1)
        {
            if (razn == 1)
            {
                arr1[I] -= 1;
                razn = 0;
            }
            if (arr1[I] < arr2[II])
            {
                arr1[I] += 11;
                razn++;
            }
            sum = arr1[I] - arr2[II];
            char l = VChar(sum);
            str3 += l;

            if (II == 0)
            {
                I--;
                if (razn == 1)
                {
                    arr1[I] -= 1;
                    razn = 0;
                }
                for (; I >= 0; I--)
                {
                    char l = VChar(arr1[I]);
                    str3 += l;
                }
                break;
            }
        }
        else if (dlin == 2)
        {
            if (razn == 1)
            {
                arr2[II] -= 1;
                razn = 0;
            }
            if (arr2[II] < arr1[I])
            {
                arr2[II] += 11;
                razn++;
            }
            sum = arr2[II] - arr1[I];
            char l = VChar(sum);
            str3 += l;

            if (I == 0)
            {
                II--;
                if (razn == 1)
                {
                    arr2[II] -= 1;
                    razn = 0;
                }
                for (; II >= 0; II--)
                {
                    char l = VChar(arr2[II]);
                    str3 += l;
                }
                str3 += "-";
                break;
            }
        }
    }
}
void input(string& str)
{
    for (;;)
    {
        cin >> str;
        int prov = 0;
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == '1') {}
            else if (str[i] == '0') {}
            else if (str[i] == '2') {}
            else if (str[i] == '3') {}
            else if (str[i] == '4') {}
            else if (str[i] == '5') {}
            else if (str[i] == '6') {}
            else if (str[i] == '7') {}
            else if (str[i] == '8') {}
            else if (str[i] == '9') {}
            else if (str[i] == 'A' || str[i] == 'a') {}
            else if (str[i] == '-') {}
            else
            {
                prov++;
            }
        }
        if (prov == 0)
            break;
        else
            cout << "Ошибка ввода. Число должно быть представленно в одиннадцатиричной с/с.\nПвторрите попытку: ";
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    string str1, str2, str3;
    char znak;
    int arr1[1000];
    int arr2[1000];
    cout << "Введите первое число: ";
    input(str1);
    cout << "Введите второе число: ";
    input(str2);
    cout << "Выберите действие (+ или -): ";
    for (;;)
    {
        cin >> znak;
        if (znak == '+' || znak == '-')
            break;
        else
            cout << "Ошибка ввода. Введите знак арифметической операции (+ или -).\nПвторрите попытку: ";
    }
    cout << endl;
    if (str1[0] != '-' && str2[0] != '-' && znak == '-')
    {
        VInt(str1, arr1, 0, 0);
        VInt(str2, arr2, 0, 0);
        minusik(arr1, arr2, str3, str1, str2);
    }
    else if (str1[0] != '-' && str2[0] != '-' && znak == '+')
    {
        VInt(str1, arr1, 0, 0);
        VInt(str2, arr2, 0, 0);
        plusik(arr1, arr2, str3, str1, str2);
    }
    if (str1[0] != '-' && str2[0] == '-' && znak == '+')
    {
        str2.erase(0, 1);
        VInt(str1, arr1, 0, 0);
        VInt(str2, arr2, 0, 0);
        minusik(arr1, arr2, str3, str1, str2);
    }
    if (str1[0] != '-' && str2[0] == '-' && znak == '-')
    {
        str2.erase(0, 1);
        VInt(str1, arr1, 0, 0);
        VInt(str2, arr2, 0, 0);
        plusik(arr1, arr2, str3, str1, str2);
    }
    if (str1[0] == '-' && str2[0] != '-' && znak == '+')
    {
        str1.erase(0, 1);
        VInt(str1, arr1, 0, 0);
        VInt(str2, arr2, 0, 0);
        minusik(arr2, arr1, str3, str2, str1);
    }
    if (str1[0] == '-' && str2[0] == '-' && znak == '-')
    {
        str1.erase(0, 1);
        str2.erase(0, 1);
        VInt(str1, arr1, 0, 0);
        VInt(str2, arr2, 0, 0);
        minusik(arr2, arr1, str3, str2, str1);
    }
    if (str1[0] == '-' && str2[0] != '-' && znak == '-')
    {
        str1.erase(0, 1);
        VInt(str1, arr1, 0, 0);
        VInt(str2, arr2, 0, 0);
        plusik(arr1, arr2, str3, str1, str2);
        str3 += '-';
    }
    if (str1[0] == '-' && str2[0] == '-' && znak == '+')
    {
        str1.erase(0, 1);
        str2.erase(0, 1);
        VInt(str1, arr1, 0, 0);
        VInt(str2, arr2, 0, 0);
        plusik(arr1, arr2, str3, str1, str2);
        str3 += '-';
    }
    cout << "Результат вычислений: ";
    for (int i = str3.size(); i > 0; i--)
        cout << str3[i];
    return 0;
}