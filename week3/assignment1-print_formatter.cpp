#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>

// Function to format an integer with commas (e.g., 1234567 -> "1,234,567")
std::string format(int number) {
    std::string result;
    std::string numStr = std::to_string(std::abs(number));
    int count = 0;

    // Add digits from right to left and insert commas every 3 digits
    for (int i = numStr.length() - 1; i >= 0; --i) {
        result.insert(0, 1, numStr[i]);
        count++;
        if (count % 3 == 0 && i != 0) {
            result.insert(0, 1, ',');
        }
    }

    // Add minus sign for negative numbers
    if (number < 0) {
        result.insert(0, 1, '-');
    }

    return result;
}

// Function to format a double to 2 decimal places
std::string format(double number) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << number;
    return out.str();
}

// Function to format a double to a custom number of decimal places
std::string format(double number, int precision) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << number;
    return out.str();
}

// Function to capitalize the first letter of each word in a string
std::string format(const std::string& text) {
    std::string result = text;

    bool capitalizeNext = true;
    for (size_t i = 0; i < result.length(); ++i) {
        if (std::isspace(result[i])) {
            capitalizeNext = true;
        } else if (capitalizeNext) {
            result[i] = std::toupper(result[i]);
            capitalizeNext = false;
        }
    }

    return result;
}

// Bonus: Function to convert string to upper or lower case
std::string format(const std::string& text, bool toUpper) {
    std::string result = text;
    if (toUpper) {
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    } else {
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    }
    return result;
}

// Main function demonstrating all format() overloads
int main() {
    std::cout << "Integer formatting:\n";
    int num = 1234567;
    std::cout << "Original: " << num << "\n";
    std::cout << "Formatted: " << format(num) << "\n\n";

    std::cout << "Double formatting (default 2 decimal places):\n";
    double dnum = 45.6789;
    std::cout << "Original: " << dnum << "\n";
    std::cout << "Formatted: " << format(dnum) << "\n\n";

    std::cout << "Double formatting (custom decimal places):\n";
    std::cout << "Original: " << dnum << " with precision 3\n";
    std::cout << "Formatted: " << format(dnum, 3) << "\n\n";

    std::cout << "String formatting:\n";
    std::string phrase = "hello world of c++ programming";
    std::cout << "Original: \"" << phrase << "\"\n";
    std::cout << "Formatted: \"" << format(phrase) << "\"\n\n";

    std::cout << "Bonus: String uppercase/lowercase:\n";
    std::cout << "Upper: \"" << format(phrase, true) << "\"\n";
    std::cout << "Lower: \"" << format(phrase, false) << "\"\n";

    return 0;
}
