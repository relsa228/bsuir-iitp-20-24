#include <iostream>
#include <Windows.h>
using namespace std;

int ed(string& str)
{
	for (size_t i = 0, prov = 0; i < str.size(); i++)
	{
		if (str[i] == '1')
		{
			prov = prov + 1;
		}
		else
		{
			return prov;
			break;
		}
	}
}

int fact(int num)
{
	int res = 1;
	for (int i = 1; i <= num; i++) 
	{
		res = res * i;
	}
	return res;
}

int schet(string& str)
{
	int res = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[ed(str)] == str[i])
		{
			res = res++;
		}
	}

	return res;
}

void Replace(string& str, char symbol)
{
	int rap = ed(str);
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == symbol)
			str[i] = '1';
	}
}

int main()
{
	string str;
	int div = 1;
	setlocale(LC_ALL, "Russian");
	cout << "Введите слово (не длинее 14 символов): ";
	cin >> str;
	cout << "\n";
	for (;;)
	{
		if (str.size() <= 14)
		{
			break;
		}
		else
		{
			cout << "Ошибка. Слово не должно быть длинее 14 символов. Повторите ввод: ";
			cin >> str;
			cout << "\n";
		}
	}
	for (int i = 0, sim; i < str.size(); i++)
	{
		//cout << str << endl;
		sim = schet(str);
		//cout << schet(str)<< endl;
		Replace(str, str[ed(str)]);
		div = div * fact(sim);
	}
	//cout << div << endl;
	cout << "Количество анаграмм к данному слову: " << fact(str.size()) / div;
}