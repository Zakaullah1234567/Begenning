// Royal Fast Food Shop Management System - Full Version with Admin & Exception Handling
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <Windows.h>
using namespace std;

void shop(){
     cout << ">>=================================================================<<\n";
    cout << "||                                                                 ||\n";
    cout << "||                                                                 ||\n";
    cout << "||   ____    ___ __   __  _     _       _____  _     ____  _____   ||\n";
    cout << "||  |  _ \\  / _ \\\\ \\ / / / \\   | |     |  ___|/ \\   / ___||_   _|  ||\n";
    cout << "||  | |_) || | | |\\ V / / _ \\  | |     | |_  / _ \\  \\___ \\  | |    ||\n";
    cout << "||  |  _ < | |_| | | | / ___ \\ | |___  |  _|/ ___ \\  ___) | | |    ||\n";
    cout << "||  |_| \\_\\ \\___/  |_|/_/   \\_\\|_____| |_| /_/   \\_\\|____/  |_|    ||\n";
    cout << "||   _____  ___    ___   ____    ____   _   _   ___   ____         ||\n";
    cout << "||  |  ___|/ _ \\  / _ \\ |  _ \\  / ___| | | | | / _ \\ |  _ \\        ||\n";
    cout << "||  | |_  | | | || | | || | | | \\___ \\ | |_| || | | || |_) |       ||\n";
    cout << "||  |  _| | |_| || |_| || |_| |  ___) ||  _  || |_| ||  __/        ||\n";
    cout << "||  |_|    \\___/  \\___/ |____/  |____/ |_| |_| \\___/ |_|           ||\n";
    cout << "||                                                                 ||\n";
    cout << "||                                                                 ||\n";
    cout << ">>=================================================================<<\n";
}
void waitDots(string msg = "", int count = 3) {
    cout << msg;
    for (int i = 0; i < count; i++) {
        cout << ".";
        Sleep(500);
    }
    cout << endl;
}

void handleException(const string& msg) {
    cerr << "[Error] " << msg << endl;
    waitDots("Returning to menu");
    system("cls");
}

// ------------------------- MenuItem Class -------------------------
class MenuItem {
public:
    int id;
    string name;
    float price;

    void input() {
        shop();
        try {
            cout << "Enter Item ID: "; cin >> id;
            cout << "Enter Item Name: "; cin.ignore(); getline(cin, name);
            cout << "Enter Item Price: "; cin >> price;
            if (price <= 0) throw runtime_error("Invalid price value!");
        }
        catch (exception& e) {
            handleException(e.what());
        }
    }

    void display() const {
        cout << left << setw(5) << id << setw(20) << name << setw(10) << price << endl;
    }
};

// ------------------------- Menu Class -------------------------
class Menu {
    vector<MenuItem> items;
public:
    void loadFromFile(string filename = "menu.dat") {
        shop();
        items.clear();
        ifstream fin(filename, ios::binary);
        if (!fin) return;
        MenuItem item;
        while (fin.read((char*)&item, sizeof(item))) {
            items.push_back(item);
        }
        fin.close();
    }

    void saveToFile(string filename = "menu.dat") {
        ofstream fout(filename, ios::binary);
        for (auto& item : items) {
            fout.write((char*)&item, sizeof(item));
        }
        fout.close();
    }

    void showMenu() {

        cout << "\n========= MENU =========\n";
        cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Price" << endl;
        cout << "-----------------------------\n";
        for (auto& item : items) item.display();
        cout << "==============================\n";
    }

    MenuItem* getItemById(int id) {
        for (auto& item : items) {
            if (item.id == id) return &item;
        }
        return nullptr;
    }

    void addMenuItem() {
        shop();
        MenuItem item;
        item.input();
        items.push_back(item);
        saveToFile();
        waitDots("Adding item");
        cout << "Item added successfully!\n";
    }
};

// ------------------------- Person & Customer -------------------------
class Person {
protected:
    string name, phone, location;
public:
    virtual void inputDetails() {
        system("cls");
        shop();
        try {
            cout << "Enter Name: "; cin.ignore(); getline(cin, name);
            cout << "Enter Phone Number: "; getline(cin, phone);
            cout << "Enter Location: "; getline(cin, location);
        } catch (exception& e) {
            handleException("Invalid person input");
        }
    }
    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getLocation() const { return location; }
};

class Customer : public Person {
    string orderType;
public:
    void inputDetails() override {
        system("cls");
        shop();
        Person::inputDetails();
        cout << "Order Type (Dine-In / Parcel): "; getline(cin, orderType);
    }
    string getOrderType() const { return orderType; }
    void showDetails() const {
        system("cls");
        shop();
        cout << "Name      : " << name << endl;
        cout << "Phone     : " << phone << endl;
        cout << "Location  : " << location << endl;
        cout << "Order Type: " << orderType << endl;
    }
};

// ------------------------- OrderItem Class -------------------------
class OrderItem {
public:
    MenuItem item;
    int quantity;
    float totalPrice;
    void calculateTotal() {
        totalPrice = item.price * quantity;
    }
};

// ------------------------- Order Class -------------------------
class Order {
    Customer customer;
    vector<OrderItem> items;
    float totalAmount = 0;
    string paymentMethod, paymentAccount, paymentStatus;

public:
    void takeOrder(Menu& menu) {
    shop();
    customer.inputDetails();
    bool done = false;

    while (!done) {
        items.clear();
        totalAmount = 0;

        while (true) {
            menu.showMenu();
            int id;
            cout << "Enter Item ID (0 to stop): "; 
            cin >> id;
            if (id == 0) break;
            MenuItem* m = menu.getItemById(id);
            if (!m) {
                handleException("Invalid item ID!");
                continue;
            }
            OrderItem oi;
            oi.item = *m;
            cout << "Enter quantity: ";
            cin >> oi.quantity;
            if (oi.quantity <= 0) {
                handleException("Quantity must be greater than 0");
                continue;
            }
            oi.calculateTotal();
            totalAmount += oi.totalPrice;
            items.push_back(oi);
        }

        cout << "\nYou have selected " << items.size() << " item(s).\n";
        showBill();  // Show current bill before saving
        cout << "1. Proceed\n2. Edit Order\n3. Cancel Order\nChoice: ";
        int ch; 
        cin >> ch;
        if (ch == 1) {
            choosePaymentMethod();
            done = true;
            saveToFile();  
            showBill();  // Show final bill after payment
        } else if (ch == 2) {
            continue;
        } else {
            waitDots("Order cancelled");
            return;
        }
    }
}

    void choosePaymentMethod() {
        
        cout << "\nSelect Payment Method:\n1. Easypaisa\n2. JazzCash\n3. Bank Transfer\n4. Cash\nChoice: ";
        int choice;
        cin >> choice; 
        cin.ignore();

        switch (choice) {
        case 1:
            paymentMethod = "Easypaisa";
            cout << "Enter Easypaisa Number: "; 
            getline(cin, paymentAccount);
            break;
        case 2:
            paymentMethod = "JazzCash";
            cout << "Enter JazzCash Number: "; 
            getline(cin, paymentAccount);
            break;
        case 3:
            paymentMethod = "Bank";
            do {
                cout << "Enter 13-digit Bank Account Number: ";
                getline(cin, paymentAccount);
            } while (paymentAccount.length() != 13);
            break;
        default:
            paymentMethod = "Cash";
            paymentStatus = "Pending";
            return;
        }

        int otp = rand() % 9000 + 1000;
        waitDots("Generating OTP");
        cout << "OTP: " << otp << endl;
        int enterotp;
        cout << "Enter OTP: ";
        cin >> enterotp;
        paymentStatus = (enterotp == otp) ? "Done" : "Failed";
    }

   void showBill() {
    system("cls");
    shop();
    
    cout << "\n========== BILL ==========" << endl;
    cout << "Name      : " << customer.getName() << endl;
    cout << "Phone     : " << customer.getPhone() << endl;
    cout << "Location  : " << customer.getLocation() << endl;
    cout << "Order Type: " << customer.getOrderType() << endl;
    cout << left << setw(20) << "Item" << setw(8) << "Qty" << setw(10) << "Price" << "Total\n";
    
    for (auto& item : items) {
        cout << left << setw(20) << item.item.name 
             << setw(8) << item.quantity 
             << setw(10) << item.item.price 
             << item.totalPrice << endl;
    }
    
    cout << "-------------------------------\n";
    cout << left << setw(25) << "Total Amount:" << totalAmount << endl;
    cout << left << setw(25) << "Payment Method:" << paymentMethod << endl;
    if (paymentMethod != "Cash") {
        cout << left << setw(25) << "Payment Account:" << paymentAccount << endl;
    }
    cout << left << setw(25) << "Payment Status:" << paymentStatus << endl;
}


    void saveToFile(string filename = "orders.txt") {
        ofstream fout(filename, ios::app);
        fout << customer.getName() << "," << customer.getPhone() << "," << customer.getLocation() << "," << customer.getOrderType()
             << "," << totalAmount << "," << paymentMethod << "," << paymentAccount << "," << paymentStatus << endl;
        for (auto& item : items) {
            fout << "-" << item.item.name << "," << item.quantity << "," << item.item.price << "," << item.totalPrice << endl;
        }
        fout << "#\n";
        fout.close();
    }
};
//-------------Admin panel--------------
class Admin {
    string username, password;

public:
    bool login() {
        system("cls");
        shop();
        ifstream fin("admin.dat");
        if (!fin) {
            username = "admin";
            password = "1234";
        } else {
            getline(fin, username);
            getline(fin, password);
            fin.close();
        }

        string u, p;
        cout << "Enter username: "; cin >> u;
        cout << "Enter password: "; cin >> p;

        return (u == username && p == password);
    }

    void changeCredentials() {
        system("cls");
        shop();
        cout << "Enter new username: "; cin >> username;
        cout << "Enter new password: "; cin >> password;
        ofstream fout("admin.dat");
        fout << username << endl << password << endl;
        fout.close();
        waitDots("Updating credentials");
        cout << "Credentials updated successfully.\n";
        system("cls");
    }

    void viewAllOrders() {
        system("cls");
        shop();
        ifstream fin("orders.txt");
        if (!fin) {
            cout << "No orders found!\n";
            return;
        }

        string line;
        while (getline(fin, line)) {
            if (line == "#") {
                cout << "------------------------------------------\n";
                continue;
            }
            else if (line[0] != '-') {
                stringstream ss(line);
                string name, phone, location, type, amount, method, account, status;

                getline(ss, name, ',');
                getline(ss, phone, ',');
                getline(ss, location, ',');
                getline(ss, type, ',');
                getline(ss, amount, ',');
                getline(ss, method, ',');
                getline(ss, account, ',');
                getline(ss, status);

                cout << "\nCustomer Name   : " << name << endl;
                cout << "Phone Number    : " << phone << endl;
                cout << "Location        : " << location << endl;
                cout << "Order Type      : " << type << endl;
                cout << "------------------------------------------\n";
                cout << left << setw(20) << "Item" << setw(10) << "Qty" << setw(10) << "Price" << "Total\n";
            } else {
                stringstream ss(line.substr(1));
                string itemName, qty, price, total;
                getline(ss, itemName, ',');
                getline(ss, qty, ',');
                getline(ss, price, ',');
                getline(ss, total);
                cout << left << setw(20) << itemName << setw(10) << qty << setw(10) << price << total << endl;
            }
        }
        fin.close();
    }
};

// ------------------------- Main -------------------------
int main() {
     MenuItem items[20] = {
    {1,  "Zinger Burger",       350},
     {2,  "Chicken Burger",      300},
     {3,  "Beef Burger",         380},
     {4,  "Cheese Burger",       400},
     {5,  "Grilled Burger",      420},
     {6,  "Chicken Shawarma",    250},
     {7,  "Beef Shawarma",       270},
     {8,  "Crispy Broast",       320},
     {9,  "Chicken Wings (6pc)", 280},
     {10, "Grilled Sandwich",    260},

     {11, "Fries (Regular)",     120},
     {12, "Fries (Masala)",      150},
     {13, "Nuggets (6pc)",       200},
     {14, "Onion Rings",         180},
     {15, "Garlic Mayo Fries",   160},

     {16, "Deal 1: Zinger + Fries + Drink",        500},
     {17, "Deal 2: 2 Burgers + 2 Drinks",           850},
     {18, "Deal 3: Shawarma + Nuggets + Fries",     600},
     {19, "Deal 4: Broast + Mayo Fries + Drink",    620},
     {20, "Deal 5: 2 Sandwiches + Fries + Drink",   750}
 };

 ofstream fout("menu.dat", ios::binary);
 for (int i = 0; i < 20; ++i) {
     fout.write((char*)&items[i], sizeof(MenuItem));
 }
 fout.close();
    try {
        Menu menu;
        menu.loadFromFile();

        int mainChoice;
        do {
            cout << "\n===== Royal Fast Food Shop  =====\n";
            cout << "1. Place Order\n2. Admin Login\n3. Exit\nEnter choice: ";
            cin >> mainChoice;

            switch (mainChoice) {
            case 1: {
                system("cls");
                Order order;
                order.takeOrder(menu);
                order.showBill();
                break;
            }
            case 2: {
                Admin admin;
                if (admin.login()) {
                    waitDots("Logging in");
                    int adminChoice;
                    do {
                        cout << "\n--- Admin Panel ---\n";
                        cout << "1. View Menu\n2. Add Menu Item\n3. View All Orders\n4. Change Credentials\n5. Logout\nChoice: ";
                        cin >> adminChoice;
                        switch (adminChoice) {
                        case 1: menu.showMenu(); break;
                        case 2: menu.addMenuItem(); break;
                        case 3: admin.viewAllOrders(); break;
                        case 4: admin.changeCredentials(); break;
                        }
                    } while (adminChoice != 5);
                } else {
                    handleException("Invalid login!");
                }
                break;
            }
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                handleException("Invalid menu choice");
            }
        } while (mainChoice != 3);
    }
    catch (exception& e) {
        handleException(e.what());
    }
    return 0;
}
