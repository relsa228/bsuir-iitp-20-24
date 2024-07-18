using System;
using LR_4.Entities;

namespace LR_4
{
    class Program
    {
        static void Main()
        {
            try
            {
                Jornal jornal = new Jornal();
                Airport airport = new Airport();

                airport.OnBuy += () => Console.WriteLine("Покупка зарегистрирована.");
                airport.OnPChanging += jornal.ChPassanger;
                airport.OnTChanging += jornal.ChTicket;

                bool work = true;
                while (work)
                {
                    string exitChoose;

                    Console.Write("\nВас приветствуют Российские Императорские авиалинии!\n\nВыберите действие:" +
                                  "\n1. Купить билет\n" + "2. Сумма всех купленных билетов\n3. Изменение базы" +
                                  "\n4. Просмотр журнала\n5. Выход\nВаш выбор: ");
                    int choose = Convert.ToInt32(Console.ReadLine());

                    switch (choose)
                    {
                        case 1:
                            Passenger passenger = airport.AirRegistration();
                            if (passenger != null)
                                airport.BuyTicket(passenger);

                            Console.Write("\nПродолжить работу (Y/N): ");
                            exitChoose = Console.ReadLine();
                            if (exitChoose == "N")
                                work = false;
                            break;

                        case 2:
                            airport.ReturnPrice();
                            Console.Write("\nПродолжить работу (Y/N): ");
                            exitChoose = Console.ReadLine();
                            if (exitChoose == "N")
                                work = false;
                            break;

                        case 3:
                            airport.ChangeBase();
                            Console.Write("\nПродолжить работу (Y/N): ");
                            exitChoose = Console.ReadLine();
                            if (exitChoose == "N")
                                work = false;
                            break;

                        case 4:
                            jornal.ViewLog();
                            Console.Write("\nПродолжить работу (Y/N): ");
                            exitChoose = Console.ReadLine();
                            if (exitChoose == "N")
                                work = false;
                            break;

                        case 5:
                            work = false;
                            break;

                        default:
                            Console.WriteLine("\nНеверный ввод.");
                            break;
                    }
                }
            }
            catch (FormatException e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}