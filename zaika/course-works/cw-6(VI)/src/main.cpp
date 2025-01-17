#include "Computer.hpp"
#include <iostream>

int main() {
    const char* filename = "computer_inventory.bin";
    int p;
    std::cout << "Enter value p: ";
    std::cin >> p;

    int count;
    Computer* computers = readComputers(filename, count);
    if (computers) {
        printComputersNeedingUpgrade(computers, count, p);
        delete[] computers;
    }

    return 0;
}
