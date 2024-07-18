#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

struct poezd
{
    int data;
    double otprav;
    int mesta;
    string fin;
};

int perebor(poezd* poezds, int den, string&city, int mest, double time, int* poz, int l)
{
    for (int i = 0; i < 4; i++)
    {
        if (poezds[i].data == den && poezds[i].fin == city && mest <= poezds[i].mesta && time <= poezds[i].otprav)
        {
            cout << endl << "Вам подойдет: " << endl;
            cout << "День отъезда: " << poezds[i].data << endl;
            cout << "Время отъезда: " << fixed << setprecision(2) << poezds[i].otprav << endl;
            cout << "Свободных мест: " << poezds[i].mesta << endl;
            cout << "Пункт назначения: " << poezds[i].fin << endl;
            cout << endl;
            poz[l] = i;
            l++;
        }
    }
    if (l == 0)
        cout << "К сожалению, в данный момент невозможно удовлетворить заказ в полном объеме.";
    return l;
}
void printArr(poezd* poezds, int j)
{
    for (int i = 0; i < j; i++)
    {
        cout << "День отъезда: " << poezds[i].data << endl;
        cout << "Время отъезда: " << fixed << setprecision(2) << poezds[i].otprav << endl;
        cout << "Свободных мест: " << poezds[i].mesta << endl;
        cout << "Пункт назначения: " << poezds[i].fin << endl;
        cout << endl;
    }
}
void zapis(int l, int* poz, poezd* poezds)
{
    ofstream fout("rezult.txt");
    fout << "Для клиента - Оргкомитет международной конференции" << endl;
    for (int i = 0; i < l; i++)
    {
        fout << "День отъезда: " << poezds[poz[i]].data << endl;
        fout << "Время отъезда: " << fixed << setprecision(2) << poezds[poz[i]].otprav << endl;
        fout << "Свободных мест: " << poezds[poz[i]].mesta << endl;
        fout << "Пункт назначения: " << poezds[poz[i]].fin << endl;
        fout << endl;
    }
    fout.close();
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int den, mest, l = 0;
    double time, prov, a;
    string city, answer;
    int poz[4];
    poezd poezds[4];

    ifstream fin("poezd.txt");
    if (!fin.is_open())
        cout << "Ошибка открытия файла.";
    else
    for (int i = 0; i < 4; i++)
    {
        fin >> poezds[i].data;
        fin >> poezds[i].otprav;
        fin >> poezds[i].mesta;
        fin >> poezds[i].fin;
    }
    cout << "Желаете вывести на экран полное расписание?" << endl;
    for (;;)
    {
        cin >> answer;
        if (answer == "Yes")
        {
            printArr(poezds, 4);
            break;
        }
        else if (answer == "No")
            break;
        else
            cout << "Введите Yes или No." << endl;
    }
    for (;;)
    {
        cout << "Введите день, на который нужны билеты: ";
        cin >> den;
        if (den > 0 && den < 8)
            break;
        else
            cout << "Ошибка. Введите число от 1 до 7 включительно.";
    }
    for (;;)
    {
        cout << "Введите время, на которое нужны билеты: ";
        cin >> time;
        prov = modf(time, &a);
        if (time > 24)
            cout << "Ошибка ввода. Формат ввода - 13.10" << endl;
        else if (prov > 0.59)
            cout << "Ошибка ввода. Формат ввода - 13.10" << endl;
        else
            break;
    }
    cout << "Введите необходимое количество мест: ";
    cin >> mest;
    cout << "Введите город, в который вы хотите поехать: ";
    cin >> city;
    l = perebor(poezds, den, city, mest, time, poz, l);
    zapis(l, poz, poezds);
    fin.close();

    return 0;
}

