#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int x, k = 0, i;
	cout << "Введите число: ";
	cin >> x;
	char* chislo = new char;
	for (i = 0; x > 0; i++, x /= 3)
	{
		chislo[i] = (x - (x / 3) * 3) % 3 + '0';
	}
	chislo[i] = 0;
	cout << "Результат перевода: ";
	for (int j = i - 1; j >= 0; j--)
		cout << chislo[j];
	return 0;
}