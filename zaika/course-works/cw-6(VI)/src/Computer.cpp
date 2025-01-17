#include "Computer.hpp"
#include <fstream>
#include <iostream>

Computer* readComputers(const char* filename, int& count) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        count = 0;
        return nullptr;
    }

    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    Computer* computers = new Computer[count];
    for (int i = 0; i < count; ++i) {
        file.read(reinterpret_cast<char*>(&computers[i]), sizeof(Computer));
    }

    file.close();
    return computers;
}

void printComputersNeedingUpgrade(Computer* computers, int count, int p) {
    for (int i = 0; i < count; ++i) {
        int integratedCount = computers[i].getIntegratedControllerCount();
        int peripheralCount = computers[i].getPeripheralDeviceCount();
        int totalDevices = integratedCount + peripheralCount;

        if (totalDevices > p) {
            std::cout << computers[i].getOwnerSurname() << std::endl;
        }
    }
}
