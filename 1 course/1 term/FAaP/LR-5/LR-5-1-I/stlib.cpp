#include "stlib.h"
#include <iostream>
#include <math.h>

using namespace std;

double SumRow(int* arr, int len, int i, int one, int po)
{
	int  m = 0;
	for (int i = 1, y = i - 1; i - 1 < len; i++)
	{
		m = m + pow((arr[i - 1] - one), po);
	}
	return m;
}
void PrintArray(int* arr, const int sqr1)
{
	for (int i = 0; i < sqr1; i++)
	{
		cout << arr[i] << "   ";
	}
	cout << endl;
}