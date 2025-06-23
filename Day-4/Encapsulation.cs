using System;

class Person
{
    private string name;
    private int age;

    public string Name
    {
        get { return name; }
        set { name = value; }
    }

    public int Age
    {
        get { return age; }
        set
        {
            if (value >= 0 && value <= 120)
            {
                age = value;
            }
            else
            {
                Console.WriteLine("Invalid age! Age must be between 0 and 120.");
            }
        }
    }

    public void ShowInfo()
    {
        Console.WriteLine("Name: " + name);
        Console.WriteLine("Age: " + age);
    }
}

class Program
{
    static void Main()
    {
        Person p1 = new Person();

        Console.Write("Enter name: ");
        p1.Name = Console.ReadLine(); 

        Console.Write("Enter age: ");
        p1.Age = Convert.ToInt32(Console.ReadLine());

        Console.WriteLine("\n--- Person Info ---");
        p1.ShowInfo(); 

        Console.ReadLine();
    }
}
