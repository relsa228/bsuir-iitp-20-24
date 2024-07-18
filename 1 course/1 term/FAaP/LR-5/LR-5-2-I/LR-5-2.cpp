#include <iostream>
#include <math.h>
#include "DLL.h"

using namespace std;


int main()
{
    setlocale(LC_ALL, "Russian");
    int str, prov = 0;
    cout << "Введите размерность ряда: ";
    cin >> str;
    int* arr = new int[str];
    FillArray(arr, str);
    cout << "Массив: " << endl;
    PrintArray(arr, str);
    cout << endl << "Синусы (соответсвенно): " << endl;
    for (int j = 0; j < str; j++)
    {
        cout << j + 1 << ".  " << sin(arr[j]) / 2 << endl;
    }
    PereborSchet(arr, str);
    for (int i = 0; i < str; i++)
    {
        if (arr[i] == (-1))
        {
            prov = prov++;
        }
    }
    cout << "Колличество элементов, выполняющих условие: " << prov;
    return 0;
}
