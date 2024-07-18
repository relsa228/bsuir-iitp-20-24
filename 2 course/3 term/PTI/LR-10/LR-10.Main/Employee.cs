namespace LR_10.Main
{
    public class Employee
    {
        public string Name;
        public int Age;
        public bool HigherEducation;

        public Employee(string name, int age, bool higherEducation)
        {
            this.Name = name;
            this.Age = age;
            this.HigherEducation = higherEducation;
        }

        public string Info()
        {
            string info = $"\nИмя: {this.Name}\nВозраст: {this.Age}\nВысшее образование: ";
            if (this.HigherEducation)
                info += "есть\n";
            else
                info += "нет\n";
            info += "-----------------------------------";
            return info;
        }
    }
}