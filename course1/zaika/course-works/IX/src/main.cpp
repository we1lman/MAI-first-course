#include "SortSearch.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

void inputArray(int arr[], int size) {
    std::cout << "Enter the elements of the array:\n";
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }
}

void generateRandomArray(int arr[], int size) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < size; ++i) {
        arr[i] = std::rand() % 100;
    }
}

int main() {
    int size, key, numKeys;

    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    int* arr = new int[size];
    SortSearch sortSearch;

    std::cout << "\nCase 1: The elements of the array are initially sorted\n";
    inputArray(arr, size);
    std::cout << "Original array: ";
    sortSearch.printArray(arr, size);
    sortSearch.mergeSort(arr, size);
    std::cout << "Sorted array: ";
    sortSearch.printArray(arr, size);

    std::cout << "\nCase 2: The elements of the array are in reverse order\n";
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
    std::cout << "Original array: ";
    sortSearch.printArray(arr, size);
    sortSearch.mergeSort(arr, size);
    std::cout << "Sorted array: ";
    sortSearch.printArray(arr, size);

    std::cout << "\nCase 3: The elements of the array are random\n";
    generateRandomArray(arr, size);
    std::cout << "Original array: ";
    sortSearch.printArray(arr, size);
    sortSearch.mergeSort(arr, size);
    std::cout << "Sorted array: ";
    sortSearch.printArray(arr, size);

    std::cout << "\nEnter the number of keys to search for: ";
    std::cin >> numKeys;

    for (int i = 0; i < numKeys; ++i) {
        std::cout << "Enter the key to search for: ";
        std::cin >> key;
        int result = sortSearch.binarySearch(arr, size, key);
        if (result != -1) {
            std::cout << "Key " << key << " found at position " << result << std::endl;
        } else {
            std::cout << "Key " << key << " not found" << std::endl;
        }
    }

    delete[] arr;
    return 0;
}
