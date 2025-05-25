// Inventory.cpp
#include "Inventory.h"
#include <iostream>
#include <iomanip>

void Inventory::addProduct(const Product& product) {
    products.push_back(product);
}

bool Inventory::removeProductByID(const std::string& id) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getID() == id) {
            products.erase(it);
            return true;
        }
    }
    return false;
}

Product* Inventory::findProductByID(const std::string& id) {
    for (auto& product : products) {
        if (product.getID() == id) {
            return &product;
        }
    }
    return nullptr;
}

Product* Inventory::findProductByName(const std::string& name) {
    for (auto& product : products) {
        if (product.getName() == name) {
            return &product;
        }
    }
    return nullptr;
}

void Inventory::listAllProducts() const {
    if (products.empty()) {
        std::cout << "No products in inventory." << std::endl;
        return;
    }
    for (const auto& product : products) {
        product.display();
    }
}

void Inventory::listOutOfStock() const {
    bool found = false;
    for (const auto& product : products) {
        if (product.getQuantity() == 0) {
            product.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No out-of-stock products." << std::endl;
    }
}

void Inventory::listLowStock() const {
    bool found = false;
    for (const auto& product : products) {
        if (product.getQuantity() > 0 && product.getQuantity() <= LOW_STOCK_THRESHOLD) {
            product.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No low-stock products." << std::endl;
    }
}

bool Inventory::updateProduct(const std::string& id, double newPrice, int newQuantity) {
    Product* product = findProductByID(id);
    if (product) {
        product->setPrice(newPrice);
        product->setQuantity(newQuantity);
        return true;
    }
    return false;
}

double Inventory::calculateTotalValue() const {
    double total = 0.0;
    for (const auto& product : products) {
        total += product.getPrice() * product.getQuantity();
    }
    return total;
}

int Inventory::totalProductCount() const {
    return products.size();
}
