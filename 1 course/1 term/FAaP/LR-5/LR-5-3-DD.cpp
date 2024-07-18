#include <iostream>
#include <math.h>
using namespace std;
int greatest(int n)
{
    int lmao = n;
    for (int i = 0, ost = 0; i < n; i++)
    {
        if (n % lmao == 0 && lmao % 2 == 1)
        {
            break;
        }
        else
            lmao = lmao--;
    }
    return lmao;
}

int sum(int n, int fir)
{
    if (fir != n)
    return greatest(fir) + sum(n, fir + 1);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int n, del = 0;
    cout << "Введите число N: ";
    cin >> n;
    if (n < pow(10, 9))
    {
        cout << "Сумма ряда: " << sum(n, 1);
    }
    else
    {
        cout << "Ошибка ввода. Чило N должно быть меньше, чем 10^9." << endl;;
    }
    return 0;
}

