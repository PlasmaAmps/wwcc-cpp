#include <iostream>
#include <iomanip>

const double PI = 3.14159;

class Rectangle {
private:
    double length;
    double width;

public:
    // Constructor
    Rectangle(double l, double w);

    // Getter methods
    double getLength() const;
    double getWidth() const;

    // Area method (returns double)
    double area() const;

    // Overloaded area method (reference parameter)
    void area(double& result) const;

    // resize method with method chaining
    Rectangle& resize(double newLength, double newWidth);

    // Print rectangle info
    void print() const;
};

// Rectangle method definitions outside class
Rectangle::Rectangle(double l, double w) : length(l), width(w) {}

double Rectangle::getLength() const {
    return length;
}

double Rectangle::getWidth() const {
    return width;
}

double Rectangle::area() const {
    return length * width;
}

void Rectangle::area(double& result) const {
    result = length * width;
}

Rectangle& Rectangle::resize(double newLength, double newWidth) {
    this->length = newLength;  // using this pointer
    this->width = newWidth;
    return *this;  // return reference to the current object
}

void Rectangle::print() const {
    std::cout << "Rectangle (Length: " << length << ", Width: " << width << ")\n";
}

class Circle {
private:
    double radius;

public:
    // Constructor
    Circle(double r) : radius(r) {}

    // Const methods for area and circumference
    double area() const {
        return PI * radius * radius;
    }

    double circumference() const {
        return 2 * PI * radius;
    }

    // Overloaded print methods
    void print() const {
        std::cout << "Circle (Radius: " << radius << ")\n";
        std::cout << "Area: " << std::fixed << std::setprecision(2) << area() << "\n";
        std::cout << "Circumference: " << std::fixed << std::setprecision(2) << circumference() << "\n";
    }

    void print(bool detailed) const {
        if (!detailed) {
            print();
        } else {
            std::cout << "Circle details:\n";
            std::cout << "Radius: " << radius << "\n";
            std::cout << "Area: π × radius² = " << PI << " × " << (radius * radius) << " = " << std::fixed << std::setprecision(2) << area() << "\n";
            std::cout << "Circumference: 2 × π × radius = 2 × " << PI << " × " << radius << " = " << std::fixed << std::setprecision(2) << circumference() << "\n";
        }
    }
};

int main() {
    std::cout << "SHAPE CALCULATOR\n---------------\n\n";

    // Rectangle
    Rectangle rect(5, 3);
    rect.print();
    std::cout << "Area: " << rect.area() << "\n";

    double refArea;
    rect.area(refArea);
    std::cout << "Passing area by reference: " << refArea << "\n\n";

    // Circle
    Circle circle(4);
    circle.print();
    std::cout << "\n";
    circle.print(true);

    std::cout << "\nMethod chaining demonstration:\n";
    std::cout << "Original rectangle: Length = " << rect.getLength() << ", Width = " << rect.getWidth() << "\n";
    rect.resize(10, 6).print();

    return 0;
}
