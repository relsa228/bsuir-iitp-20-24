#include <iostream>
#include <math.h>

using namespace std;

int Funkchiya(int p, int q)
{
        int F = 0;
        if (p % 10 > 0)
            F = p % 10;
        else if (p == 0)
            F = 0;
        else
            F = p / 10;
        if (q == 0)
        {
            cout << F << "  ";
            return F;
        }
        cout << F << "  ";
        return F + Funkchiya(p + 1, q - 1);

}

int main()
{
    setlocale(LC_ALL, "Russian");
    int p, q, i;
    cout << "Введите p: ";
    cin >> p;
    cout << "Введите q: ";
    cin >> q;
    if (q < p)
    {
        cout << "Ошибка ввода, q не должен быть меньше p.";
        return 1;
    }
    i = q - p;
    cout << Funkchiya(p, i);
    return 0;
}

