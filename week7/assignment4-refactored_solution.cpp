// A class for managing a bank account
#include <string> //Added for the use of string in the later part of the code to help it work properly. I also went through and changed each string to std::string to help it work properly.
#include <iostream> // Added for the use of cout and endl in the later part of the code to help it work properly.
#include <iomanip> // Added for the use of setprecision in the later part of the code to help it work properly.


// Constants to replace magic numbers
static constexpr double SAVINGS_INTEREST = 0.03;
static constexpr double CHECKING_INTEREST = 0.01;
static constexpr double BUSINESS_INTEREST = 0.005;

//changed account to Account for consistency.
class Account {
private:
    // Made all data members private
    std::string customerName;
    double balance;
    bool isOpen;
    int accountNumber;
    std::string accountType;

public:
// Constructor replaces setup function
    Account(const std::string& name, int number, const std::string& type) {
        customerName = name;
        accountNumber = number;
        accountType = type;
        balance = 0.0;
        isOpen = true;

        // Validation: Ensure type is valid
        if (type != "savings" && type != "checking" && type != "business") {
             std::cerr << "Invalid account type. Defaulting to checking." << std::endl;
            accountType = "checking";
         }
    }
        
// Deposit function with validation
    void deposit(double amount) {
        if (!isOpen) {
        std::cerr << "Cannot deposit to a closed account." << std::endl;
        return;
        }
        if (amount > 0) {
            balance += amount;
        } else {
            std::cerr << "Deposit amount must be positive." << std::endl;
        }
    }

// Withdraw function with balance check
    void withdraw(double amount) {
        if (!isOpen) {
            std::cerr << "Cannot withdraw from a closed account." << std::endl;
            return;
        }

        if (amount < 0) {
            std::cerr << "Withdrawal amount must be positive." << std::endl;
        } else if (amount > balance) {
            std::cerr << "Insufficient funds for withdrawal." << std::endl;
        } else {
            balance -= amount;
        }
    }

    // Apply interest based on account type, with the constants made above.
    void do_interest() {
        if (!isOpen) return;

        if (accountType == "savings") {
            balance *= (1.0 + SAVINGS_INTEREST);
        } else if (accountType == "checking") {
            balance *= (1.0 + CHECKING_INTEREST);
        } else if (accountType == "business") {
            balance *= (1.0 + BUSINESS_INTEREST);
        }
    }

// 📋 Print function with const correctness and formatting
    void print() const {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Customer Name: " << customerName << std::endl;
        std::cout << "Balance: $" << balance << std::endl;
        std::cout << "Account Type: " << accountType << std::endl;
        std::cout << "Status: " << (isOpen ? "Open" : "Closed") <<    std::endl;
    }

    // Close account safely
    void close() {
        isOpen = false;
    }

    // Getter with const correctness
    double getBalance() const {
        return balance;
    }

    bool getIsOpen() const {
        return isOpen;
    }

    std::string getAccountType() const {
        return accountType;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    std::string getCustomerName() const {
        return customerName;
    }
};


/*
int main() {
    Account acc1("John Smith", 12345, "savings");

    acc1.deposit(1000);
    acc1.withdraw(250);
    acc1.do_interest();
    acc1.print();

    acc1.close();

    // Trying actions on closed account:
    acc1.deposit(100); // Should display error

    return 0;
}
*/