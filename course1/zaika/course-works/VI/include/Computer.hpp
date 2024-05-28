#ifndef COMPUTER_HPP
#define COMPUTER_HPP

#include <iostream>
#include <cstring>

const int MAX_SURNAME = 30;
const int MAX_TYPE = 10;
const int MAX_CONTROLLER_TYPE = 15;
const int MAX_OS = 20;

class Computer {
private:
    char ownerSurname[MAX_SURNAME];
    int cpuCount;
    char cpuType[MAX_TYPE];
    int memorySize;
    char videoControllerType[MAX_CONTROLLER_TYPE];
    int videoMemorySize;
    char hddType[MAX_TYPE];
    int hddCount;
    int hddCapacity;
    int integratedControllerCount;
    int peripheralDeviceCount;
    char os[MAX_OS];

public:
    Computer(const char* surname = "", int cpu = 0, const char* cpuType = "", int memory = 0, const char* videoType = "",
             int videoMemory = 0, const char* hddType = "", int hddCnt = 0, int hddCap = 0,
             int integratedCnt = 0, int peripheralCnt = 0, const char* osType = "")
    {
        strncpy(ownerSurname, surname, MAX_SURNAME);
        ownerSurname[MAX_SURNAME - 1] = '\0';
        cpuCount = cpu;
        strncpy(this->cpuType, cpuType, MAX_TYPE);
        this->cpuType[MAX_TYPE - 1] = '\0';
        memorySize = memory;
        strncpy(videoControllerType, videoType, MAX_CONTROLLER_TYPE);
        videoControllerType[MAX_CONTROLLER_TYPE - 1] = '\0';
        videoMemorySize = videoMemory;
        strncpy(this->hddType, hddType, MAX_TYPE);
        this->hddType[MAX_TYPE - 1] = '\0';
        hddCount = hddCnt;
        hddCapacity = hddCap;
        integratedControllerCount = integratedCnt;
        peripheralDeviceCount = peripheralCnt;
        strncpy(os, osType, MAX_OS);
        os[MAX_OS - 1] = '\0';
    }

    const char* getOwnerSurname() const { return ownerSurname; }
    int getCpuCount() const { return cpuCount; }
    const char* getCpuType() const { return cpuType; }
    int getMemorySize() const { return memorySize; }
    const char* getVideoControllerType() const { return videoControllerType; }
    int getVideoMemorySize() const { return videoMemorySize; }
    const char* getHddType() const { return hddType; }
    int getHddCount() const { return hddCount; }
    int getHddCapacity() const { return hddCapacity; }
    int getIntegratedControllerCount() const { return integratedControllerCount; }
    int getPeripheralDeviceCount() const { return peripheralDeviceCount; }
    const char* getOs() const { return os; }

    void print() const {
        std::cout << "Owner: " << ownerSurname << std::endl
                  << "CPU Count: " << cpuCount << std::endl
                  << "CPU Type: " << cpuType << std::endl
                  << "Memory Size: " << memorySize << " GB" << std::endl
                  << "Video Controller Type: " << videoControllerType << std::endl
                  << "Video Memory Size: " << videoMemorySize << " GB" << std::endl
                  << "HDD Type: " << hddType << std::endl
                  << "HDD Count: " << hddCount << std::endl
                  << "HDD Capacity: " << hddCapacity << " GB" << std::endl
                  << "Integrated Controller Count: " << integratedControllerCount << std::endl
                  << "Peripheral Device Count: " << peripheralDeviceCount << std::endl
                  << "OS: " << os << std::endl;
    }
};

Computer* readComputers(const char* filename, int& count);
void printComputersNeedingUpgrade(Computer* computers, int count, int p);

#endif // COMPUTER_HPP
