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
    char owner_surname[MAX_SURNAME];
    int cpu_count;
    char cpu_type[MAX_TYPE];
    int memory_size;
    char video_controller_type[MAX_CONTROLLER_TYPE];
    int video_memory_size;
    char hdd_type[MAX_TYPE];
    int hdd_count;
    int hdd_capacity;
    int integrated_controller_count;
    int peripheral_device_count;
    char os[MAX_OS];

public:
    Computer(const char* surname = "", int cpu = 0, const char* cpuType = "", int memory = 0, const char* videoType = "",
             int videoMemory = 0, const char* hddType = "", int hddCnt = 0, int hddCap = 0,
             int integratedCnt = 0, int peripheralCnt = 0, const char* osType = "")
    {
        strncpy(owner_surname, surname, MAX_SURNAME);
        owner_surname[MAX_SURNAME - 1] = '\0';
        cpu_count = cpu;
        strncpy(cpu_type, cpuType, MAX_TYPE);
        cpu_type[MAX_TYPE - 1] = '\0';
        memory_size = memory;
        strncpy(video_controller_type, videoType, MAX_CONTROLLER_TYPE);
        video_controller_type[MAX_CONTROLLER_TYPE - 1] = '\0';
        video_memory_size = videoMemory;
        strncpy(hdd_type, hddType, MAX_TYPE);
        hdd_type[MAX_TYPE - 1] = '\0';
        hdd_count = hddCnt;
        hdd_capacity = hddCap;
        integrated_controller_count = integratedCnt;
        peripheral_device_count = peripheralCnt;
        strncpy(os, osType, MAX_OS);
        os[MAX_OS - 1] = '\0';
    }

    const char* getOwnerSurname() const { return owner_surname; }
    int getCpuCount() const { return cpu_count; }
    const char* getCpuType() const { return cpu_type; }
    int getMemorySize() const { return memory_size; }
    const char* getVideoControllerType() const { return video_controller_type; }
    int getVideoMemorySize() const { return video_memory_size; }
    const char* getHddType() const { return hdd_type; }
    int getHddCount() const { return hdd_count; }
    int getHddCapacity() const { return hdd_capacity; }
    int getIntegratedControllerCount() const { return integrated_controller_count; }
    int getPeripheralDeviceCount() const { return peripheral_device_count; }
    const char* getOs() const { return os; }

    void print() const {
        std::cout << "Owner: " << owner_surname << std::endl
                  << "CPU Count: " << cpu_count << std::endl
                  << "CPU Type: " << cpu_type << std::endl
                  << "Memory Size: " << memory_size << " GB" << std::endl
                  << "Video Controller Type: " << video_controller_type << std::endl
                  << "Video Memory Size: " << video_memory_size << " GB" << std::endl
                  << "HDD Type: " << hdd_type << std::endl
                  << "HDD Count: " << hdd_count << std::endl
                  << "HDD Capacity: " << hdd_capacity << " GB" << std::endl
                  << "Integrated Controller Count: " << integrated_controller_count << std::endl
                  << "Peripheral Device Count: " << peripheral_device_count << std::endl
                  << "OS: " << os << std::endl;
    }
};

Computer* readComputers(const char* filename, int& count);

void printComputersNeedingUpgrade(Computer* computers, int count, int p);

#endif // COMPUTER_HPP
