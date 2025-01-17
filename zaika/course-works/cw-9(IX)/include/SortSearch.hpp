#ifndef SORTSEARCH_HPP
#define SORTSEARCH_HPP

class SortSearch {
public:
    void mergeSort(int arr[], int size);
    int binarySearch(int arr[], int size, int key);
    void printArray(int arr[], int size);

private:
    void merge(int arr[], int left, int mid, int right);
    void mergeSortHelper(int arr[], int left, int right);
};

#endif // SORTSEARCH_HPP
