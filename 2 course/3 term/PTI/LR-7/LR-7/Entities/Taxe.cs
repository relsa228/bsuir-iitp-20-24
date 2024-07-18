using System;

namespace LR_7.Entities
{
    public class Taxe
    {
        public string EndPoint;
        public float Price;

        public Taxe()
        {
            EndPoint = "";
            Price = 0;
        }

        public void AddTaxe()
        {
            Console.Write("\nИнформация о тарифе\nВведите пункт прибытия: ");
            this.EndPoint = Console.ReadLine();
            do 
                Console.Write("Введите цену билета: ");
            while (!float.TryParse(Console.ReadLine(), out this.Price));
        }
        
        public string Info()
        {
            string info = "\nТочка прибытия: " + this.EndPoint + "\nЦена: " + this.Price;
            return info;
        }
    }
}