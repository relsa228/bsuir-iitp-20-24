using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mnemonic
{
    internal class Program 
    {
        class Field
        {
            public int[,] numfield = new int[6, 6];
            public int[,] nullfield = new int[6, 6];

            public static void PrintField(int[,] nullfield)
            {
                for (int i = 0; i < 6; i++)
                {
                    Console.Write("\n\t\t|");
                    for (int j = 0; j < 6; j++)
                    {
                        Console.Write("\t"+ nullfield[j, i]);
                    }
                    Console.Write("\t|" + "\n\n");
                }
            }

            public static void FillNull(int[,] nullfield, int[,] numfield)
            {
                for (int i = 0; i < 6; i++)
                {
                    for (int j = 0; j < 6; j++)
                    {
                        nullfield[i, j] = 0;
                        numfield[i, j] = 0;
                    }
                }
            }

            public static void FillNum(int[,] numfield)
            {
                for (int i = 2; i < 20; i++)
                {
                    for (int j = 0; ;)
                    {
                        Random rnd = new Random();
                        int str = rnd.Next(0, 6);
                        int col = rnd.Next(0, 6);
                        if (numfield[str, col] == 0)
                        {
                            numfield[str, col] = i;
                            j++;
                        }

                        if (j == 2)
                            break;
                    }
                }
            }

            public static int CheckCouple(int[,] nullfield)
            {
                int check = 0;
                for (int i = 0; i < 6; i++)
                {
                    for (int j = 0; j < 6; j++)
                    {
                        if (nullfield[i, j] != 0)
                            if (nullfield[i, j] != 1)
                                check++;
                    }
                }
                return check;
            }

            public static int Win(int[,] nullfield)
            {
                int check = 0;
                for (int i = 0; i < 6; i++)
                {
                    for (int j = 0; j < 6; j++)
                    {
                        if (nullfield[i, j] != 1)
                            check++;
                    }
                }
                return check;
            }
        }

        public static void Main(string[] args)
        {
            Field GameField = new Field();
            Field.FillNull(GameField.numfield, GameField.nullfield);
            Field.FillNum(GameField.numfield);
            for (int score = 0; ;)
            {
                if (Field.Win(GameField.nullfield) == 0)
                {
                    Console.WriteLine("O_O------------------------------------O_o");
                    Console.WriteLine("\n\tПоздравляю! Вы выиграли!");
                    Console.Write("\tКолличество ваших ходов: " + (score / 2));
                    Console.WriteLine("\n\nO_o------------------------------------O_O");
                    Console.WriteLine("\nЖелаете сыграть еще раз? (Да - ENTER, Нет - Esc)");
                    var key = Console.ReadKey();
                    if (key.Key == ConsoleKey.Enter)
                    {
                        Field.FillNull(GameField.numfield, GameField.nullfield);
                        Field.FillNum(GameField.numfield);
                        Console.Clear();
                    }
                    else if (key.Key == ConsoleKey.Escape)
                        break;
                }

                int col, str = 0;
                Console.WriteLine("\t\t\t\t\tМнемоник");
                Console.WriteLine("\nИщите пары чисел, которые спрятаны на поле (0 - клетка еще не разгадана, 1 - пара найдена)\n");
                Console.WriteLine("\t\tOwO–––––––––––––––––––––––––––––––––––––––––––––––––––OwO");
                Field.PrintField(GameField.nullfield);
                Console.WriteLine("\t\tOwO–––––––––––––––––––––––––––––––––––––––––––––––––––OwO\n");
                if (Field.CheckCouple(GameField.nullfield) == 2)
                {
                    int[] num = new int[6];
                    for (int i = 0; i < 6; i++)
                    {
                        for (int j = 0; j < 6; j++)
                        {
                            if (GameField.nullfield[i, j] != 0)
                                if (GameField.nullfield[i, j] != 1)
                                {
                                    num[str] = GameField.nullfield[i, j];
                                    str++;
                                    num[str] = i;
                                    str++;
                                    num[str] = j;
                                    str++;
                                }
                        }
                    }
                    if (num[0] == num[3])
                    {
                        Console.Write("Пара найдена. Поздравляю!");
                        GameField.nullfield[num[1], num[2]] = 1;
                        GameField.nullfield[num[4], num[5]] = 1;
                    }
                    else
                    {
                        Console.Write("Пара не найдена.");
                        GameField.nullfield[num[1], num[2]] = 0;
                        GameField.nullfield[num[4], num[5]] = 0;
                    }
                    Console.ReadKey();
                    Console.Clear();
                }
                else
                {
                    Console.Write("Введите номер строки: ");
                    col = Convert.ToInt32(Console.ReadLine());
                    Console.Write("Введите номер клетки в строке: ");
                    str = Convert.ToInt32(Console.ReadLine());
                    int check;
                    if (str < 7 && col < 7)
                        if (str > 0 && col > 0)
                            check = 0;
                        else
                            check = 1;
                    else
                        check = 1;
                    if (check == 1)
                        Console.Write("\nОшибка ввода.");
                    else
                    {
                        if (GameField.nullfield[(str - 1), (col - 1)] == 0)
                            GameField.nullfield[(str - 1), (col - 1)] = GameField.numfield[(str - 1), (col - 1)];
                        else
                            Console.Write("\nЭта клетка уже активна. Выберите другую.");
                    }
                    score++;
                    Console.ReadKey();
                    Console.Clear();
                }
            }
        }
    }
}
