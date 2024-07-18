using System;

namespace LR_6
{
    class Zaporozhec : Car
    {
        public Zaporozhec()
        {
            MaxSpeed = 35;
            MaxAcceleration = 3;
            MaxBraking = 2;
            Mk = "Запорожец";
        }
        
        public override void Beep()
        {   
            Console.WriteLine("Би-бииип. Вы бибикнули.");
        }
    }
}