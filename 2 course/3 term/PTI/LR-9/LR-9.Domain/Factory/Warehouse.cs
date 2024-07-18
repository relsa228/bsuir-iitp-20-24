using System;

namespace LR_9.Domain.Factory
{
    [Serializable]
    public class Warehouse
    {
        public int InWarehouse;
        public int MaxCapacity;
        public string HeadOfWarehouse;

        public Warehouse()
        {
            
        }
        
        public Warehouse(string headOfWarehouse)
        {
            InWarehouse = 0;
            MaxCapacity = 100;
            HeadOfWarehouse = headOfWarehouse;
        }

        public bool AddToWarehouse(int count)
        {
            this.InWarehouse += count;
            if (this.InWarehouse > this.MaxCapacity)
            {
                this.InWarehouse -= count;
                return false;
            }
            
            return true;
        }

        public bool RemoveFromWarehouse(int count)
        {
            int temp = this.InWarehouse; 
            this.InWarehouse -= count;
            if (this.InWarehouse < 0)
            {
                this.InWarehouse += count;
                return false;
            }

            return true;
        }
    }
}