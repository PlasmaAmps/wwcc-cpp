// assignment3-main.cpp
#include "Product.h"
#include "Inventory.h"
#include <iostream>
#include <limits>
using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Inventory inventory;
    int choice;

    do {
        cout << "\nPRODUCT INVENTORY SYSTEM\n";
        cout << "------------------------\n";
        cout << "MAIN MENU:\n";
        cout << "1. Add New Product\n";
        cout << "2. Display All Products\n";
        cout << "3. Search for a Product\n";
        cout << "4. Update Product\n";
        cout << "5. Add Stock\n";
        cout << "6. Remove Stock\n";
        cout << "7. Display Inventory Statistics\n";
        cout << "8. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        clearInput();

        switch (choice) {
            case 1: {
                string id, name;
                double price;
                int quantity;
                cout << "\nADD NEW PRODUCT\n--------------\n";
                cout << "Enter product ID: ";
                getline(cin, id);
                cout << "Enter product name: ";
                getline(cin, name);
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter initial quantity: ";
                cin >> quantity;
                clearInput();
                Product newProduct(id, name, price, quantity);
                inventory.addProduct(newProduct);
                cout << "Product added successfully!\n";
                break;
            }
            case 2:
                cout << "\nALL PRODUCTS\n-----------\n";
                inventory.listAllProducts();
                break;
            case 3: {
                string query;
                cout << "\nSEARCH FOR A PRODUCT\n--------------------\n";
                cout << "Enter product ID or name: ";
                getline(cin, query);
                Product* found = inventory.findProductByID(query);
                if (!found) found = inventory.findProductByName(query);
                if (found) found->display();
                else cout << "Product not found.\n";
                break;
            }
            case 4: {
                string id;
                double newPrice;
                int newQuantity;
                cout << "\nUPDATE PRODUCT\n--------------\n";
                cout << "Enter product ID to update: ";
                getline(cin, id);
                cout << "Enter new price: ";
                cin >> newPrice;
                cout << "Enter new quantity: ";
                cin >> newQuantity;
                clearInput();
                if (inventory.updateProduct(id, newPrice, newQuantity))
                    cout << "Product updated successfully.\n";
                else
                    cout << "Product not found.\n";
                break;
            }
            case 5: {
                string id;
                int amount;
                cout << "\nADD STOCK\n---------\n";
                cout << "Enter product ID: ";
                getline(cin, id);
                cout << "Enter amount to add: ";
                cin >> amount;
                clearInput();
                Product* p = inventory.findProductByID(id);
                if (p) {
                    p->addStock(amount);
                    cout << "Stock added.\n";
                } else cout << "Product not found.\n";
                break;
            }
            case 6: {
                string id;
                int amount;
                cout << "\nREMOVE STOCK\n------------\n";
                cout << "Enter product ID: ";
                getline(cin, id);
                cout << "Enter amount to remove: ";
                cin >> amount;
                clearInput();
                Product* p = inventory.findProductByID(id);
                if (p) {
                    p->removeStock(amount);
                    cout << "Stock removed.\n";
                } else cout << "Product not found.\n";
                break;
            }
            case 7: {
                cout << "\nINVENTORY STATISTICS\n--------------------\n";
                cout << "Total number of products: " << inventory.totalProductCount() << endl;
                cout << fixed << setprecision(2);
                cout << "Total inventory value: $" << inventory.calculateTotalValue() << endl;
                cout << "Out of stock products: \n";
                inventory.listOutOfStock();
                cout << "Low stock products (5 or fewer): \n";
                inventory.listLowStock();
                break;
            }
            case 8:
                cout << "Thank you for using the Product Inventory System. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 8);

    return 0;
}
