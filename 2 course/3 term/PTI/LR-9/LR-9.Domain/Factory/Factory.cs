using System;

namespace LR_9.Domain.Factory
{
    [Serializable]
    public class Factory
    {
        public Warehouse DetailWarehouse = new Warehouse("Валерий Альбертович Шпак");
        public Warehouse ProductWarehouse = new Warehouse("Богомолов Александр Александрович");
        public int Workers;
        public string Specialization;
        public int Budget;
        public Factory()
        {
            
        }
        public Factory(string specialization, int workers, int budget)
        {
            Specialization = specialization;
            Workers = workers;
            Budget = budget;
        }
        public void ProduceProducts(int count)
        {
            if (this.DetailWarehouse.RemoveFromWarehouse(10*count) && this.ProductWarehouse.AddToWarehouse(count))
                Console.WriteLine("Произведено " + count + " продуктов по специализации.");
            else
                Console.WriteLine("Ошибка при производстве.");
        }

        public void BuyDetails(int count)
        {
            if (Budget < count * 100 && DetailWarehouse.AddToWarehouse(count))
                Console.WriteLine("Ошибка при покупке.");
            else
            {
                Budget -= count * 100;
                Console.WriteLine("Куплено " + count + " деталей.");
            }
        }

        public void SaleProducts(int count)
        {
            if (ProductWarehouse.RemoveFromWarehouse(count))
            {
                Budget += 10000 * count;
                Console.WriteLine("Продано " + count + " деталей.\nПолучено " + 10000 * count + " долларов.");
            }
            else
                Console.WriteLine("На складе не хватает изделий.");
        }

        public void Info()
        {
            string info = "Специальность завода: " + this.Specialization + "\nРаботников: " + this.Workers +
                          "\nБюджет завода: " + this.Budget + "\nДеталей на складе: " + this.DetailWarehouse.InWarehouse 
                          + "\nПродукта на складе: " + this.ProductWarehouse.InWarehouse;
            Console.WriteLine(info);
            Console.WriteLine("--------------------------");
        }
    }
}