#include <iostream>
#include <iomanip> 
#include <cctype>  

using namespace std;

// Function to check if temperature is valid
bool isValidTemperature(double value, char unit, string& warning) {
    switch (toupper(unit)) {
        case 'C':
            if (value < -273.15) {
                warning = "Error: Temperature below absolute zero in Celsius!";
                return false;
            }
            break;
        case 'F':
            if (value < -459.67) {
                warning = "Error: Temperature below absolute zero in Fahrenheit!";
                return false;
            }
            break;
        case 'K':
            if (value < 0) {
                warning = "Error: Temperature below absolute zero in Kelvin!";
                return false;
            }
            break;
        default:
            warning = "Invalid unit.";
            return false;
    }
    return true;
}

// Function to convert temperature to all three units
void convertTemperature(double inputValue, char unit,
                        double& celsius, double& fahrenheit, double& kelvin) {
    switch (toupper(unit)) {
        case 'C':
            celsius = inputValue;
            fahrenheit = (inputValue * 9 / 5) + 32;
            kelvin = inputValue + 273.15;
            break;
        case 'F':
            celsius = (inputValue - 32) * 5 / 9;
            fahrenheit = inputValue;
            kelvin = celsius + 273.15;
            break;
        case 'K':
            celsius = inputValue - 273.15;
            fahrenheit = (celsius * 9 / 5) + 32;
            kelvin = inputValue;
            break;
    }
}

int main() {
    double inputValue;
    char unit;
    double celsius, fahrenheit, kelvin;
    string warning;

    cout << "Enter a temperature value: ";
    cin >> inputValue;

    cout << "Enter the unit (C for Celsius, F for Fahrenheit, K for Kelvin): ";
    cin >> unit;

    // Validate unit input
    unit = toupper(unit);
    if (unit != 'C' && unit != 'F' && unit != 'K') {
        cout << "Invalid unit entered. Please use C, F, or K." << endl;
        return 1;
    }

    // Check for valid temperature
    if (!isValidTemperature(inputValue, unit, warning)) {
        cout << warning << endl;
        return 1;
    }

    // Perform conversion
    convertTemperature(inputValue, unit, celsius, fahrenheit, kelvin);

    // Set floating-point formatting
    cout << fixed << setprecision(2);
    cout << "\nTemperature Conversions:" << endl;
    cout << "Celsius: " << celsius << "°C" << endl;
    cout << "Fahrenheit: " << fahrenheit << "°F" << endl;
    cout << "Kelvin: " << kelvin << "K" << endl;

    return 0;
}
