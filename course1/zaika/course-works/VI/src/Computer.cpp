#include "../include/Computer.hpp"
#include <fstream>
#include <iostream>

Computer* readComputers(const char* filename, int& count) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "failed to open file: " << filename << std::endl;
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
        // Получение количества интегрированных контроллеров и периферийных устройств
        int integratedCount = computers[i].getIntegratedControllerCount();
        int peripheralCount = computers[i].getPeripheralDeviceCount();

        // Суммирование этих значений
        int totalDevices = integratedCount + peripheralCount;

        // Проверка условия и вывод фамилии владельца, если условие выполнено
        if (totalDevices > p) {
            std::cout << computers[i].getOwnerSurname() << std::endl;
        }
    }
}