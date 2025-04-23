// assignment0-distance_calculator.cpp
#include <iostream>
#include <cmath>        // For sqrt()
#include <iomanip>      // For setting decimal precision
#include <utility>      // For std::pair

using namespace std;

// Function to calculate distance between two points
double calculateDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Bonus: Function to calculate the midpoint between two points
pair<double, double> calculateMidpoint(double x1, double y1, double x2, double y2) {
    double midX = (x1 + x2) / 2.0;
    double midY = (y1 + y2) / 2.0;
    return make_pair(midX, midY);
}

int main() {
    double x1, y1, x2, y2;

    // Prompt the user to enter coordinates
    cout << "Enter the coordinates of the first point:\n";
    cout << "x1: ";
    cin >> x1;
    cout << "y1: ";
    cin >> y1;

    cout << "Enter the coordinates of the second point:\n";
    cout << "x2: ";
    cin >> x2;
    cout << "y2: ";
    cin >> y2;

    // Calculate distance
    double distance = calculateDistance(x1, y1, x2, y2);

    // Set precision to 2 decimal places
    cout << fixed << setprecision(2);

    // Output the result
    cout << "The distance between (" << x1 << "," << y1 << ") and ("
         << x2 << "," << y2 << ") is: " << distance << endl;

    // Bonus: Output midpoint
    pair<double, double> midpoint = calculateMidpoint(x1, y1, x2, y2);
    cout << "The midpoint between the two points is: ("
         << midpoint.first << ", " << midpoint.second << ")" << endl;

    return 0;
}
