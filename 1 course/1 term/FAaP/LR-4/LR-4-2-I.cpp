#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	int array[4][3], prod = 1;
	setlocale(LC_ALL, "Russian");
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				array[i][j] = rand() % 200;
			}
		}
	}

	for (int i = 0, col = 0, str = 0, num = 1; i < 12; i++)
	{
		cout << array[str][col] << "\t";
		if (str == 3)
		{
			col = col++;
			str = 0;
			cout << endl;
		}
		else
			str = str++;
	}
	cout << endl;
	for (int j = 0, col = 0, str = 1; j < 2; j++)
	{
		if (array[col][str] > 0)
		{
			prod = prod * array[col][str];
			str = str++;
		}
		else
			str = str++;
	}
	if (array[1][2] > 0)
	{
		prod = prod * array[1][2];
	}
	cout << "Произведение равно: " << prod << endl;
	system("pause");
	return 0;
}
