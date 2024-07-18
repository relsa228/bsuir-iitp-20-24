using System;

namespace LR_8
{
    class Program
    {
        delegate string WrCon(string addition);
            
        static void Main()
        {
            WrCon wrCon = addition => "\nУкажите желаемое " + addition;
            IClutch clutch = new Clutch();
            Console.WriteLine("Выберите машину: ");
            Console.WriteLine("1. Волга\n2. Жига\n3. Запорожец\n");
            Car car = null;
            bool stat = true;
            while (stat)
            {
                Console.Write("Ваш выбор: ");
                int carChoice = Convert.ToInt32(Console.ReadLine());

                switch (carChoice)
                {
                    case 1:
                        car = new Volga();
                        stat = false;
                        break;
                    case 2:
                        car = new Zhiga();
                        stat = false;
                        break;
                    case 3:
                        car = new Zaporozhec();
                        stat = false;
                        break;
                    default:
                        Console.WriteLine("\nВведите действительный номер.");
                        break;
                }
            }

            Vehicle.Help help = car.HelpMeth();
            car.NotValidInput += help;
            bool globalCheck = true;
            while (globalCheck)
            {
                Console.Clear();
                Console.WriteLine("\nСписок воозможных действий: ");
                Console.WriteLine("1. Разгон\n2. Движение\n3. Переключить коробку передач\n4. Торможение\n5. Узнать марку\n6. Сравнить машины\n7. Бибикнуть\n8. Выйти из машины");
                Console.Write("\nВыберите действие: ");
                int choice = Convert.ToInt32(Console.ReadLine());
                switch (choice)
                {
                    case 1:
                        Console.Write(wrCon("время разгона: "));
                        int time1 = Convert.ToInt32(Console.ReadLine()); 
                        Console.Write(wrCon("ускорение: "));
                        car.SetAcceleration(Convert.ToInt32(Console.ReadLine()));
                        car.Overclocking(time1); 
                        Console.WriteLine("\nРазгон завершен. Текущая скорость: " + car["SStatus"]);
                        Console.WriteLine("Текущие координаты: " + car["CStatus"] + "\n");
                        Console.ReadKey();
                        break;
                    
                    case 2: 
                        Console.Write(wrCon("время движения: "));
                        int time = Convert.ToInt32(Console.ReadLine()); 
                        car.Move(time); 
                        Console.WriteLine("Движение завершено. Текущие координаты: " + car["CStatus"] + "\n"); 
                        Console.ReadKey(); 
                        break;
                    
                    case 3:
                        Console.WriteLine("\nДоступные передачи:\n1. Drive\n2. Parking\n3. Revers");
                        Console.Write("\nВыберите передачу: ");
                        for (;;)
                        {
                            int transmis = Convert.ToInt32(Console.ReadLine());
                            bool check = false;
                            switch (transmis)
                            {
                                case 1:
                                    clutch.StartDrive(car);
                                    check = true;
                                    break;
                                case 2:
                                    check = true;
                                    clutch.StartPark(car);
                                    break;
                                case 3:
                                    check = true;
                                    clutch.StartRevers(car);
                                    break;
                                default:
                                    Console.WriteLine("Введите действительный номер: ");
                                    break;
                            }

                            if (check)
                                break;
                        }
                        Console.ReadKey();
                        break;
                    
                    case 4:
                        Console.Write(wrCon("время торможения: "));
                        int timeB = Convert.ToInt32(Console.ReadLine()); 
                        Console.Write("Укажите желаемую скорость торможения: ");
                        car.SetBraking(Convert.ToInt32(Console.ReadLine())); 
                        car.Braking(timeB); 
                        Console.WriteLine("\nТорможение завершено. Текущая скорость: " + car["SStatus"]);
                        Console.WriteLine("Текущие координаты: " + car["CStatus"] + "\n");
                        Console.ReadKey();
                        break;
                    
                    case 5:
                        Console.Write("\nМарка вашего автомобиля: " + car.MkStatus() + "\n\n");
                        Console.ReadKey();
                        break;
                    
                    case 6:
                        if(car.Equals(new Volga()))
                            Console.WriteLine("\nВолга: одинаковые");
                        else
                            Console.WriteLine("\nВолга: разные");
                        
                        if(car.Equals(new Zhiga()))
                            Console.WriteLine("Жига: одинаковые");
                        else
                            Console.WriteLine("Жига: разные");
                        
                        if(car.Equals(new Zaporozhec()))
                            Console.Write("Запорожец: одинаковые\n");
                        else
                            Console.Write("Запорожец: разные\n");
                        Console.ReadKey();
                        break;
                    
                    case 7:
                        car.Beep();
                        Console.ReadKey();
                        break;

                    case 8:
                        if (car["SStatus"] != 0)
                        {
                            Console.Write("Я понимаю, что представленный модельный ряд мягко говоря удручает, но все же выходить из машины на ходу - не самая лучшая идея. Хотя кто я такой, чтобы вас судить?");
                            Random alive = new Random();
                            int value = alive.Next(0, 2); 
                            if (value == 1)
                                Console.WriteLine("\n\nНу ничего себе. Вспомнив уроки гимнастики времен младшей школы вы сгруппировались и пережили падение, поразив проезжающих мимо.");
                            else if (value == 0)
                                Console.WriteLine("\n\nПриземление прошло довольно неудачно, вы сломали шею. Ну что ж, бывает.");
                        }
                        globalCheck = false;
                        Console.ReadKey();
                        break;
                    
                    default: 
                        Console.WriteLine("Такого действия не существует");
                        Console.ReadKey();
                        break;
                }
            }
        }
    }
}