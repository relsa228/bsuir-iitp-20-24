using System;

namespace LR_6
{
    class Car : Vehicle, ITransmission
    {
        private int _parking;
        protected string Mk;

        public Car()
        {
            _parking = 0;
        }

        public int this[string status]
        {
            set
            {
                switch (status)
                {
                    case "PStatus":
                        _parking = value;
                        break;
                    case "SStatus":
                        Speed = value;
                        break;
                    case "CStatus":
                        Coordinates = value;
                        break;
                }
            }
            get
            {
                switch (status)
                {
                    case "PStatus":
                        return _parking;
                    case "SStatus":
                        return Speed;
                    case "CStatus":
                        return Coordinates;
                    default:
                        return 0;
                }
            }
        }

        public void Revers()
        {
            Speed = Speed * (-1);
            _parking = 0;
        }

        public void Drive()
        {
            _parking = 0;
            if (Speed < 0)
                Speed = Speed * (-1);
        }

        public void Park()
        {
            _parking = 1;
            Speed = 0;
        }

        public void Move(int time)
        {
            if (_parking == 1)
                Console.WriteLine("Переключите коробку в режим вождения");
            else
                base.Move(time);
        }

        public void Overclocking(int time)
        {
            if (_parking == 1)
                Console.WriteLine("Переключите коробку в режим вождения");
            else
                base.Overclocking(time);
        }

        public string MkStatus()
        {
            return Mk;
        }
        
        public virtual void Beep()
        {
        }
    }
}