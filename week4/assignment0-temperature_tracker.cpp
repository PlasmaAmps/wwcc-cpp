#include <iostream>
#include <iomanip>
using namespace std;

const int NUM_DAYS = 7;

int main() {
    double temperatures[NUM_DAYS];
    double sum = 0.0;
    double average;
    int highestIndex = 0;
    int lowestIndex = 0;

    cout << "Temperature Tracker\n";
    cout << "------------------\n";

    // Input temperatures
    for (int i = 0; i < NUM_DAYS; ++i) {
        cout << "Enter temperature for day " << (i + 1) << ": ";
        cin >> temperatures[i];

        // Track sum for average
        sum += temperatures[i];

        // Check for highest/lowest
        if (temperatures[i] > temperatures[highestIndex]) {
            highestIndex = i;
        }
        if (temperatures[i] < temperatures[lowestIndex]) {
            lowestIndex = i;
        }
    }

    average = sum / NUM_DAYS;

    // Display analysis
    cout << fixed << setprecision(1);
    cout << "\nTemperature Analysis:\n";
    cout << "Highest temperature: " << temperatures[highestIndex] << "°F (day " << (highestIndex + 1) << ")\n";
    cout << "Lowest temperature: " << temperatures[lowestIndex] << "°F (day " << (lowestIndex + 1) << ")\n";
    cout << "Average temperature: " << average << "°F\n";

    // Display above-average days
    cout << "\nDays with above-average temperatures:\n";
    bool anyAboveAverage = false;
    for (int i = 0; i < NUM_DAYS; ++i) {
        if (temperatures[i] > average) {
            cout << "- Day " << (i + 1) << ": " << temperatures[i] << "°F\n";
            anyAboveAverage = true;
        }
    }
    if (!anyAboveAverage) {
        cout << "None\n";
    }

    // Bonus: ASCII Temperature Chart
    cout << "\nTemperature Chart:\n";
    for (int i = 0; i < NUM_DAYS; ++i) {
        cout << "Day " << (i + 1) << " (" << temperatures[i] << "°F): ";
        int asterisks = static_cast<int>(temperatures[i] / 10);
        for (int j = 0; j < asterisks; ++j) {
            cout << "*";
        }
        cout << ".\n";
    }

    return 0;
}
