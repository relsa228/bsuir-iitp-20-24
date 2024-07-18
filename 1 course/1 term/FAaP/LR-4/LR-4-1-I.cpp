#include <iostream>

using namespace::std;

int main()
{
	int i = 0, k1 = 0, prov = 0, k2 = 0;
	int array[7];
	setlocale(LC_ALL, "Russian");
	for (int j = 0, s = 0; j < 7; j++)
	{
		cout << "Введите элемент массива номер " << s + 1 << ": "; 
		cin >> array[s++];
		cout << "\n";
	}
	while (i < 7)
	{
		k2 = k1 + 1;
		if (array[k1] > array[k2])
		{
			prov++;
		}
		k1 = k1++;
		i = i++;
	}
	if (prov == 7)
	{
		cout << "\nЭлементы массива расположены в порядке убывания \n";
	}
	else
	{
		cout << "\nЭлементы массива не расположены в порядке убывания \n";
	}
	
	system("pause");
	return(0);
}


