using System;

namespace LR_8
{
    public class Employee
    {
        public string Name { get; set; }
        public int Age { get; set; }
        public bool HigherEducation { get; set; }

        public Employee(string name, int age, bool higherEducation)
        {
            Name = name;
            Age = age;
            HigherEducation = higherEducation;
        }

        public void Info()
        {
            Console.Write("\nИмя: " + this.Name + "\nВозраст: " + this.Age +"\nВысшее образование: ");
            if(HigherEducation)
                Console.Write("есть\n");
            else
                Console.Write("нет\n");    
            Console.Write("------------------------");
        }
    }
}