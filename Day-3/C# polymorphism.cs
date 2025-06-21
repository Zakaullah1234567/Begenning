using System;

class Vehicle
{
    public string brand;

    public virtual void show()
    {
        Console.WriteLine("Driving a vehicle");
    }

    public virtual void GetData()
    {
        Console.Write("Enter Brand: ");
        brand = Console.ReadLine();
    }
}

class Car : Vehicle
{
    public string model;

    public override void GetData()
    {
        base.GetData();
        Console.Write("Enter Car Model: ");
        model = Console.ReadLine();
    }

    public override void show()
    {
        Console.WriteLine($"Driving Car: {brand} - Model: {model}");
    }
}

class Bike : Vehicle
{
    public int engineCC;

    public override void GetData()
    {
        base.GetData();
        Console.Write("Enter Engine CC: ");
        engineCC = Convert.ToInt32(Console.ReadLine());
    }

    public override void show()
    {
        Console.WriteLine($"Riding Bike: {brand} - {engineCC}cc");
    }
}

class Truck : Vehicle
{
    public int loadCapacity;

    public override void GetData()
    {
        base.GetData();
        Console.Write("Enter Load Capacity (tons): ");
        loadCapacity = Convert.ToInt32(Console.ReadLine());
    }

    public override void show()
    {
        Console.WriteLine($"Driving Truck: {brand} - Load: {loadCapacity} tons");
    }
}

class Program
{
    static void Main()
    {
        Console.Write("How many vehicles do you want to enter? ");
        int n = Convert.ToInt32(Console.ReadLine());

        Vehicle[] vehicles = new Vehicle[n];

        for (int i = 0; i < n; i++)
        {
            Console.WriteLine($"\nEnter type of vehicle {i + 1} (car/bike/truck): ");
            string type = Console.ReadLine().ToLower();

            switch (type)
            {
                case "car":
                    vehicles[i] = new Car();
                    break;
                case "bike":
                    vehicles[i] = new Bike();
                    break;
                case "truck":
                    vehicles[i] = new Truck();
                    break;
                default:
                    Console.WriteLine("Invalid type! Defaulting to Vehicle.");
                    vehicles[i] = new Vehicle();
                    break;
            }

            vehicles[i].GetData(); 
        }

        Console.WriteLine("\n--- Vehicle Information ---\n");
        for (int i = 0; i < n; i++)
        {
            vehicles[i].show(); 
        }

        Console.ReadLine();
    }
}
