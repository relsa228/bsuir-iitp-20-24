#include <iostream>
using namespace std;
void PrintArray(int** arr, const int sqr1, const int sqr2)
{
	for (int j = 0; j < sqr1; j++)
	{
		for (int i = 0; i < sqr1; i++)
		{
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
}
void FillArray(int** arr, const int sqr1, const int sqr2)
{
	for (int i = 0; i < sqr1; i++)
	{
		for (int j = 0; j < sqr1; j++)
		{
			arr[i][j] = rand() % 10;
		}
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int sqr1;
	cout << "Введите размер квадратной матрицы: ";   
	cin >> sqr1;
	int sqr2 = sqr1;
	int** arr = new int* [sqr1];
	cout << "Первая матрица:" << endl;
	for (int i = 0; i < sqr1; i++)
		arr[i] = new int[sqr1];
	FillArray(arr, sqr1, sqr1);
	PrintArray(arr, sqr1, sqr1);
	cout << endl;
	cout << "Вторая матрица:" << endl;   
	int** array = new int* [sqr2];
	for (int i = 0; i < sqr2; i++)
		array[i] = new int[sqr2];
	FillArray(array, sqr1, sqr1);
	PrintArray(array, sqr1, sqr1);
	cout << endl;
	for (int i = 0, sqr3 = 0, max = 0, col = 0; i < sqr1; i++) 	
	{
		for (int j = 0, sqr4 = 0; j < sqr1; j++)
		{
			if (array[sqr4][sqr3] > max)
			{
				max = array[sqr4][sqr3];
			}
			else
				sqr4 = sqr4++;
		}
		for (int str = 0; str < sqr1; str++)
		{
			arr[str][col] = arr[str][col] * max;
		}
		sqr3 = sqr3++;
		col = col++;
		max = 0;
	}
	cout << endl;
	cout << "Новая матрица:" << endl; 	
	PrintArray(arr, sqr1, sqr1);
	for (int i = 0; i < sqr2; i++)
	{
		delete[] array[i];
	}
	delete[] array;
	for (int i = 0; i < sqr1; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
	return 0;
}