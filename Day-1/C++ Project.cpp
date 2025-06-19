#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <Windows.h>
using namespace std;

// ------------------------- MenuItem Class -------------------------
class MenuItem {
public:
    int id;
    string name;
    float price;

    void input() {
        cout << "Enter Item ID: "; cin >> id;
        cout << "Enter Item Name: "; cin.ignore(); getline(cin, name);
        cout << "Enter Item Price: "; cin >> price;
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
        cout << "========================\n";
        cout << "===                  ===\n";
        cout << "========= MENU =========\n";
        cout << "===                  ===\n";
        cout << "=======================\n";
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
        MenuItem item;
        item.input();
        items.push_back(item);
        saveToFile();
        cout << "Adding item";
        for (int i = 0; i < 3; i++) {
            cout << ".";
            Sleep(500);
        }
        cout << "Item added successfully!\n";
    }
};

// ------------------------- Person Class -------------------------
class Person {
protected:
    string name, phone, location;
public:
    virtual void inputDetails() {
        cout << "Enter Name: "; cin.ignore(); getline(cin, name);
        cout << "Enter Phone Number: "; getline(cin, phone);
        cout << "Enter Location: "; getline(cin, location);
    }
    virtual void showDetails() {
        cout << "Name      : " << name << endl;
        cout << "Phone     : " << phone << endl;
        cout << "Location  : " << location << endl;
    }
    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getLocation() const { return location; }
};

// ------------------------- Customer Class -------------------------
class Customer : public Person {
    string orderType;
public:
    void inputDetails() override {
        Person::inputDetails();
        cout << "Order Type (Dine-In / Parcel): "; getline(cin, orderType);
    }
    void showDetails() override {
        Person::showDetails();
        cout << "Order Type: " << orderType << endl;
    }
    string getOrderType() const { return orderType; }
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
        customer.inputDetails();
        int choice;
        bool hasItems = false;

        do {
            menu.showMenu();
            cout << "Enter Item ID to order (0 to finish): ";
            cin >> choice;
            if (choice == 0) break;
            MenuItem* item = menu.getItemById(choice);
            if (item) {
                OrderItem oItem;
                oItem.item = *item;
                cout << "Enter quantity: ";
                cin >> oItem.quantity;
                oItem.calculateTotal();
                totalAmount += oItem.totalPrice;
                items.push_back(oItem);
                hasItems = true; 
            }
            else {
                cout << "Invalid ID!\n";
            }
        } while (true);
        if (hasItems) {
            choosePaymentMethod();
            saveToFile();
        }
        else {
            cout << "No items were ordered. Exiting without payment";
            for (int i = 0; i < 3; i++) {
                cout << ".";
                Sleep(500);
            }
            cout << endl;
        }
    }

    void choosePaymentMethod() {
        system("cls");
        cout << "\nSelect Payment Method:\n1. Easypaisa\n2. JazzCash\n3. Bank Transfer\n4. Cash\nChoice: ";
        int choice;
        cin >> choice; cin.ignore();

        switch (choice) {
        case 1:
            paymentMethod = "Easypaisa";
            cout << "Enter Easypaisa Number: "; getline(cin, paymentAccount);
            break;
        case 2:
            paymentMethod = "JazzCash";
            cout << "Enter JazzCash Number: "; getline(cin, paymentAccount);
            break;
        case 3:
            paymentMethod = "Bank";
            do {
                cout << "Enter 13-digit Bank Account Number: ";
                getline(cin, paymentAccount);
            } while (paymentAccount.length() != 13);
            break;
        case 4:
            paymentMethod = "Cash";
            paymentStatus = "Pending";
            return;
        default:
            paymentMethod = "Cash";
            paymentStatus = "Pending";
            return;
        }

        int otp = rand() % 9000 + 1000;
        cout << "Please wait while your OTP is generated";
        for (int i = 0; i < 3; i++) {
            cout << ".";
            Sleep(500);
        }
        cout << "\nGenerated OTP: " << otp << endl;
        int userOTP;
        cout << "Enter the OTP: "; cin >> userOTP;
        paymentStatus = (userOTP == otp) ? "Done" : "Failed";
    }

    void showBill() {
        cout << "Generating Bill";
        for (int i = 0; i < 3; i++) {
            cout << ".";
            Sleep(500);
        }
        system("cls");
        cout << "\n\n######################################\n";
        cout << "###                                     ###\n";
        cout << "###         Royal Fast Food Shop        ###\n";
        cout << "###                                     ###\n";
        cout << "###########################################\n";
        customer.showDetails();
        cout << "###########################################\n";
        cout << "###                                     ###\n";
        cout << left << setw(15) << "Item" << setw(8) << "Qty" << setw(10) << "Price" << "Total\n";
        cout << "###                                     ###\n";
        cout << "###########################################\n";
        for (auto& it : items) {
            cout << left << setw(15) << it.item.name << setw(8) << it.quantity
                << setw(10) << it.item.price << it.totalPrice << endl;
        }
        cout << "###########################################\n";
        cout << "###                                     ###\n";
        cout << left << setw(30) << "Total Amount:" << totalAmount << endl;
        cout << left << setw(30) << "Payment Method:" << paymentMethod << endl;
        cout << left << setw(30) << "Account Info:" << paymentAccount << endl;
        cout << left << setw(30) << "Payment Status:" << paymentStatus << endl;
        cout << "###                                     ###\n";
        cout << "###########################################\n";
    }

    void saveToFile(string filename = "orders.txt") {
        ofstream fout(filename, ios::app);
        if (fout) {
            fout << customer.getName() << "," << customer.getPhone() << "," << customer.getLocation() << ","
                << customer.getOrderType() << "," << totalAmount << "," << paymentMethod << ","
                << paymentAccount << "," << paymentStatus << endl;
            for (auto& item : items) {
                fout << "-" << item.item.name << "," << item.quantity << ","
                    << item.item.price << "," << item.totalPrice << endl;
            }
            fout << "#\n";
        }
        fout.close();
    }
};

// ------------------------- Admin Class -------------------------
class Admin {
    string username, password;

public:
    bool login() {
        ifstream fin("admin.dat");
        if (!fin) {
            username = "admin";
            password = "1234";
        }
        else {
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
        cout << "Enter new username: "; cin >> username;
        cout << "Enter new password: "; cin >> password;
        ofstream fout("admin.dat");
        fout << username << endl << password << endl;
        fout.close();
        cout << "Loading";
        for (int i = 0; i < 3; i++) {
            cout << ".";
            Sleep(500);
        }
        cout << "Credentials updated successfully.\n";
    }

    void viewAllOrders() {
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
                }
                else {
                    stringstream ss(line.substr(1)); // Remove '-' before parsing
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
    Menu menu;
    menu.loadFromFile();

    int mainChoice;
    do {
        cout << "\n===== Royal Fast Food Shop  =====\n";
        cout << "1. Place Order\n2. Admin Login\n3. Exit\nEnter choice: ";
        cin >> mainChoice;

        if (mainChoice == 1) {
            system("cls");
            Order order;
            order.takeOrder(menu);
            order.showBill();
        }
        else if (mainChoice == 2) {
            Admin admin;
            if (admin.login()) {
                cout << "Logging in";
                for (int i = 0; i < 3; i++) {
                    cout << ".";
                    Sleep(500);
                }
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
            }
            else {
                cout << "Invalid login!\n";
            }
        }
    } while (mainChoice != 3);

    return 0;
}