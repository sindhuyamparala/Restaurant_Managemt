#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Order {
    string itemName;
    int quantity;
    double priceInRupees;
};

struct MenuItem {
    string itemName;
    double priceInRupees;
};

struct Table {
    int tableNumber;
    bool reserved;
    string customerName;
    vector<Order> orders;
};

void displayMenu(const vector<MenuItem>& menu) {
    cout << "Menu Sections:\n";
    cout << "1. Soups and Salads\n";
    cout << "2. Starters\n";
    cout << "3. Main Course\n";
    cout << "4. Desserts\n";
    cout << "5. Shakes and Beverages\n";
}

void displayMenu(const vector<MenuItem>& menu, int sectionChoice, bool displayHeader = true) {
    if (displayHeader) {
        cout << "Menu:\n";
        cout << setw(5) << "Item " << setw(30) << "Name" << setw(15) << "  Price (Rs)\n";
    }

    for (int i = 0; i < menu.size(); ++i) {
        // Check if the item belongs to the selected section
        if ((sectionChoice == 1 && i < 9) || (sectionChoice == 2 && i >= 9 && i < 35) ||
            (sectionChoice == 3 && i >= 35 && i < 73) || (sectionChoice == 4 && i >= 73 && i < 79) ||
            (sectionChoice == 5 && i >= 79)) {
            cout << setw(5) << i + 1 << setw(30) << menu[i].itemName << setw(10) << "Rs " << menu[i].priceInRupees << endl;
        }
    }
}


void displayTables(const vector<Table>& tables) {
    cout << "Table\tStatus\tCustomer\n";
    for (const Table& table : tables) {
        cout << table.tableNumber << "\t" << (table.reserved ? "Reserved" : "Available") << "\t" << table.customerName << endl;
    }
}

void placeOrder(vector<Table>& tables, const vector<MenuItem>& menu, int tableNumber) {
    int sectionChoice, itemChoice, quantity;

    while (true) {
        displayMenu(menu);

        cout << "Enter the section number to view items (0 to finish): ";
        cin >> sectionChoice;

        if (sectionChoice == 0) {
            break; // Finish ordering
        } else if (sectionChoice < 1 || sectionChoice > 5) {
            cout << "Invalid section choice\n";
            continue;
        }

        while (true) {
            displayMenu(menu, sectionChoice);

            cout << "Enter the item number to order\n(0 to finish, -1 to go back to section selection): ";
            cin >> itemChoice;

            if (itemChoice == 0) {
                break; // Finish ordering from the current section
            } else if (itemChoice == -1) {
                break; // Go back to section selection
            } else if (itemChoice >= 1 && itemChoice <= menu.size()) {
                Order order; 
                order.itemName = menu[itemChoice - 1].itemName;
                order.priceInRupees = menu[itemChoice - 1].priceInRupees;

                cout << "Enter the quantity: ";
                cin >> quantity;
                order.quantity = quantity;
                
                
                tables[tableNumber - 1].orders.push_back(order);

            } else {
                cout << "Invalid choice\n";
            }
        }
    }

    cout << "Order placed successfully!\n";
}

void displayBill(const vector<Table>& tables, const vector<MenuItem>& menu, int tableNumber) {
    const Table& table = tables[tableNumber - 1];
    double totalAmount = 0.0;

    cout << "Bill for Table " << table.tableNumber << " (Customer: " << table.customerName << "):\n";
    cout << setw(15) << "Item " << setw(10) << " Quantity " << setw(10) << " Price (Rs) " << setw(15) << " Total (Rs)\n";

    for (const Order& order : table.orders) {
        cout << setw(15) << order.itemName << setw(10) << order.quantity << setw(10) << order.priceInRupees << setw(15)
             << order.quantity * order.priceInRupees << endl;

        totalAmount += order.quantity * order.priceInRupees;
    }

cout << "----------------------------------------------\n";
    cout << setw(35) << "Total: " << setw(15) << totalAmount << endl;
}

int main() {
    vector<MenuItem> menu = {
    // Soups and salads
    {"Tomato Soup", 170},
    {"Veg Sweet Corn Soup", 185},
    {"Veg Hot and Sour Soup", 185},
    {"Veg Manchow Soup", 185},
    {"Chicken Manchow Soup", 264},
    {"Chicken Sweet Corn Soup", 251},
    {"Chicken Hot and Sour Soup", 264},
    {"Sliced Green Salad", 145},
    {"Mexican Salad", 290},
    {"Chicken Mexican Salad", 330},

    // Starters
    {"Veggie Pizza Regular", 209},
    {"Medium", 379},
    {"Large", 609},
    {"Chicken Pizza Regular", 399},
    {"Medium", 699},
    {"Large", 1029},
    {"4 Cheese Pizza", 349},
    {"Paneer Pizza", 299},
    {"Veg Burger", 150},
    {"Chicken Burger", 210},
    {"Pasta", 270},
    {"Chicken Sandwich", 295},
    {"Veg Sandwich", 200},
    {"Cheese Sandwich", 250},
    {"Crispy Corn", 300},
    {"Veg Noodles", 150},
    {"Chicken Noodles", 240},
    {"Veg Manchuria", 110},
    {"Chicken Manchuria", 270},
    {"Chicken fingers", 275},
    {"Chicken Majestics", 370},
    {"Chilli Chicken", 375},
    {"Apollo Fish", 350},
    {"Loose Prawn", 410},

    // Main Course
    //Breads
    {"Roti", 50},    
    {"Butter Roti",75},
    {"Plain Naan", 60},
    {"Aloo Paratha",70 },
    {"Lachha Paratha", 80},
    {"Butter Naan", 85},
    {"Kulcha", 80},
    //Veg Curry
    {"Mix Veg Curry", 235},
    {"Veg Kadai", 250},
    {"Veg Kofta", 250},
    {"Paneer Butter Masala", 270},
    {"Paneer Methi Masala", 260},
    {"Paneer Tikka Masala", 275},
    {"Chilli Mushroom ", 300},
    //Non veg curry
    {"Egg Masala", 250},
    {"Chicken Curry", 415},
    {"Boneless Chicken Curry",450},
    {"Kadai Chicken", 415},
    {"Punjabi Chicken", 400},
    {"Butter Chicken", 475},
    {"Chicken Tikka Masala", 435},
    {"Mutton Curry",491 },
    {"Mutton Keema Curry", 510},
    {"Fish Curry", 567},
    {"Prawns Curry", 567},
    //Fried rice
    {"Veg Fried Rice", 330},
    {"Egg Fried Rice", 370},
    {"Chicken Fried Rice", 405},
    //veg
    {"Veg Biryani", 350},
    {"Paneer Biryani", 365},
    {"Cashewnut Biryani", 390},
    //Biryanis
    {"Chicken Dum Biryani", 495},
    {"Boneless Chicken Biryani", 520},
    {"Spl. Chicken Biryani", 550},
    {"Wings Biryani", 470},
    {"Hyderabadi Biryani", 515},
    {"Mutton Dum Biryani", 565},
    {"Fish Biryani", 567},
    {"prawn Biryani", 597},
    // Desserts
    {"Gulab jamun ice cream", 210},
    {"Strawberry ice cream", 210},
    {"Chocolate ice cream", 210},
    {"Butterscotch ice cream", 210},
    {"Vanilla ice cream", 200},
    {"Apricot Delight", 250},

    // Shakes and Beverages
    {"Strawberry Milkshake", 250},
    {"Chocolate Milkshake", 250},
    {"Kitkat Milkshake", 270},
    {"Flavored Thickshake", 275},
    {"Butter Milk", 120},
    {"Lassi", 125},
    {"Soda", 95},
    {"Mojito", 170},
    {"Blue lagoon", 180},
    {"Water bottle 500ml", 30}
};
    const int numTables = 6;
    vector<Table> tables(numTables);

    for (int i = 0; i < numTables; ++i) {
        tables[i].tableNumber = i + 1;
        tables[i].reserved = false;
    }

    int option;
    do {
        cout << "\nRestaurant Management System\n";
        cout << "1. Display Table Status\n";
        cout << "2. Reserve a Table\n";
        cout << "3. Place an Order\n";
        cout << "4. Display Bill\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1:
                displayTables(tables);
                break;
            case 2: {
                int tableNumber;
                cout << "Enter the table number to reserve: ";
                cin >> tableNumber;

                if (tableNumber >= 1 && tableNumber <= numTables) {
                    if (!tables[tableNumber - 1].reserved) {
                        cout << "Enter the name of the customer: ";
                        cin.ignore();
                        getline(cin, tables[tableNumber - 1].customerName);
                        tables[tableNumber - 1].reserved = true;
                        cout << "Table reserved successfully for " << tables[tableNumber - 1].customerName << "!\n";
                    } else {
                        cout << "Table is already reserved. Choose another table.\n";
                    }
                } else {
                    cout << "Invalid table number\n";
                }
                break;
            }
            case 3: {
                int tableNumber;
                cout << "Enter the table number to place an order: ";
                cin >> tableNumber;

                if (tableNumber >= 1 && tableNumber <= numTables) {
                    if (tables[tableNumber - 1].reserved) {
                        placeOrder(tables, menu, tableNumber);
                    } else {
                        cout << "Table is not reserved. Please reserve the table first.\n";
                    }
                } else {
                    cout << "Invalid table number\n";
                }
                break;
            }
            case 4: {
                int tableNumber;
                cout << "Enter the table number to display the bill: ";
                cin >> tableNumber;

                if (tableNumber >= 1 && tableNumber <= numTables) {
                    if (tables[tableNumber - 1].reserved) {
                        displayBill(tables, menu, tableNumber);
                    } else {
                        cout << "Table is not reserved. Please reserve the table first.\n";
                    }
                } else {
                    cout << "Invalid table number\n";
                }
                break;
            }
            case 5:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (option != 5);

    return 0;
}
