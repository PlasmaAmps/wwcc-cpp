// Product.h
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
#include <iomanip>

class Product {
private:
    std::string id;
    std::string name;
    double price;
    int quantity;

public:
    Product(std::string id, std::string name, double price, int quantity);

    std::string getID() const;
    std::string getName() const;
    double getPrice() const;
    int getQuantity() const;

    void setPrice(double newPrice);
    void setQuantity(int newQuantity);

    void addStock(int amount);
    void removeStock(int amount);

    void display() const;
};

#endif // PRODUCT_H
