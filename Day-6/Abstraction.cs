using System;

abstract class Payment
{
    public string userName;
    public double accNumber;

    public void GetUser()
    {
        Console.Write("Enter your name: ");
        userName = Console.ReadLine();
        Console.Write("Enter Your account number: ");
        accNumber = Convert.ToDouble(Console.ReadLine());
    }

    public abstract void Pay(double amount);
}

class CreditCard : Payment
{
    public override void Pay(double amount)
    {
        Console.WriteLine($"{userName}, your payment of Rs. {amount} via Credit Card is successful.");
    }
}

class JazzCash : Payment
{
    public override void Pay(double amount)
    {
        Console.WriteLine($"{userName}, your payment of Rs. {amount} via JazzCash is successful.");
    }
}

class EasyPaisa : Payment
{
    public override void Pay(double amount)
    {
        Console.WriteLine($"{userName}, your payment of Rs. {amount} via EasyPaisa is successful.");
    }
}

class Program
{
    static void Main()
    {
        Console.WriteLine("----- Welcome to our Payment System -----");
        Console.WriteLine("1. Credit Card");
        Console.WriteLine("2. JazzCash");
        Console.WriteLine("3. EasyPaisa");
        Console.Write("Choose Payment Method (1-3): ");
        int choice = Convert.ToInt32(Console.ReadLine());

        Payment payment; 

        switch (choice)
        {
            case 1:
                payment = new CreditCard();
                break;
            case 2:
                payment = new JazzCash();
                break;
            case 3:
                payment = new EasyPaisa();
                break;
            default:
                Console.WriteLine("Invalid choice. Exiting...");
                return;
        }

        payment.GetUser();

        Console.Write("Enter payment amount: Rs. ");
        double amount = Convert.ToDouble(Console.ReadLine());

        payment.Pay(amount); 

        Console.ReadLine();
    }
}
