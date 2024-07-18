using System;
using LR_4.Collections;

namespace LR_4.Entities
{
    public class Jornal
    {
        private MyCustomCollection<string> _ticketJornal = new MyCustomCollection<string>();
        private MyCustomCollection<string> _passengerJornal = new MyCustomCollection<string>();

        public void ViewLog()
        {
            try
            {
                Console.Write("\nКакой журнал нужно просмотреть:\n1. Журнал изменения базы " +
                              "пассажиров\n2. Журнал изменения базы билетов\nВаш выбор: ");
                int choose = Convert.ToInt32(Console.ReadLine());

                if (choose == 1)
                {
                    for (int i = 1; i <= _passengerJornal.Count; i++)
                        Console.WriteLine(_passengerJornal[i]);
                    return;
                }

                if (choose == 2)
                {
                    for (int i = 1; i <= _ticketJornal.Count; i++)
                        Console.WriteLine(_ticketJornal[i]);
                    return;
                }

                Console.WriteLine("Неверный ввод");
            }
            catch (FormatException e)
            {
                Console.WriteLine(e.Message);
            }
        }

        public void ChTicket(Ticket ticket, bool operation)
        {
            string record = "";
            if (operation)
                 record = "\nДобавлен билет:" + ticket.Info();
            else if (ticket != null)
                record = "\nУдален билет:" + ticket.Info();
            _ticketJornal.Add(record);   
        }
        
        public void ChPassanger(Passenger passenger, bool operation)
        {
            string record = "";
            if (operation)
                record = "\nДобавлен пассажир:" + passenger.Info();
            else if (passenger != null) 
                record = "\nУдален пассажир:" + passenger.Info();
            _passengerJornal.Add(record);    
        }
    }
}