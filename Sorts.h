#ifndef SORTS_H
#define SORTS_H

#include "Message.h"

inline bool compareByType(const Message& a, const Message& b) {
    return a.type < b.type;
}

inline bool compareById(const Message& a, const Message& b) {
    return a.id < b.id;
}

inline bool compareCombined(const Message& a, const Message& b) {
    if (a.type != b.type) {
        return a.type < b.type;
    }
    return a.id < b.id;
}

void quickSort(Message arr[], int low, int high, bool (*compare)(const Message&, const Message&)) {
    if (low < high) {
        Message pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (compare(arr[j], pivot)) {
                i++;
                Message temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        Message temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int pi = i + 1;

        quickSort(arr, low, pi - 1, compare);
        quickSort(arr, pi + 1, high, compare);
    }
}

void countingSortByType(Message arr[], int n, int maxType = 10) {
    Message* output = new Message[n];
    int* count = new int[maxType + 1];

    for (int i = 0; i <= maxType; i++) count[i] = 0;
    for (int i = 0; i < n; i++) count[arr[i].type]++;
    for (int i = 1; i <= maxType; i++) count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i].type] - 1] = arr[i];
        count[arr[i].type]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    delete[] output;
    delete[] count;
}

void countingSortForRadix(Message arr[], int n, int exp) {
    Message* output = new Message[n];
    int count[10] = { 0 };

    for (int i = 0; i < n; i++) {
        count[(arr[i].id / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i].id / exp) % 10] - 1] = arr[i];
        count[(arr[i].id / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    delete[] output;
}

void radixSortById(Message arr[], int n) {
    int maxId = arr[0].id;
    for (int i = 1; i < n; i++) {
        if (arr[i].id > maxId) maxId = arr[i].id;
    }

    for (int exp = 1; maxId / exp > 0; exp *= 10) {
        countingSortForRadix(arr, n, exp);
    }
}

void combinedNonComparisonSort(Message arr[], int n, int maxType = 10) {
    radixSortById(arr, n);         
    countingSortByType(arr, n, maxType); 
}

#endif