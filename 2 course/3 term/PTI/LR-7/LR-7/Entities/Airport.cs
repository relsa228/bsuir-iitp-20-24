using System;
using System.Collections.Generic;
using System.Linq;

namespace LR_7.Entities
{
    public delegate void BuyTicket();
    public delegate void TicketBaseChanging(Ticket ticket, bool operation); 
    public delegate void PassengerBaseChanging(Passenger passenger, bool operation); 
    public delegate void TaxeBaseChanging(Taxe taxe, bool operation); 
    
    public class Airport
    {
        public event BuyTicket OnBuy;
        public event PassengerBaseChanging OnPChanging;
        public event TicketBaseChanging OnTChanging;
        public event TaxeBaseChanging OnTaxeChanging;

        private Dictionary<string,Taxe> _taxeBase = new Dictionary<string,Taxe>();
        private List<string> _directionBase = new List<string>();
        private List<Passenger> _passengerBase = new List<Passenger>();
        private List<Ticket> _ticketBase = new List<Ticket>();
        
        private int _suitable;

        public Airport()
        {
            _suitable = 0;
        }
        
        public Passenger AirRegistration()
        {
            Passenger passenger = new Passenger();
                        
            Console.Write("\nЖелаете пройти регистрацию?\n1. Да, желаю\n2. Нет, " +
                          "я уже проходил регистрацию\n");
            int reg;
            do 
                Console.Write("Ваш выбор: ");
            while (!int.TryParse(Console.ReadLine(), out reg));
            
            switch (reg)
            {
                case 1:
                    passenger.Registration();
                    for (int i = 0; i < _passengerBase.Count; i++) 
                        if (_passengerBase[i].PassportNum == passenger.PassportNum) 
                        {
                            Console.Write("Такой пассажир уже зарегестрирован. Если вы этого не дел" +
                                              "али, обратитесь в техподдержку.");
                            return null;
                        }
                
                    _passengerBase.Add(passenger);
                    OnPChanging?.Invoke(passenger, true);
                    Console.Write("Ваши данные сохранены!\n");
                    return passenger;
                
                
                case 2:
                    Console.Write("\nВведите номер вашего паспорта: ");
                    string passport = Console.ReadLine(); 
                    for (int i = 0; i < _passengerBase.Count; i++) 
                        if (_passengerBase[i].PassportNum == passport) 
                        {
                            passenger = _passengerBase[i]; 
                            Console.Write("\nЗдравствуйте, " + passenger.FName + " " + passenger.SName + "!");
                            return passenger;
                        }
                    Console.Write("Совпадений в базе не найдено.\n");
                    return null;
                
                default:
                    Console.Write("Неверный ввод.\n");
                    return null;
            }
        }

        public void BuyTicket(Passenger passenger)
        {
            String finishPoint;
            
            Console.Write("\nВведите пункт назначения: ");
            finishPoint = Console.ReadLine();
                        
            Console.Write("\nВам подойдут следующие рейсы: ");
            for (int i = 0; i < _ticketBase.Count; i++)
                if (_ticketBase[i].FindSuitable(finishPoint))
                { 
                    Console.Write("\nНомер билета: " + i);
                    Console.WriteLine(_ticketBase[i].Info()); 
                    _suitable++;
                }

            if (_suitable == 0)
            {
                Console.Write("\nСожалеем, но подходящих рейсов не найдено.");
                return;
            }

            int indexTic;
            do 
                Console.Write("Ваш выбор: ");
            while (!int.TryParse(Console.ReadLine(), out indexTic));
            
            if (indexTic < _ticketBase.Count && indexTic >= 0)
            {
                Ticket temp = _ticketBase[indexTic];
                passenger.InPropertyTicket.Add(temp);
                OnBuy?.Invoke();
                return;
            }
                
            Console.Write("\nТакого билета нет в базе.");
        }

        public void Financial()
        {
            Console.Write("\nВыберите вариант:\n1. Для одного пассажира\n2. " +
                          "Сумма всех реализованных билетов\n3. Пассажир, заплативший максимальную сумму.\n" +
                          "4. Колличество пассажиров, заплативших больше определенной суммы\n5. Сколько потратил" +
                          " пассажир по каждому направлению.\n");
            int secondChoose;
            do 
                Console.Write("Ваш выбор: ");
            while (!int.TryParse(Console.ReadLine(), out secondChoose));
            Console.Write("\n");
            
            switch (secondChoose)
            {
                case 1:
                    int index;
                    do 
                        Console.Write("Индекс пассажира в списке: ");
                    while (!int.TryParse(Console.ReadLine(), out index));
                    
                    if (index < _passengerBase.Count && index >= 0)
                    {
                        Passenger temp = _passengerBase[index];
                        Console.Write("Данный пассажир купил билетов на сумму: " + temp.InPropertyTicket.Sum(n => n.Price)
                            + " рублей.");
                    }
                    else
                        Console.Write("Такого пассажира нет в базе.");
                    break;
                
                case 2:
                    float totalSum = _passengerBase.Sum(n => n.InPropertyTicket.Sum(ticket => ticket.Price));
                    Console.Write("\nСумма всех проданных билетов: " + totalSum + " рублей.");
                    break;
                
                case 3:
                    if (_passengerBase.Count != 0)
                    {
                        var result = from u in _passengerBase
                            orderby u.InPropertyTicket.Sum(t => t.Price) descending
                            select u;
                        Console.Write("\n" + result.First().FName + " " + result.First().SName);
                    }
                    else
                        Console.Write("\nСписок пассажиров пуст.");
                    break;

                case 4:
                    int sum;
                    do 
                        Console.Write("Введите сумму: ");
                    while (!int.TryParse(Console.ReadLine(), out sum));
                    
                    int totSum = _passengerBase.Aggregate(0, (proc, next) => next.InPropertyTicket.Sum(n 
                        => n.Price) > sum ? proc+1 : proc);
                    Console.Write("Пассажиров, заплативших больше: " + totSum);
                    break;
                
                case 5:
                    int pass;
                    do 
                        Console.Write("Номер пассажира в списке: ");
                    while (!int.TryParse(Console.ReadLine(), out pass));

                    if (pass < _passengerBase.Count && pass >= 0)
                    {
                        var directionGroup = _passengerBase[pass].InPropertyTicket
                            .GroupBy(p=>p.FinishPoint)
                            .Select(g=>new {Name=g.Key, Sum=g.Sum(t=>t.Price)});
                        
                        foreach (var group in directionGroup)
                            Console.WriteLine($"Направление: {group.Name}\nПотрачено: {group.Sum} рублей\n");
                        break;
                    }
                    else
                    {
                        Console.Write("Такого пассажира нет в базе.");
                        break;
                    }

                default:
                    Console.Write("Неверный ввод.");
                    break;
            }
        }

        public void ReturnTaxe()
        {
            Console.Write("\nСписок текущих тарифов (от дорогих к дешевым):");
            var result = from taxe in _taxeBase
                orderby taxe.Value.Price descending 
                select taxe;
            foreach (KeyValuePair<string, Taxe> taxe in result)
                Console.Write("\n"+taxe.Value.EndPoint+$" (Цена: {taxe.Value.Price})");
        }

        public void ChangeBase()
        {
            Console.Write("\nКакую базу необходимо изменить:\n1. Базу пассажиров\n2. Базу" +
                              " билетов\n3. Базу тарифов\n");
            int firstChoose;
            do 
                Console.Write("Ваш выбор: ");
            while (!int.TryParse(Console.ReadLine(), out firstChoose));
            
            switch (firstChoose)
            {
                case 1:
                    Console.Write("\nБаза пассажиров:\n");
                
                    for (int i = 0; i < _passengerBase.Count; i++)
                        if (_passengerBase[i] != null)
                            Console.WriteLine("\nНомер пассажира: " + i + _passengerBase[i].Info());
                
                    Console.Write("\n");
                    this.DeletePassanger();
                    break;
                
                case 2:
                    Console.Write("\nБаза билетов:\n");
                
                    for (int i = 0; i < _ticketBase.Count; i++)
                        Console.WriteLine("\nНомер билета: " + i + _ticketBase[i].Info());

                    Console.Write("\nЧто вы хотите сделать (выход - любое число, кроме 1 и 2):\n1. Добавить билет\n2. " +
                                  "Удалить" + " билет\n");
                    int secondChoose;
                    do 
                        Console.Write("Ваш выбор: ");
                    while (!int.TryParse(Console.ReadLine(), out secondChoose));
                    
                    if (secondChoose == 1)
                        this.AddTicket();
                    if (secondChoose == 2)
                        this.DeleteTicket();
                    break;
                    
                case 3:
                    Console.Write("\nБаза тарифов:\n");
                    
                    for (int i = 0; i < _taxeBase.Count; i++)
                        Console.WriteLine("\nНомер тарифа: " + i + _taxeBase[_directionBase[i]].Info());
                    
                    Console.Write("\nЧто вы хотите сделать (выход - любое число, кроме 1 и 2):\n1. Добавить тариф\n2. " +
                                  "Удалить" + " тариф\n");
                    int thirdChoose;
                    do 
                        Console.Write("Ваш выбор: ");
                    while (!int.TryParse(Console.ReadLine(), out thirdChoose));
                    
                    if (thirdChoose == 1)
                        this.AddTaxe();
                    if (thirdChoose == 2)
                        this.DeleteTaxe();
                    break;

                default:
                    Console.Write("Неверный ввод.");
                    break;
            }
        }
        
        private void AddTicket()
        {
            Ticket ticket = new Ticket();
            ticket.AddNewTicket();
            if (_taxeBase.Any(n => n.Key == ticket.FinishPoint))
            {
                Taxe taxe = _taxeBase[ticket.FinishPoint];
                ticket.Price = taxe.Price;
                _ticketBase.Add(ticket);
                OnTChanging?.Invoke(ticket, true);
                Console.Write("\nБилет добавлен.");
            }
            else
                Console.Write("\nДля данного напрвления нет тарифа");
        }

        private void AddTaxe()
        {
            Taxe taxe = new Taxe();
            taxe.AddTaxe(); 
            _directionBase.Add(taxe.EndPoint);
            _taxeBase.Add(taxe.EndPoint ,taxe);
            OnTaxeChanging?.Invoke(taxe, true);
            Console.Write("\nТариф добавлен.");
        }

        private void DeletePassanger()
        {
            int pass;
            do 
                Console.Write("Введите номер пассажира, которого нужно удалить: ");
            while (!int.TryParse(Console.ReadLine(), out pass));
            
            if (pass < _passengerBase.Count && pass >= 0)
            {
                Passenger passenger = _passengerBase[pass];
                OnPChanging(passenger, false);
                _passengerBase.Remove(_passengerBase[pass]);
                Console.Write("Удаление завершено.");
            }
            else
                Console.Write("Ошибка. Tакого пассажира нет в базе.");
        }
        
        private void DeleteTicket()
        {
            int tick;
            do 
                Console.Write("Введите номер билета, который нужно удалить: ");
            while (!int.TryParse(Console.ReadLine(), out tick));
            
            if (tick < _taxeBase.Count && tick >= 0)
            {
                Ticket ticket = _ticketBase[tick];
                OnTChanging?.Invoke(ticket, false);
                _ticketBase.Remove(_ticketBase[tick]);
                Console.Write("Удаление завершено.");
            }
            else
                Console.Write("Ошибка. Такого билета нет в базе.");
        }
        
        private void DeleteTaxe()
        {
            Console.Write("\nВведите направление, которое нужно удалить: ");
            string direct = Console.ReadLine();
            if (_taxeBase.Any(n => n.Key == direct) && _directionBase.Any(n => n == direct))
            {
                Taxe taxe = _taxeBase[direct];
                OnTaxeChanging?.Invoke(taxe, false);
                _taxeBase.Remove(direct);
                _directionBase.Remove(direct);
                Console.Write("Удаление завершено.");
            }
            else
                Console.Write("Ошибка. Такого тарифа не существует.");
        }
    }
}