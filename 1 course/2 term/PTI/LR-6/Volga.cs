using System;

namespace LR_6
{
    class Volga : Car
    {
        public Volga()
        {
            Mk = "Волга";
            MaxAcceleration = 5;
            MaxSpeed = 45;
            MaxBraking = 2;
        }
        
        public override void Beep()
        {   
            Console.WriteLine("Бип-би-бип. Вы бибикнули.");
        }
    }
}