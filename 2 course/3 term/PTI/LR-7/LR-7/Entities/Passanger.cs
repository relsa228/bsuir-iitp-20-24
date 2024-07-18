using System;
using System.Collections.Generic;

namespace LR_7.Entities
{
    public class Passenger: IComparable
    {
        public string FName { get; set; }
        public string SName { get; set; }
        private string _citizenship;
        private string _gender;
        public string PassportNum { get; set; }
        public List<Ticket> InPropertyTicket;
        
        public Passenger()
        {
            InPropertyTicket = new List<Ticket>();
            FName = "";
            SName = "";
            _citizenship = "";
            _gender = "";
            PassportNum = "";
        }

        public void Registration()
        {
            Console.Write("\nВаши паспортные данные\nВведите ваше имя: "); 
            this.FName = Console.ReadLine(); 
            Console.Write("Введите вашу фамилию: ");
            this.SName = Console.ReadLine();
            Console.Write("Введите ваш пол: ");
            this._gender = Console.ReadLine();
            Console.Write("Введите ваше гражданство: ");
            this._citizenship = Console.ReadLine();
            Console.Write("Введите номер вашего паспорта: ");
            this.PassportNum = Console.ReadLine();
        }

        public string Info()
        {
            string info = "\nИмя: " + this.FName + "\nФамилия: " + this.SName +
                          "\nПол: " + this._gender + "\nГражданство: " + this._citizenship
                          + "\nНомер паспорта: " + this.PassportNum;
            return info;
        }
        
        public int CompareTo(object obj)
        {
            Passenger temp = obj as Passenger;
            if (temp != null && temp.PassportNum == this.PassportNum)
                return 0;
            return 1;
        }
    }
}