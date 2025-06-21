# Vehicle Management System in C#

This is a simple console-based **Vehicle Management System** built using **C# and Object-Oriented Programming**. The system demonstrates the use of **inheritance**, **polymorphism**, and **dynamic object creation** using a `Vehicle` base class and derived classes `Car`, `Bike`, and `Truck`.

## Features

- Input and display multiple types of vehicles.
- Uses arrays and loops to handle multiple vehicle entries.
- Demonstrates `virtual` and `override` keywords for polymorphism.
- Dynamic object creation using `switch-case`.
- Clean and beginner-friendly code structure.

## Class Structure

### `Vehicle` (Base Class)
- Data Member: `brand`
- Methods:
  - `virtual void GetData()` – input brand.
  - `virtual void show()` – display default vehicle message.

### `Car : Vehicle`
- Data Member: `model`
- Overrides:
  - `GetData()` – gets brand and model.
  - `show()` – displays brand and model.

### `Bike : Vehicle`
- Data Member: `engineCC`
- Overrides:
  - `GetData()` – gets brand and engine CC.
  - `show()` – displays brand and engine CC.

### `Truck : Vehicle`
- Data Member: `loadCapacity`
- Overrides:
  - `GetData()` – gets brand and load capacity.
  - `show()` – displays brand and load capacity.


## Author

- **Zaka Ullah** <br>– Computer Science Student




