// Inventory.h
#ifndef INVENTORY_H
#define INVENTORY_H

#include "Product.h"
#include <vector>
#include <string>

class Inventory {
private:
    std::vector<Product> products;
    const int LOW_STOCK_THRESHOLD = 5;

public:
    void addProduct(const Product& product);
    bool removeProductByID(const std::string& id);
    Product* findProductByID(const std::string& id);
    Product* findProductByName(const std::string& name);

    void listAllProducts() const;
    void listOutOfStock() const;
    void listLowStock() const;

    bool updateProduct(const std::string& id, double newPrice, int newQuantity);
    double calculateTotalValue() const;
    int totalProductCount() const;
};

#endif // INVENTORY_H
