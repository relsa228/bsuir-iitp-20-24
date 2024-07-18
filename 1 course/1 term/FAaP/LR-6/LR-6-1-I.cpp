#include <iostream>
#include <string>

using namespace std;

void chet(char* str, int i)
{
    for (int j = 0, num = 0; j < i; j++)
    {
        if (str[j] == str[j + 1])
        {
            num = num++;
        }
        else
        {
            if (num > 0 && num % 2 != 0)
            {
                //cout << "\n nacalo       " << num << "     konec    \n";
                for (int i = 0, dop = j; i <= num; i++)
                {
                    cout << str[dop - num];
                    dop = dop++;
                }
                cout << "\t";
            }
            num = 0;
        }
    }
}

void printArr(char* str, int i)
{
    for (int j = 0; j < i; j++)
    {
        cout << str[j];
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int sim;
    cout << "Введите количество элементов: ";
    cin >> sim;
    char* str = new char[sim];
    cout << "Введите элементы (только 0 и 1): ";
    for (int j = 0; j < sim; j++)
    {
        m:
        cin >> str[j];
        if (str[j] != '1' && str[j] != '0')
        {
            cout << "Ошибка. Символ номер " << j + 1 << " не равен 0 или 1" << endl;
            goto m;
        }
    }
    cout << "Строка: ";
    printArr(str, sim);
    cout << endl << "Четные группы: ";
    chet(str, sim);
    delete[] str;
    return 0;
}
