#include <iostream>
using namespace std;
void PrintArray(int* arr, const int sqr1)
{
	for (int i = 0; i < sqr1; i++)
	{
		cout << arr[i] << "   ";
	}
	cout << endl;
}
void PrintBigArray(int** arr, const int sqr1, const int sqr2)
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
void MainLine(int** arr, int* array, int str)
{
	for (int i = 0, str1 = 0, col1 = 0, p = 0; i < str; i++)
	{
		p = arr[str1][col1];
		array[str1] = p;
		col1 = col1++;
		str1 = str1++;
	}
}
void EvenMembers(int* array, int str)
{
	for (int i = 0, str1 = 0; i < str; i++)
	{
		if (array[str1] % 2 == 0)
		{
			cout << array[str1] << "   ";
			str1 = str1++;
		}
		else
		{
			str1 = str1++;
		}
	}
}
void FillArray(int** arr, const int sqr1, const int sqr2)
{
	for (int i = 0, num = 0; i < sqr1; i++)
	{
		for (int j = 0; j < sqr2; j++)
		{
			cout << "Введите элемент номер " << num + 1 << ": ";
			cin >> arr[i][j];
			num = num++;
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
	int** arr = new int* [str];
	for (int i = 0; i < str; i++)
	{
		arr[i] = new int[col];
	}
	FillArray(arr, str, col);
	cout << "\nИсходный массив:" << endl;
	PrintBigArray(arr, str, col);
	if (col > str)
	{
		int* array1 = new int[str];
		MainLine(arr, array1, str);
		cout << "\nГлавная линия матрицы:" << endl;
		PrintArray(array1, str);
		cout << "\nЧетные элементы главной линия матрицы:" << endl;
		EvenMembers(array1, str);
		delete[] array1;
	}
	else
	{
		int* array2 = new int[col];
		MainLine(arr, array2, col);
		cout << "\nГлавная линия матрицы:" << endl;
		PrintArray(array2, col);
		cout << "\nЧетные элементы главной линия матрицы:" << endl;
		EvenMembers(array2, col);
		delete[] array2;
	}
	for (int i = 0; i < str; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
	return 0;
}