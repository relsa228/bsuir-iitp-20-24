#include <iostream>
#include <math.h>
#include "stlib.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int len;
	double m = 0, D = 0;
	cout << "Введите размер массива: ";
	cin >> len;
	int* arr = new int [len];
	for (int i = 1, ct = 0; i < len + 1; i++)
	{
		if (i > 17)
			arr[i - 1] = sin(i);
		else
		{
			ct = 1 / tan(i);
			arr[i - 1] = pow(ct, 2);
		}
	}
	cout << endl << "Исходный массив:" << endl;
	PrintArray(arr, len);
	m = SumRow(arr, len, 1, 0, 1) / len;
	cout << endl << "Математическое ожидание равно: " << endl << m << endl;
	D = SumRow(arr, len, 1, m, 2) / len;
	cout << endl << "Дисперсия равна: " << endl << D << endl;
	delete[] arr;
	return 0;
}