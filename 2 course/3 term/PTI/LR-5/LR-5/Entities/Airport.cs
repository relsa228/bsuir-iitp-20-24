using System;
using LR_4.Collections;

namespace LR_4.Entities
{
    public delegate void BuyTicket();
    public delegate void TicketBaseChanging(Ticket ticket, bool operation); 
    public delegate void PassengerBaseChanging(Passenger passenger, bool operation); 
    
    public class Airport
    {
        public event BuyTicket OnBuy;
        public event PassengerBaseChanging OnPChanging;
        public event TicketBaseChanging OnTChanging;

        private MyCustomCollection<Ticket> _ticketBase = new MyCustomCollection<Ticket>();
        private MyCustomCollection<Passenger> _passengerBase = new MyCustomCollection<Passenger>();
        
        private float _totalSum;
        private int _suitable;

        public Airport()
        {
            this._suitable = 0;
            this._totalSum = 0;
        }
        
        public Passenger AirRegistration()
        {
            Passenger passenger = new Passenger();
                        
            Console.Write("\nЖелаете пройти регистрацию?\n1. Да, желаю\n2. Нет, " +
                          "я уже проходил регистрацию\nВаш выбор: ");
            int reg = Convert.ToInt32(Console.ReadLine());
            
            if (reg == 1)
            {
                passenger.Registration();
                for (int i = 1; i <= _passengerBase.Count; i++) 
                    if (_passengerBase[i].PassportNum == passenger.PassportNum) 
                    {
                        Console.WriteLine("Такой пассажир уже зарегестрирован. Если вы этого не дел" +
                                          "али, обратитесь в техподдержку.");
                        return null;
                    }
                
                _passengerBase.Add(passenger);
                OnPChanging?.Invoke(passenger, true);
                Console.Write("Ваши данные сохранены!\n");
                return passenger;
            }
            
            if (reg == 2) 
            {
                Console.Write("\nВведите номер вашего пасспорта: ");
                string passport = Console.ReadLine(); 
                for (int i = 1; i <= _passengerBase.Count; i++) 
                    if (_passengerBase[i].PassportNum == passport) 
                    {
                        passenger = _passengerBase[i]; 
                        Console.Write("\nЗдравствуйте, " + passenger.FName + " " + passenger.SName + "!");
                        return passenger;
                    }
                Console.Write("Совпадений в базе не найдено.\n");
                return null;
            }

            Console.Write("Неверный ввод.\n");
            return null;
        }

        public void BuyTicket(Passenger passenger)
        {
            String finishPoint;
            Console.Write("\nВведите пункт назначения: ");
            finishPoint = Console.ReadLine();
                        
            Console.Write("\nВам подойдут следующие рейсы: ");
            for (int i = 1; i <= _ticketBase.Count; i++)
                if (_ticketBase[i].FindSuitable(finishPoint))
                { 
                    Console.Write("\nНомер билета: " + i);
                    Console.WriteLine(_ticketBase[i].Info()); 
                    _suitable++;
                }

            if (_suitable == 0)
            {
                Console.WriteLine("\nСожалеем, но подходящих рейсов не найдено.");
                return;
            }

            Console.Write("\nВаш выбор: ");
            int indexTic = Convert.ToInt32(Console.ReadLine());
            if (indexTic <= _ticketBase.Count)
            {
                Ticket temp = _ticketBase[indexTic]; 
                _totalSum += temp.Price;
                passenger.TotalSum += temp.Price;
                OnBuy?.Invoke();
                return;
            }
                
            Console.Write("\nТакого билета нет в базе.");
        }

        private void AddTicket()
        {
            Ticket ticket = new Ticket();
            ticket.AddNewTicket();
            _ticketBase.Add(ticket);
            OnTChanging?.Invoke(ticket, true);
            Console.Write("\nБилет добавлен.");
        }

        public void ReturnPrice()
        {
            Console.Write("\nВыберите вариант:\n1. Для одного пассажира\n2. " +
                          "Сумма всех реализованных билетов\nВаш выбор: ");
            int secondChoose = Convert.ToInt32(Console.ReadLine());
            if (secondChoose == 1)
            {
                Console.Write("\nИндекс пассажира в списке: ");
                int index = Convert.ToInt32(Console.ReadLine());
                if (index <= _passengerBase.Count)
                {
                    Passenger temp = _passengerBase[index];
                    Console.Write("Данный пассажир купил билетов на сумму: " + temp.TotalSum + " рублей.");
                }
                else
                    Console.Write("Такого пассажира нет в базе.");
            }
            else if (secondChoose == 2)
                Console.Write("\nСумма всех проданных билетов: " + _totalSum + " рублей.");
        }

        public void ChangeBase()
        {
            Console.Write("\nКакую базу необходимо изменить:\n1. Базу пассажиров\n2. Базу" +
                              " билетов\nВаш выбор: ");
            int firstChoose = Convert.ToInt32(Console.ReadLine());
            if (firstChoose == 1)
            {
                Console.Write("\nБаза пассажиров:\n");
                
                for (int i = 1; i <= _passengerBase.Count; i++)
                    if (_passengerBase[i] != null)
                        Console.Write("\nНомер пассажира: " + i + _passengerBase[i].Info() + "\n");
                
                Console.Write("\n");
                this.DeletePassanger();
                return;
            }
            if (firstChoose == 2)
            {
                Console.Write("\nБаза билетов:\n");
                
                for (int i = 1; i <= _ticketBase.Count; i++)
                    Console.Write("\nНомер билета: " + i + _ticketBase[i].Info() + "\n");
                
                Console.Write("\n");
                
                Console.Write("\nЧто вы хотите сделать:\n1. Добавить билет\n2. Удалить" +
                                  " билет\nВаш выбор: ");
                int secondChoose = Convert.ToInt32(Console.ReadLine());
                if (secondChoose == 1)
                {
                    this.AddTicket();
                    return;
                }
                if (secondChoose == 2)
                {
                    this.DeleteTicket();
                    return;
                }
            }
            Console.WriteLine("Неверный ввод.");
        }

        private void DeletePassanger()
        {
            Console.Write("Введите номер пассажира, которого нужно удалить: ");
            int pass = Convert.ToInt32(Console.ReadLine());
            Passenger passenger = _passengerBase[pass];
            OnPChanging(passenger, false);
            _passengerBase.Remove(_passengerBase[pass]);
            Console.WriteLine("Удаление завершено.");
        }
        
        private void DeleteTicket()
        {
            Console.Write("Введите номер билета, который нужно удалить: ");
            int tick = Convert.ToInt32(Console.ReadLine());
            Ticket ticket = _ticketBase[tick];
            OnTChanging?.Invoke(ticket, false);
            _ticketBase.Remove(_ticketBase[tick]);
            Console.WriteLine("Удаление завершено.");
        }
    }
}