using System;
using System.Collections.Generic;

namespace LR_7.Entities
{
    public class Jornal
    {
        private List<string> _ticketJornal = new List<string>();
        private List<string> _passengerJornal = new List<string>();
        private List<string> _taxeJornal = new List<string>();

        public void ViewLog()
        {
            try
            {
                Console.Write("\nКакой журнал нужно просмотреть:\n1. Журнал изменения базы " +
                              "пассажиров\n2. Журнал изменения базы билетов\n3. Журнал изменения " +
                              "базы тарифов\n");
                int choose;
                do 
                    Console.Write("Ваш выбор: ");
                while (!int.TryParse(Console.ReadLine(), out choose));
                switch (choose)
                {
                    case 1:
                        for (int i = 0; i < _passengerJornal.Count; i++)
                            Console.WriteLine(_passengerJornal[i]);
                        break;
                    
                    case 2:
                        for (int i = 0; i < _ticketJornal.Count; i++)
                            Console.WriteLine(_ticketJornal[i]);
                        break;
                    
                    case 3:
                        for (int i = 0; i < _taxeJornal.Count; i++)
                            Console.WriteLine(_taxeJornal[i]);
                        break;
                    
                    default:
                        Console.Write("Неверный ввод.");
                        break;
                }
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
        
        public void ChTaxe(Taxe taxe, bool operation)
        {
            string record = "";
            if (operation)
                record = "\nДобавлен тариф:" + taxe.Info();
            else if (taxe != null) 
                record = "\nУдален тариф:" + taxe.Info();
            _taxeJornal.Add(record);    
        }
    }
}