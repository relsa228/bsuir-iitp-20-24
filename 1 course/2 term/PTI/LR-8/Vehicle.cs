using System;

namespace LR_8
{
    abstract class Vehicle: IEquatable<Vehicle>
    {
        public event Help NotValidInput;
        internal delegate void Help();
        delegate string StrHelp(string error, string info);
        delegate void GetMessage(string message);
        
        protected int Speed;
        protected internal int MaxSpeed;
        protected int Coordinates;
        private int _acceleration;
        protected internal int MaxAcceleration;
        private int _braking;
        protected internal int MaxBraking;
        private string _resInfo;

        protected Vehicle()
        {
            Speed = 0;
            Coordinates = 0;
            _acceleration = 0;
            MaxBraking = 0;
            _braking = 0;
        }

        public Help HelpMeth()
        {
            string info = "\nДанные о машине:\nМаксимальная скорость: " + this.MaxSpeed + "\nМаксимальное ускорение: " + this.MaxAcceleration + "\nМаксимальная скорость торможения: " + this.MaxBraking;
            string error = "\nОшибка ввода";
            StrHelp strHelp = (error, info) => error + info;
            _resInfo = strHelp(error, info);

            Help help = this.GetRes;
            return help;
        }

        public void GetRes()
        {
            GetMessage message = delegate(string mes)
            {
                Console.WriteLine(mes);
            };

            message(_resInfo);
        }
        
        public void Braking(int time)
        {
            try
            {
                if (time >= 0)
                {
                    Coordinates = (int) (Coordinates + Speed * time - (_braking * Math.Pow(time, 2) / 2));
                    Speed = Speed - _braking * time;
                    if (Speed < 0)
                        Speed = 0;
                }
                else
                    throw new Exception("Отрицательное время.");
            }
            catch (Exception e)
            {
                NotValidInput?.Invoke();
            }
        }
        
        public void SetBraking(int br)
        {
            try
            {
                if (br <= MaxBraking && br >= 0)
                    _braking = br;
                else
                    throw new Exception("Неверное торможение");
            }
            catch (Exception e)
            {
                NotValidInput?.Invoke();
            }
        }

        public void SetAcceleration(int acc)
        {
            try
            {
                if (acc <= MaxAcceleration && acc >= 0)
                    _acceleration = acc;
                else
                    throw new Exception("Неверный разгон");
            }
            catch (Exception e)
            {
                NotValidInput?.Invoke();
            }
        }

        public void Overclocking(int time)
        {
            try
            {
                if (time >= 0)
                {
                    Coordinates = (int) (Coordinates + Speed * time + (_acceleration * Math.Pow(time, 2) / 2));
                    Speed = _acceleration * time + Speed;
                    if (Speed > MaxSpeed)
                        Speed = MaxSpeed;
                }
                else
                    throw new Exception("Отрицательное время");
            }
            catch (Exception e)
            {
                NotValidInput?.Invoke();
            }
        }

        public void Move(int time)
        {
            try
            {
                if (time >= 0)
                    Coordinates = Coordinates + Speed * time;
                else
                    throw new Exception("Отрицательное время");
            }
            catch (Exception e)
            {
                NotValidInput?.Invoke();
            }
        }

        public bool Equals(Vehicle other)
        {
            if (ReferenceEquals(null, other)) return false;
            if (ReferenceEquals(this, other)) return true;
            return MaxSpeed == other.MaxSpeed && MaxAcceleration == other.MaxAcceleration && MaxBraking == other.MaxBraking;
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj.GetType() != this.GetType()) return false;
            return Equals((Vehicle) obj);
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(MaxSpeed, MaxAcceleration, MaxBraking);
        }
    }
}