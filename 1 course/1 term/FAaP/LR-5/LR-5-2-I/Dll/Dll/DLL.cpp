#include "pch.h"
#include <iostream>
#include <math.h>
#include "DLL.h"
using namespace std;

void PereborSchet(int* arr, int str)
{
    double x;
    x = sin(arr[str]) / 2;
    if (str == 0)
    {
        return;
    }
    else
    {
        if (x < 0)
        {
            arr[str] = (-1);
        }
        return PereborSchet(arr, str - 1);
    }
}

void PrintArray(int* arr, const int sqr1)
{
    for (int i = 0; i < sqr1; i++)
    {
        cout << arr[i] << "   ";
    }
}

void FillArray(int* arr, const int sqr1)
{
    for (int i = 0; i < sqr1; i++)
    {
        arr[i] = rand() % 20;
    }
}