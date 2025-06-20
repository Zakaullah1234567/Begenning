using System;

class Person
{
    public string name;
    public int age;

    public void GetData()
    {
        Console.Write("Enter Name: ");
        name = Console.ReadLine();

        Console.Write("Enter Age: ");
        age = Convert.ToInt32(Console.ReadLine());
    }

    public void ShowData()
    {
        Console.WriteLine("Name: " + name);
        Console.WriteLine("Age: " + age);
    }
}

class Student : Person
{
    public string rollNumber;
    public string department;

    public void Input()
    {
        GetData();

        Console.Write("Enter Roll Number: ");
        rollNumber = Console.ReadLine();

        Console.Write("Enter Department: ");
        department = Console.ReadLine();
    }

    public void ShowStudentData()
    {
        ShowData();
        Console.WriteLine("Roll Number: " + rollNumber);
        Console.WriteLine("Department: " + department);
        Console.WriteLine("----------------------------------");
    }
}

class Program
{
    static void Main()
    {
        Student[] students = new Student[10];

        Console.WriteLine("Enter data for 10 students:\n");

        for (int i = 0; i < 3; i++)
        {
            Console.WriteLine($"--- Studentn {i + 1} ---");
            students[i] = new Student();
            students[i].Input();
        }

        Console.WriteLine("--- Displaying Student Data ---");

        for (int i = 0; i < 3; i++)
        {
            Console.WriteLine($"Student {i + 1}:");
            students[i].ShowStudentData();
        }

        Console.WriteLine("Enter Roll Number to Search: ");
        string rollToSearch = Console.ReadLine();

        SearchStudent(students, rollToSearch);

        Console.ReadLine();
    }
    static void SearchStudent(Student[] students, string roll)
    {
        bool found = false;

        for (int i = 0; i < students.Length; i++)
        {
            if (students[i].rollNumber == roll)
            {
                Console.WriteLine("\nStudent Found:");
                students[i].ShowStudentData();
                found = true;
                break;
            }
        }

        if (!found)
        {
            Console.WriteLine("\nNo student found with Roll Number: " + roll);
        }
    }
}
