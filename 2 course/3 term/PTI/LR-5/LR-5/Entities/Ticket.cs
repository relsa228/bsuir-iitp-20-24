using System;

namespace LR_4.Entities
{
    public class Ticket : IComparable
    {
        private string _startPoint;
        private string _finishPoint;
        public float Price { get; set; }
        private string _bortNum;
        private string _date;
        public Ticket()
        {
            _startPoint = "Национальный Императорский аэропорт России";
            _finishPoint = "";
            Price = 0;
            _bortNum = "";
            _date = "";
        }

        public bool FindSuitable(string finishPoint)
        {
            if (this._finishPoint == finishPoint)
                return true;
            return false;
        }

        public void AddNewTicket()
        {
            Console.Write("\nИнформация о билете\nВведите пункт прибытия: ");
            this._finishPoint = Console.ReadLine();
            Console.Write("Введите номер борта: ");
            this._bortNum = Console.ReadLine();
            Console.Write("Введите дату вылета (DD/MM/YYYY): ");
            this._date = Console.ReadLine();
            Console.Write("Введите цену билета: ");
            this.Price = Convert.ToSingle(Console.ReadLine());
        }

        public string Info()
        {
            string info = "\nНомер рейса: " + this._bortNum + "\nТочка отправления: " + this._startPoint +
                          "\nТочка прибытия: " + this._finishPoint + "\nДата вылета: " + this._date
                          + "\nЦена билета: " + this.Price + " рублей";
            return info;
        }

        public int CompareTo(object obj)
        {
            Ticket temp = obj as Ticket;
            if (temp != null && temp._startPoint == this._startPoint && temp._finishPoint == this._finishPoint && 
                temp._date == this._date && temp._bortNum == this._bortNum && temp.Price == this.Price)
                return 0;
            return 1;
        }
    }
}