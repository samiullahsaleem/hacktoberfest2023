#include "Utils.h"
#include <iostream>

namespace sdds {
    int getInt(int min, int max) {
        int value;
        bool done = false;
        while (!done) {
            std::cin >> value;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cout << "Invalid Integer, try again: ";
            }
            else if (value < min || value > max) {
                std::cout << "[" << min << "<=value<=" << max << "], retry: > ";
            }
            else {
                done = true;
            }
            std::cin.ignore(1000, '\n');
        }
        return value;
    }
}
