# Royal Fast Food Shop Management System

This is a *C++ console-based application* that simulates a fast-food restaurant management system. It allows both *customers* and *admins* to interact with the system in a user-friendly way.

---

## Features

### Customer Panel:
- View menu and place orders
- Enter name, phone number, and location
- Select items with quantity
- Choose payment method (Easypaisa, JazzCash, Bank Transfer, or Cash)
- OTP verification for secure payment
- Generate detailed receipt

### Admin Panel:
- Login with credentials (admin / 1234 by default)
- View full menu
- Add new menu items
- View all customer orders with full details
- Change admin username and password

---

## File Handling

The system uses file handling to store:
- Menu items (menu.dat in binary)
- Admin credentials (admin.dat)
- Orders (orders.txt)

---

## Technologies Used

- C++ (OOP concepts)
- File handling (binary and text)
- Console UI formatting using iomanip
- OTP system using rand() and Sleep() from <Windows.h>

---

## How to Run

1. Open project in any C++ IDE or terminal with Windows OS.
2. Compile using a C++ compiler like g++ or Code::Blocks.
3. Run the executable.
4. Choose to either:
   - Place Order (as a customer)
   - Login as Admin

---

## Folder Structure
RoyalFastFood/ main.cpp 
menu.dat         # Binary file with menu items 
admin.dat        # Admin credentials
orders.txt       # All orders saved here

---

## Sample Admin Credentials

- Username: admin
- Password: 1234

> You can change these from the admin panel in the program.

---

## Author

Developed by Zaka Ullah
Student of Computer Science  
Pir Mehr Ali Shah Arid Agriculture University, Rawalpindi

---

## Note

This project was built as part of a learning journey into *Object-Oriented Programming in C++* with file handling and system-level features.