using System;

class BankAccount
{
    private string accountHolder;
    private double balance;

    public string AccountHolder
    {
        get { return accountHolder; }
        set { accountHolder = value; }
    }

    public double Balance
    {
        get { return balance; }
    }

    public BankAccount(string name, double initialDeposit)
    {
        accountHolder = name;

        if (initialDeposit >= 0)
            balance = initialDeposit;
        else
            Console.WriteLine("Initial deposit cannot be negative.");
    }
    public void Deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            Console.WriteLine($"Rs. {amount} deposited successfully.");
        }
        else
        {
            Console.WriteLine("Invalid deposit amount.");
        }
    }

    public void Withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            Console.WriteLine($"Rs. {amount} withdrawn successfully.");
        }
        else
        {
            Console.WriteLine("Invalid or insufficient funds.");
        }
    }

    public void ShowAccount()
    {
        Console.WriteLine("--- Account Information ---");
        Console.WriteLine("Account Holder: " + accountHolder);
        Console.WriteLine("Current Balance: Rs. " + balance);
    }
}

class Program
{
    static void Main()
    {
        Console.Write("Enter account holder name: ");
        string name = Console.ReadLine();

        Console.Write("Enter initial deposit: Rs. ");
        double deposit = Convert.ToDouble(Console.ReadLine());

        BankAccount account = new BankAccount(name, deposit);

        int choice;
        do
        {
            Console.WriteLine("--- Bank Menu ---");
            Console.WriteLine("1. Deposit");
            Console.WriteLine("2. Withdraw");
            Console.WriteLine("3. Show Account Info");
            Console.WriteLine("4. Exit");
            Console.Write("Enter your choice: ");
            choice = Convert.ToInt32(Console.ReadLine());

            switch (choice)
            {
                case 1:
                    Console.Write("Enter amount to deposit: Rs. ");
                    double d = Convert.ToDouble(Console.ReadLine());
                    account.Deposit(d);
                    break;

                case 2:
                    Console.Write("Enter amount to withdraw: Rs. ");
                    double w = Convert.ToDouble(Console.ReadLine());
                    account.Withdraw(w);
                    break;

                case 3:
                    account.ShowAccount();
                    break;

                case 4:
                    Console.WriteLine("Thank you for using our Bank ");
                    break;

                default:
                    Console.WriteLine("Invalid choice. Try again.");
                    break;
            }

        } while (choice != 4);

        Console.ReadLine();
    }
}
