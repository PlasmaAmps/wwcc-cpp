// assignment1-sales_analysis.cpp
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    const int DAYS_IN_WEEK = 7;
    const string dayNames[DAYS_IN_WEEK] = {
        "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
    };
    double sales[DAYS_IN_WEEK];
    double totalSales = 0.0;
    double averageSales;
    int bestDayIndex = 0, worstDayIndex = 0;
    int daysAboveAverage = 0;
    double weekendSales = 0.0;

    cout << fixed << setprecision(2);
    cout << "WEEKLY SALES ANALYSIS\n---------------------\n";

    // Input sales for each day
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        cout << "Enter sales for " << dayNames[i] << ": ";
        cin >> sales[i];
        totalSales += sales[i];

        // Track weekend sales (Saturday = index 5, Sunday = index 6)
        if (i == 5 || i == 6) {
            weekendSales += sales[i];
        }
    }

    averageSales = totalSales / DAYS_IN_WEEK;

    // Find best and worst days
    for (int i = 1; i < DAYS_IN_WEEK; i++) {
        if (sales[i] > sales[bestDayIndex]) bestDayIndex = i;
        if (sales[i] < sales[worstDayIndex]) worstDayIndex = i;
    }

    // Count days above average
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        if (sales[i] > averageSales) {
            daysAboveAverage++;
        }
    }

    double weekendPercentage = (weekendSales / totalSales) * 100.0;

    // Output results
    cout << "\nSales Summary:\n";
    cout << "Total Sales: $" << totalSales << endl;
    cout << "Average Daily Sales: $" << averageSales << endl;

    cout << "\nBest Day: " << dayNames[bestDayIndex] << " with $" << sales[bestDayIndex] << endl;
    cout << "Worst Day: " << dayNames[worstDayIndex] << " with $" << sales[worstDayIndex] << endl;

    cout << "\nDays above average: " << daysAboveAverage << endl;
    cout << "Weekend sales: $" << weekendSales << " (" << setprecision(1) << weekendPercentage << "% of total)" << endl;

    // Bonus: Sales distribution chart
    cout << "\nSales Distribution:\n";
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        double percentage = (sales[i] / totalSales) * 100.0;
        int barLength = static_cast<int>(percentage / 1.25); // 1 block = 1.25%

        cout << left << setw(10) << dayNames[i] << ": ";
        cout << right << setw(5) << setprecision(1) << percentage << "% ";
        for (int j = 0; j < barLength; j++) {
            cout << "\u2588"; // The Unicode block character
        }
        cout << endl;
    }

    return 0;
}
