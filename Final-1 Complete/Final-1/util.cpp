#include "util.h"
#include <iostream>
#include <limits>

namespace Util {

    int getChoice(int maxOption) {
        int choice;  

        while (true) {
            std::cout << "Enter choice (1-" << maxOption << "): ";
            if (std::cin >> choice) {
                if (choice >= 1 && choice <= maxOption) {
                    return choice;
                }
            }
            std::cout << "Invalid input. Please enter a number between 1 and " << maxOption << ".\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}