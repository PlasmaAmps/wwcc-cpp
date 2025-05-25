// Product.cpp
#include "Product.h"

Product::Product(std::string id, std::string name, double price, int quantity)
    : id(id), name(name) {
    setPrice(price);
    setQuantity(quantity);
}

std::string Product::getID() const {
    return id;
}

std::string Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

void Product::setPrice(double newPrice) {
    if (newPrice >= 0) {
        price = newPrice;
    } else {
        std::cerr << "Invalid price. Price must be non-negative." << std::endl;
    }
}

void Product::setQuantity(int newQuantity) {
    if (newQuantity >= 0) {
        quantity = newQuantity;
    } else {
        std::cerr << "Invalid quantity. Quantity must be non-negative." << std::endl;
    }
}

void Product::addStock(int amount) {
    if (amount > 0) {
        quantity += amount;
    } else {
        std::cerr << "Invalid stock amount. Must be positive." << std::endl;
    }
}

void Product::removeStock(int amount) {
    if (amount > 0 && amount <= quantity) {
        quantity -= amount;
    } else {
        std::cerr << "Invalid stock removal amount." << std::endl;
    }
}

void Product::display() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "ID: " << id << " | Name: " << name
              << " | Price: $" << price << " | In Stock: " << quantity << std::endl;
}
