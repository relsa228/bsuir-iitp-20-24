using System;
using LR_7.Entities;

namespace LR_7
{
    class Program
    {
        static void Main()
        {
            Jornal jornal = new Jornal();
            Airport airport = new Airport();
            
            airport.OnBuy += () =>Console.WriteLine("Покупка зарегистрирована.");
            airport.OnPChanging += jornal.ChPassanger;
            airport.OnTChanging += jornal.ChTicket;
            airport.OnTaxeChanging += jornal.ChTaxe;
            
            bool work = true;
            while (work) 
            { 
                string exitChoose;
                Console.Write("\nВас приветствуют Российские Императорские авиалинии!\n\nВыберите действие:" +
                              "\n1. Купить билет\n2. Список тарифов\n3. Финансы\n4. " +
                              "Изменение базы\n5. Просмотр журнала\n6. Выход\n");
                int choose;
                do 
                    Console.Write("Ваш выбор: ");
                while (!int.TryParse(Console.ReadLine(), out choose));

                switch (choose)
                {
                    case 1:
                        Passenger passenger = airport.AirRegistration();
                        if (passenger != null)
                            airport.BuyTicket(passenger);
                        
                        Console.Write("\n\nПродолжить работу (Y/N): ");
                        exitChoose = Console.ReadLine();
                        if (exitChoose == "N") 
                            work = false;
                        break;
                    
                    case 2:
                        airport.ReturnTaxe();
                        Console.Write("\n\nПродолжить работу (Y/N): ");
                        exitChoose = Console.ReadLine();
                        if (exitChoose == "N") 
                            work = false;
                        break;
                    
                    case 3:
                        airport.Financial();
                        Console.Write("\n\nПродолжить работу (Y/N): ");
                        exitChoose = Console.ReadLine();
                        if (exitChoose == "N")
                            work = false;
                        break;
                    
                    case 4:
                        airport.ChangeBase();
                        Console.Write("\n\nПродолжить работу (Y/N): ");
                        exitChoose = Console.ReadLine();
                        if (exitChoose == "N")
                            work = false;
                        break;
                    
                    case 5:
                        jornal.ViewLog();
                        Console.Write("\n\nПродолжить работу (Y/N): ");
                        exitChoose = Console.ReadLine();
                        if (exitChoose == "N")
                            work = false;
                        break;
                    
                    case 6:
                        work = false;
                        break;
  
                    default:
                        Console.WriteLine("\nНеверный ввод.");
                        break;
                }
            }
        }
    }
}