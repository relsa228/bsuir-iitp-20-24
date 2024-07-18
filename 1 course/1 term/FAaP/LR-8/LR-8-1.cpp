#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <windows.h>

using namespace std;

struct bus
{
    int num;
    string type;
    string finpoint;
    double otprav;
    double prib;
};
void printArr(bus* buses, int num)
{
    for (int i = 0; i < num; i++)
    {
        cout << "Номер автобуса: " << buses[i].num << endl;
        cout << "Тип автобуса: " << buses[i].type << endl;
        cout << "Пункт назначения: " << buses[i].finpoint << endl;
        cout << "Время отправки: " << fixed << setprecision(2) << buses[i].otprav << endl;
        cout << "Время прибытия: " << fixed << setprecision(2) << buses[i].prib << endl << endl;

    }
}
void fillarray(bus* buses)
{
    buses[0].num = 228;
    buses[1].num = 1337;
    buses[2].num = 256;
    buses[3].num = 54;
    buses[4].num = 7;
    buses[5].num = 410;

    buses[0].type = "междугородний";
    buses[1].type = "междугородний";
    buses[2].type = "междугородний";
    buses[3].type = "междугородний";
    buses[4].type = "междугородний";
    buses[5].type = "междугородний";

    buses[0].finpoint = "Leninsk";
    buses[1].finpoint = "Cherepovec";
    buses[2].finpoint = "Leninsk";
    buses[3].finpoint = "Samara";
    buses[4].finpoint = "Cherepovec";
    buses[5].finpoint = "Sovenok";

    buses[0].otprav = 6.14;
    buses[1].otprav = 8.30;
    buses[2].otprav = 8.30;
    buses[3].otprav = 14.25;
    buses[4].otprav = 16.40;
    buses[5].otprav = 10.35;

    buses[0].prib = 15.30;
    buses[1].prib = 16.30;
    buses[2].prib = 14.30;
    buses[3].prib = 22.43;
    buses[4].prib = 0.40;
    buses[5].prib = 18.43;
}
void sortirovka(bus* buses, string& city, double time)
{
    bus buses2[6];
    int j = 0;
    bus vrem;
    for (int i = 0; i < 6; i++)
    {
        if (buses[i].finpoint == city)
        {
            if (buses[0].prib < time)
            {
                buses2[j] = buses[i];
                j++;
            }
        }
    }
    if (j == 0)
        cout << "Извините, на данный момент ни одного подходящего рейса не найдено." << endl;
    else if (j == 1)
    {
        cout << "Вот подходящие результаты: " << endl << endl;
        printArr(buses2, 1);
    }
    else
    {
        cout << endl << "Вот подходящие результаты: " << endl << endl;
        double per = buses2[0].prib;
        int raz = j;
        for (int i = 0; i < j--; i++)
        {
            int indx = i;
            for (int j = i; j < j; j++)
            {
                if (buses2[j].prib > buses2[i].prib)
                {
                    indx = j;
                }
            }
            if (indx != i)
            {
                vrem = buses2[i];
                buses2[i] = buses2[indx];
                buses2[indx] = vrem;
            }
        }
        printArr(buses2, raz);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    string answer, city;
    double time, prov, a;
    bus buses[6];
    fillarray(buses);
    cout << "Желаете вывести на экран полное расписание?" << endl;
    for (;;)
    {
        cin >> answer;
        if (answer == "Yes")
        {
            printArr(buses, 6);
            break;
        }
        else if (answer == "No")
            break;
        else
            cout << "Введите Yes или No." << endl;
    }
    cout << "Введите название пункта назначения: ";
    cin >> city;
    for (;;)
    {
        cout << "До какого времени вам необходимо туда добраться: ";
        cin >> time;
        prov = modf(time, &a);
        if (time > 24)
            cout << "Ошибка ввода. Формат ввода - 13.10" << endl;
        else if (prov > 0.59)
            cout << "Ошибка ввода. Формат ввода - 13.10" << endl;
        else
            break;
    }
    sortirovka(buses, city, time);
    return 0;
}
