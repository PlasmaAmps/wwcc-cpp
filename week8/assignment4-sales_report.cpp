#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

struct ProductInfo {
    string productName;
    string category;
    int totalUnitsSold = 0;
    double unitPrice = 0.0;
    double totalRevenue = 0.0;
};

void getCurrentDateTime(string& outDateTime) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << put_time(ltm, "%Y-%m-%d %H:%M:%S");
    outDateTime = ss.str();
}

void reportError(int lineNumber, const string& reason) {
    cerr << "Error (line " << lineNumber << "): " << reason << endl;
}

int main() {
    ifstream inputFile("sales_data.txt");
    ofstream outputFile("sales_summary.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open sales_data.txt" << endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        cerr << "Failed to open sales_summary.txt" << endl;
        return 1;
    }

    map<string, map<string, ProductInfo>> categoryMap;
    map<string, double> categoryRevenue;
    map<string, int> categoryUnits;

    int lineNumber = 0;
    int totalTransactions = 0;
    int totalUnitsSold = 0;
    double totalRevenue = 0.0;

    string bestProduct;
    double bestRevenue = 0.0;

    string line;
    while (getline(inputFile, line)) {
        lineNumber++;
        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        string date, product, category;
        int quantity;
        double unitPrice;

        if (!(ss >> date >> product >> category >> quantity >> unitPrice)) {
            reportError(lineNumber, "Malformed line or missing data");
            continue;
        }

        if (quantity <= 0) {
            reportError(lineNumber, "Quantity must be a positive integer");
            continue;
        }

        if (unitPrice <= 0.0) {
            reportError(lineNumber, "Unit price must be a positive number");
            continue;
        }

        double revenue = quantity * unitPrice;

        ProductInfo& pInfo = categoryMap[category][product];
        pInfo.productName = product;
        pInfo.category = category;
        pInfo.totalUnitsSold += quantity;
        pInfo.unitPrice = unitPrice; // assuming unit price is consistent
        pInfo.totalRevenue += revenue;

        categoryRevenue[category] += revenue;
        categoryUnits[category] += quantity;

        totalRevenue += revenue;
        totalUnitsSold += quantity;
        totalTransactions++;

        if (pInfo.totalRevenue > bestRevenue) {
            bestRevenue = pInfo.totalRevenue;
            bestProduct = product;
        }
    }

    // Generate report header
    string currentDateTime;
    getCurrentDateTime(currentDateTime);
    outputFile << "SALES SUMMARY REPORT\n";
    outputFile << "Generated: " << currentDateTime << "\n";
    outputFile << "=====================================\n\n";

    // Table Header
    outputFile << left << setw(20) << "Product"
               << setw(15) << "Category"
               << right << setw(12) << "Units Sold"
               << setw(12) << "Unit Price"
               << setw(15) << "Total Revenue" << "\n";

    outputFile << string(20, '-') << "  "
               << string(15, '-') << "  "
               << string(11, '-') << "  "
               << string(11, '-') << "  "
               << string(14, '-') << "\n";

    outputFile << fixed << setprecision(2);

    for (const auto& categoryPair : categoryMap) {
        const string& category = categoryPair.first;
        const auto& products = categoryPair.second;

        for (const auto& productPair : products) {
            const ProductInfo& p = productPair.second;

            outputFile << left << setw(20) << p.productName
                       << setw(15) << p.category
                       << right << setw(12) << p.totalUnitsSold
                       << setw(12) << p.unitPrice
                       << setw(15) << p.totalRevenue << "\n";
        }

        // Category Subtotal
        outputFile << " " << setw(35) << " "
                   << right << setw(12) << categoryUnits[category]
                   << setw(15) << " "
                   << setw(15) << categoryRevenue[category] << "\n\n";
    }

    outputFile << "=====================================\n";
    outputFile << "SUMMARY STATISTICS\n";
    outputFile << "=====================================\n";
    outputFile << "Total Products Sold: " << categoryMap.size() << "\n";
    outputFile << "Total Units Sold: " << totalUnitsSold << "\n";
    outputFile << "Total Revenue: $" << totalRevenue << "\n";
    if (totalTransactions > 0)
        outputFile << "Average Sale Value: $" << (totalRevenue / totalTransactions) << "\n";
    else
        outputFile << "Average Sale Value: $0.00\n";

    outputFile << "Best-Selling Product: " << bestProduct << " ($" << bestRevenue << ")\n";

    inputFile.close();
    outputFile.close();

    cout << "Report generated: sales_summary.txt" << endl;
    return 0;
}
