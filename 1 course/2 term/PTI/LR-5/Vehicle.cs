using System;

namespace LR_5
{
    abstract class Vehicle
    {
        protected int Speed;
        protected int MaxSpeed;
        protected int Coordinates;
        private int _acceleration;
        protected int MaxAcceleration;
        private int _braking;
        protected int MaxBraking;

        protected Vehicle()
        {
            Speed = 0;
            Coordinates = 0;
            _acceleration = 0;
            MaxBraking = 0;
            _braking = 0;
        }
        
        public void Braking(int time)
        {
            Coordinates = (int) (Coordinates + Speed * time - (_braking * Math.Pow(time,2) / 2));
            Speed = Speed - _braking * time;
            if (Speed < 0)
                Speed = 0;
        }
        
        public void SetBraking(int br)
        {
            if (br > MaxBraking)
                br = MaxBraking;
            _braking = br > 0 ? br : 0;
        }

        public void SetAcceleration(int acc)
        {
            if (acc > MaxAcceleration)
                acc = MaxAcceleration;
            _acceleration = acc > 0 ? acc : 0;
        }

        public void Overclocking(int time)
        {
            Coordinates = (int) (Coordinates + Speed * time + (_acceleration * Math.Pow(time,2) / 2));
            Speed = _acceleration * time + Speed;
            if (Speed > MaxSpeed)
                Speed = MaxSpeed;
        }

        public void Move(int time)
        {
            Coordinates = Coordinates + Speed * time;
        }
    }
}