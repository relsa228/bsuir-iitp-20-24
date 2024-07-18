#include <iostream>

using namespace std;
void PrintArray(int** arr, const int str, const int col)
{
    for (int i = 0; i < str; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

int main()
{
    int i = 0, j, k = 0, p = 1, str, col;
    setlocale(LC_ALL, "Russian");
    cout << "Введите колличество строк: ";
    cin >> str;
    cout << "Введите количество столбцов: ";
    cin >> col;
    int** arr = new int* [str];
    for (int i = 0; i < str; i++)
    {
        arr[i] = new int[col];
    }

    while (i < col * str) 
    {
        k++;
        for (j = k - 1; j < col - k + 1; j++)
        {
            arr[k - 1][j] = p++;
            i++;
        }  

        for (j = k; j < str - k + 1; j++)
        {
            arr[j][col - k] = p++;
            i++;
        }  

        for (j = col - k - 1; j >= k - 1; j--)
        {
            arr[str - k][j] = p++;
            i++;
        }  

        for (j = str - k - 1; j >= k; j--)
        {
            arr[j][k - 1] = p++;
            i++;
        }   

    }
    PrintArray(arr, str, col);

    return(0);
}