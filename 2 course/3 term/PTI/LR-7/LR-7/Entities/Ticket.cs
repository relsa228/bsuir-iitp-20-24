using System;

namespace LR_7.Entities
{
    public class Ticket : IComparable
    {
        public string FinishPoint;
        public float Price { get; set; }
        private string _bortNum;
        private string _date;
        public Ticket()
        {
            FinishPoint = "";
            Price = 0;
            _bortNum = "";
            _date = "";
        }

        public bool FindSuitable(string finishPoint)
        {
            if (this.FinishPoint == finishPoint)
                return true;
            return false;
        }

        public void AddNewTicket()
        {
            Console.Write("\nИнформация о билете\nВведите пункт назначения: ");
            this.FinishPoint = Console.ReadLine();
            Console.Write("Введите номер борта: ");
            this._bortNum = Console.ReadLine();
            Console.Write("Введите дату вылета (DD/MM/YYYY): ");
            this._date = Console.ReadLine();
        }

        public string Info()
        {
            string info = "\nНомер рейса: " + this._bortNum + "\nТочка прибытия: " + this.FinishPoint + "\nДата вылета: "
                          + this._date + "\nЦена билета: " + this.Price + " рублей";
            return info;
        }

        public int CompareTo(object obj)
        {
            Ticket temp = obj as Ticket;
            if (temp != null && temp.FinishPoint == this.FinishPoint && 
                temp._date == this._date && temp._bortNum == this._bortNum && temp.Price == this.Price)
                return 0;
            return 1;
        }
    }
}