#include <iostream>

using namespace std;

int insize(int* arr)
{
    int res = 0;
    for (;;)
    {
        if (arr[res] == 20)
        {
            return res;
        }
        res++;
    }
}

void PerevodVInt(string& perv, int* arr)
{
    for (int i = 0, j = 0; i < perv.size(); i++)
    {
        if (perv[i] == '1')
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
        else if (perv[i] == 'A' || perv[i] == 'a')
        {
            arr[j] = 10;
        }
        j++;
    }
}

int perevod10(int* arr, int sys, int size)
{
    int res = 0, sch = size;
    for (int i = 0; i < size; i++)
    {
        res += arr[i] * pow(sys, sch - 1);
        sch--;
    }
    return res;
}

void perevod8(string& perv)
{
    int res, i = 0, osnov = 7;
    int arr2[1000];
    int* arr = new int[perv.size()];
    PerevodVInt(perv, arr);
    res = perevod10(arr, 11, perv.size());
    if (res < 0)
    {
        cout << "-";
    }
    for (;;)
    {

        if (res < 0)
        {
            arr2[i] = abs(res) % osnov;
            res = abs(res) / osnov;
        }
        else
        {
            arr2[i] = res % osnov;
            res = res / osnov;
        }
        i++;
        if (res == 0)
        {
            arr2[i] = 20;
            break;
        }
    }
    int j = insize(arr2) - 1;
    for (;;)
    {
        cout << arr2[j];
        if (j == 0)
            break;
        j--;
    }
}

int proverka(string& perv)
{
    for (int i = 0; i < perv.size(); i++)
    {
        int prov = 0;
        if (perv[i] == '1') {}
        else if (perv[i] == '2') {}
        else if (perv[i] == '3') {}
        else if (perv[i] == '4') {}
        else if (perv[i] == '5') {}
        else if (perv[i] == '6') {}
        else if (perv[i] == '7') {}
        else if (perv[i] == '8') {}
        else if (perv[i] == '9') {}
        else if (perv[i] == 'A' || perv[i] == 'a') {}
        else
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    string perv;
    for (;;)
    {
        cout << "Введите число в одиннадцатиричной с/с: ";
        cin >> perv;
        cout << endl;
        if (proverka(perv) == 1)
            break;
        cout << "Ошибка. Число не в одиннадцатиричной с/с. Повторите ввод." << endl;
    }
    cout << "Число в семиричной с/с: ";
    perevod8(perv);
    return 0;
}
