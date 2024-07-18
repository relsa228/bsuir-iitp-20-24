using System;

namespace LR_6
{
    class Zhiga : Car
    {
        public Zhiga()
        {
            Mk = "Жига";
            MaxAcceleration = 5;
            MaxBraking = 2;
            MaxSpeed = 40;
        }
        
        public override void Beep()
        {   
            Console.WriteLine("Би-би-бип. Вы бибикнули.");
        }
    }
}