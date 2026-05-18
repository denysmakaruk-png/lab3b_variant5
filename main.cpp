#include <iostream>
#include <chrono>
#include "Message.h"
#include "Sorts.h"

void copyArray(Message src[], Message dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void printArray(Message arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "[ID: " << arr[i].id << " | Type: " << arr[i].type 
                  << " | Text: " << arr[i].text << "]\n";
    }
    std::cout << "---------------------------------------\n";
}

int main() {
    const int N = 6;
    Message originalData[N] = {
        {105, 2, "Hello", 1},
        {23,  1, "World", 2},
        {105, 1, "Test",  3},
        {12,  2, "Data",  4},
        {8,   0, "C++",   5},
        {44,  1, "Code",  6}
    };

    Message arr[N];

    std::cout << "=== ORIGINAL DATA ===\n";
    printArray(originalData, N);

    std::cout << "\n=== SORTING BY TYPE ===\n";
    
    copyArray(originalData, arr, N);
    auto start = std::chrono::high_resolution_clock::now();
    countingSortByType(arr, N);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Counting Sort (by Type) completed.\n";
    printArray(arr, N);

    copyArray(originalData, arr, N);
    quickSort(arr, 0, N - 1, compareByType);
    std::cout << "QuickSort (by Type) completed.\n";

    std::cout << "\n=== SORTING BY USER ID ===\n";

    copyArray(originalData, arr, N);
    radixSortById(arr, N);
    std::cout << "Radix Sort (by ID) completed.\n";
    printArray(arr, N);

    copyArray(originalData, arr, N);
    quickSort(arr, 0, N - 1, compareById);
    std::cout << "QuickSort (by ID) completed.\n";

    std::cout << "\n=== COMBINED SORTING (Type -> ID) ===\n";

    copyArray(originalData, arr, N);
    quickSort(arr, 0, N - 1, compareCombined);
    std::cout << "QuickSort (Combined: Type then ID):\n";
    printArray(arr, N);

    copyArray(originalData, arr, N);
    combinedNonComparisonSort(arr, N);
    std::cout << "Stable Linear Sorts (Combined: Radix ID then Counting Type):\n";
    printArray(arr, N);

    std::cout << "Execution completed successfully!\n";
    return 0;
}