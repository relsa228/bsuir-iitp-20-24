namespace WorkerLib
{
    public class Worker
    {
        public int Id;
        public string Name;
        public int Age;

        public Worker(int id, int age, string name)
        {
            this.Age = age;
            this.Id = id;
            this.Name = name;
        }

        public string Info()
        {
            string res = $"Номер в списке: {Id}\nИмя: {Name}\nВозраст: {Age}\n";
            res += "--------------------------";
            return res;
        }
    }
}