#include <iostream>

using namespace std;

void VInt(string& perv, int* arr, int i, int u)
{
    for (int j = 0; i < perv.size() - u; i++)
    {
        if (perv[i] == '-')
            u--;                               //подозрительная хуйня
        else
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
            if (i == 1) {}
            else
                j++;
        }
    }
}

int ComVi(string& str)
{
    long double res = 0;
    int arr1[1000];
    int arr2[1];
    int y = str.size() - 6, u = 5;
    if (str[0] == '-')
    {
        y = str.size() - 7;
    }
    VInt(str, arr1, 0, u);
    for (int i = 0; i < y; i++)
    {
        long double step = pow(10, 0 - i);
        res = res + arr1[i] * step;
    };
    VInt(str, arr2, str.size() - 1, 0);
    res = res * pow(10, arr2[0]);
    if (str[0] == '-')
        res = 0 - res;
    return res;
}

int insize(int* arr)
{
    int res = 0;
    for (;;)
    {
        if (arr[res] == 2)
        {
            return res;
        }
        res++;
    }
}

void printArr(int* arr, int prov)
{
    if (insize(arr) < 7)
    {
        cout << prov << ".";
        for (int i = 0; i < 7 - insize(arr); i++)
            cout << "0";
        for (int i = insize(arr) - 1; i >= 0; i--)
            cout << arr[i];
    }
    else
    {
        cout << prov << ".";
        for (int i = insize(arr) - 1; i >= 0; i--)
            cout << arr[i];
    }
}

void perevodKod(int ch)
{
    int prov = 0;
    if (ch < 0)
    {
        prov = 1;
        ch = 0 - ch;
    }
    int arr[1000];
    for (int i = 0;; i++)
    {
        arr[i] = ch % 2;
        ch = ch / 2;
        if (ch == 0)
        {
            i++;
            arr[i] = 2;
            break;
        }
    }
    printArr(arr, prov);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    string str;
    cout << "Введите число в естественном виде (12 = 1.2*10^1): ";
    cin >> str;
    cout << "Прямой код числа: ";
    perevodKod(ComVi(str));
    return 0;
}