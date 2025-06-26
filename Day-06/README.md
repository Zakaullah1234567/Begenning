# 💳 C# Payment System using Abstract Classes

This is a C# console application that demonstrates **abstraction** and **polymorphism** using an abstract `Payment` class. The program allows users to choose a payment method (Credit Card, JazzCash, EasyPaisa), enter their details, and process a payment.

---

## Key Concepts Demonstrated

- **Abstraction** with `abstract class`
- **Polymorphism** via overridden `Pay()` method
- **Inheritance** from a base class
- Clean and user-friendly console interaction

---

## Features

- Multiple payment method options:
  - Credit Card
  - JazzCash
  - EasyPaisa
- Prompts user for:
  - Name
  - Account Number
  - Payment amount
- Confirms the payment with a personalized message

---

## Sample Output

----- Welcome to our Payment System -----

1.Credit Card

2.JazzCash

3.EasyPaisa
Choose Payment Method (1-3): 2
Enter your name: Zaka ullah
Enter Your account number: 123456
Enter payment amount: Rs. 500

*Zaka Ullah, your payment of Rs. 500 via JazzCash is successful.*


---

## Author

Made by **Zaka Ullah**

---

## Future Improvements

- Add input validation (e.g. numeric checks, account number length)
- Add more payment methods (e.g., Bank Transfer, PayPal)
- Save payment logs to a file or database
