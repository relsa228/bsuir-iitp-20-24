#include <iostream>

using namespace std;

void PrintArray(int** arr, const int sqr1, const int sqr2)
{
	for (int i = 0; i < sqr1; i++)
	{
		for (int j = 0; j < sqr2; j++)
		{
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
}

void swap(int** arr, int n, int a1, int a2)
{
	for (size_t i = 0; i < n; i++)
	{
		int buf = arr[a1][i];
		arr[a1][i] = arr[a2][i];
		arr[a2][i] = buf;
	}
}

int GetMaxElement(int** arr, int n, int index)
{
	int max = INT_MIN;
	for (size_t i = 0; i < n; i++)
	{
		if (arr[index][i] > max)
			max = arr[index][i];
	}
	return max;
}

void FillArray(int** arr, const int sqr1, const int sqr2)
{
	for (int i = 0; i < sqr1; i++)
	{
		for (int j = 0; j < sqr2; j++)
		{
			arr[i][j] = rand() % 200;
		}
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int str, col;
	cout << "Введите колличество строк: ";
	cin >> str;
	cout << "Введите колличество столбцов: ";
	cin >> col;
	int* array = new int[str];
	int** arr = new int* [str];
	for (int i = 0; i < str; i++)
	{
		arr[i] = new int[col];
	}
	FillArray(arr, str, col);
	cout << "\nИсходная матрица:" << endl;
	PrintArray(arr, str, col);
	cout << "\nИсправленная матрица:" << endl;
	for (int i = 1; i < str; i++)
		for (int j = 0; j < str - i; j++)
		{
			if (GetMaxElement(arr, col, j) > GetMaxElement(arr, col, j + 1))
				swap(arr, col, j, j + 1);
		}
	PrintArray(arr, str, col);
	for (int i = 0; i < str; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
	return 0;
}