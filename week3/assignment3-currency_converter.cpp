#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Static variable to track number of conversions performed
static int conversionCount = 0;

// Conversion functions
// Convert USD to EUR
double dollarToEuro(double amount) {
    conversionCount++;
    return amount * 0.85;
}

// Convert USD to GBP
double dollarToPound(double amount) {
    conversionCount++;
    return amount * 0.74;
}

// Convert USD to JPY
double dollarToYen(double amount) {
    conversionCount++;
    return amount * 110.33;
}

// Returns total number of conversions performed
int getConversionCount() {
    return conversionCount;
}

// Print conversion history
void printConversionHistory(string history[], int count) {
    if (count == 0) {
        cout << "\nNo conversions were performed in this session." << endl;
        return;
    }
    cout << "\nConversion History:" << endl;
    for (int i = 0; i < count; ++i) {
        cout << i + 1 << ". " << history[i] << endl;
    }
}

int main() {
    int choice;
    double amount;
    double result;
    char again;
    const int MAX_HISTORY = 100;
    string history[MAX_HISTORY];
    int historyCount = 0;

    do {
        // Display menu
        cout << "\nCURRENCY CONVERTER" << endl;
        cout << "------------------" << endl;
        cout << "1. Convert USD to Euro (EUR)" << endl;
        cout << "2. Convert USD to British Pound (GBP)" << endl;
        cout << "3. Convert USD to Japanese Yen (JPY)" << endl;
        cout << "4. Exit" << endl;

        cout << "\nEnter your choice (1-4): ";
        cin >> choice;

        if (choice >= 1 && choice <= 3) {
            cout << "Enter amount in USD: ";
            cin >> amount;

            // Perform conversion based on choice
            switch (choice) {
                case 1:
                    result = dollarToEuro(amount);
                    cout << fixed << setprecision(2);
                    cout << amount << " USD = " << result << " EUR" << endl;
                    history[historyCount++] = to_string(amount) + " USD -> " + to_string(result) + " EUR";
                    break;
                case 2:
                    result = dollarToPound(amount);
                    cout << fixed << setprecision(2);
                    cout << amount << " USD = " << result << " GBP" << endl;
                    history[historyCount++] = to_string(amount) + " USD -> " + to_string(result) + " GBP";
                    break;
                case 3:
                    result = dollarToYen(amount);
                    cout << fixed << setprecision(2);
                    cout << amount << " USD = " << result << " JPY" << endl;
                    history[historyCount++] = to_string(amount) + " USD -> " + to_string(result) + " JPY";
                    break;
            }

            // Display conversion count
            cout << "\nNumber of conversions performed: " << getConversionCount() << endl;
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice. Please select an option between 1 and 4." << endl;
        }

        cout << "\nWould you like to perform another conversion? (y/n): ";
        cin >> again;
    } while (again == 'y' || again == 'Y');

    // Print conversion history on exit
    printConversionHistory(history, historyCount);

    cout << "\nThank you for using the Currency Converter!" << endl;
    return 0;
}
