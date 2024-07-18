using System;

namespace LR_7
{
    class Program
    {
        static void Main()
        {
           while (true)
            {
                Console.WriteLine("\nВыберите действие:");
                Console.WriteLine("1. Сравнить дроби\n2. Арифметические действия с дробями\n3. Конвертировать дробь\n4. Выйти");
                Console.Write("Ваш выбор: ");
                int chose = Convert.ToInt32(Console.ReadLine());
                switch (chose)
                {
                    case 1:
                        Fraction frEq1 = Fraction.Input("\nВведите первую дробь: ");
                        Fraction frEq2 = Fraction.Input("\nВведите вторую дробь: ");

                        if (frEq1 > frEq2)
                            Console.WriteLine(frEq1 + " больше чем " + frEq2);
                        else if (frEq1 < frEq2)
                            Console.WriteLine(frEq2 + " больше чем " + frEq1);
                        else if (frEq1 == frEq2)
                            Console.WriteLine("Дроби равны.");
                        break;
                    
                    case 2:
                        Fraction frAct1 = Fraction.Input("\nВведите первую дробь: ");
                        Fraction frAct2 = Fraction.Input("\nВведите вторую дробь: ");
                        
                        bool loop = true;
                        while (loop)
                        {
                            Console.WriteLine("\nКакое действие желаете совершить:");
                            Console.WriteLine("1. Сложение\n2. Вычитание\n3. Умножение\n4. Деление");
                            Console.Write("Ваш выбор: ");
                            int action = Convert.ToInt32(Console.ReadLine());
                            Fraction result;
                            switch (action)
                            {
                                case 1:
                                    result = frAct1 + frAct2; 
                                    Console.WriteLine("Результат: " + result);
                                    loop = false;
                                    break;

                                case 2:
                                    result = frAct1 - frAct2;
                                    Console.WriteLine("Результат: " + result);
                                    loop = false;
                                    break;

                                case 3:
                                    result = frAct1 * frAct2;
                                    Console.WriteLine("Результат: " + result);
                                    loop = false;
                                    break;

                                case 4:
                                    result = frAct1 / frAct2;
                                    Console.WriteLine("Результат: " + result);
                                    loop = false;
                                    break;
                                
                                default:
                                    Console.WriteLine("Выберите действительное действие");
                                    break;
                            }
                        }
                        break;
                    
                    case 3:
                        
                        Fraction frConvert = Fraction.Input("\nВведите конвертируемую дробь: ");

                        double frDoub = frConvert;
                        int frInt = frConvert;
                        
                        Console.Write("\nДробь в целочисленном представлении: " + frInt);
                        Console.Write("\nДробь в десятичном представлении: " + frDoub);
                        break;
                    
                    case 4:
                        return;
                    
                    default:
                        Console.WriteLine("Введите действительный номер действия.");
                        break;
                }
            }
        }
    }
}
