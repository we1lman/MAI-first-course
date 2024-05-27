#include "Computer.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

void writeComputers(const char* inputFilename, const char* outputFilename) {
    std::ifstream inputFile(inputFilename);
    if (!inputFile) {
        std::cerr << "The file could not be opened for reading: " << inputFilename << std::endl;
        return;
    }

    int count = 0;
    std::string line;
    while (std::getline(inputFile, line)) {
        ++count;
    }

    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    Computer* computers = new Computer[count];
    int index = 0;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        char surname[MAX_SURNAME];
        int cpu;
        char cpuType[MAX_TYPE];
        int memory;
        char videoType[MAX_CONTROLLER_TYPE];
        int videoMemory;
        char hddType[MAX_TYPE];
        int hddCnt;
        int hddCap;
        int integratedCnt;
        int peripheralCnt;
        char os[MAX_OS];

        iss >> surname >> cpu >> cpuType >> memory >> videoType >> videoMemory >> hddType
            >> hddCnt >> hddCap >> integratedCnt >> peripheralCnt >> os;

        computers[index] = Computer(surname, cpu, cpuType, memory, videoType, videoMemory, hddType,
                                    hddCnt, hddCap, integratedCnt, peripheralCnt, os);
        ++index;
    }

    inputFile.close();

    std::ofstream outputFile(outputFilename, std::ios::binary);
    if (!outputFile) {
        std::cerr << "The file could not be opened for writing: " << outputFilename << std::endl;
        delete[] computers;
        return;
    }

    outputFile.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (int i = 0; i < count; ++i) {
        outputFile.write(reinterpret_cast<const char*>(&computers[i]), sizeof(Computer));
    }

    outputFile.close();
    std::cout << "The " << outputFilename << " file has been successfully created." << std::endl;

    delete[] computers;
}

int main() {
    const char* inputFilename = "../include/data.txt";
    const char* outputFilename = "computer_inventory.dat";
    writeComputers(inputFilename, outputFilename);
    return 0;
}
