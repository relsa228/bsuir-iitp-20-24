//доделать для 131
#include <iostream>
using namespace std;
void proverka3(int x)
{
	int y = 3;
	int i = x & y;
	cout << i;
	if (i == 3 || i==2|| i==1||i==0)
		cout << "true";
	else
		cout << "false";
}
void proverka61(int x)
{
	int y = 61, i, del = 61, j = 0;
	int prov = x & y;
	for (; j < 42; j++)
	{
		i = del & y;
		if (prov == i)
		{
			cout << "true";
			break;
		}
		del += 61;
	}
	cout << i;
	if (j == 42)
		cout << "false";
}
void proverka131(int x)
{
	int y = 131;
	int i = x & y;
	cout << i;
	if (i == 131 || i == 2 || i == 129|| i == 0)
		cout << "true";
	else if (i == 1 || i == 3 || i == 128 || i == 130)
		cout << "true";
	else
		cout << "false";
}


int main() 
{
	setlocale(LC_ALL, "Russian");
	int x;
	cout << "Введите число: ";
	cin >> x;
	cout << "Делимость на 3: ";
	proverka3(x);
	cout << endl;
	cout << "Делимость на 61: ";
	proverka61(x);
	cout << endl;
	cout << "Делимость на 131: ";
	proverka131(x);
	cout << endl;
	return 0;
}