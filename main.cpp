#include <iostream>
#include <cstring>
#include "book_subscription.h"
#include "file_reader.h"
#include "constants.h"

int compareDurationDesc(const void* a, const void* b) {
    PhoneCall* x = (PhoneCall*)a;
    PhoneCall* y = (PhoneCall*)b;
    
    int h1, m1, s1, h2, m2, s2;
    sscanf(x->duration, "%d:%d:%d", &h1, &m1, &s1);
    sscanf(y->duration, "%d:%d:%d", &h2, &m2, &s2);
    
    int sec1 = h1 * 3600 + m1 * 60 + s1;
    int sec2 = h2 * 3600 + m2 * 60 + s2;
    
    return sec2 - sec1;
}

int compareNumberAndCost(const void* a, const void* b) {
    PhoneCall* x = (PhoneCall*)a;
    PhoneCall* y = (PhoneCall*)b;
    
    int cmp = strcmp(x->number, y->number);
    if (cmp != 0) return cmp;
    
    if (x->costPerMinute > y->costPerMinute) return -1;
    if (x->costPerMinute < y->costPerMinute) return 1;
    return 0;
}

void heapify(PhoneCall* arr, int n, int i, int (*compare)(const void*, const void*)) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && compare(&arr[left], &arr[largest]) > 0) largest = left;
    if (right < n && compare(&arr[right], &arr[largest]) > 0) largest = right;
    
    if (largest != i) {
        PhoneCall temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest, compare);
    }
}

void heapSort(PhoneCall* arr, int n, int (*compare)(const void*, const void*)) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, compare);
    }
    for (int i = n - 1; i > 0; i--) {
        PhoneCall temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0, compare);
    }
}

void quickSort(PhoneCall* arr, int low, int high, int (*compare)(const void*, const void*)) {
    if (low >= high) return;
    
    PhoneCall pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (compare(&arr[j], &pivot) < 0) {
            i++;
            PhoneCall temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    PhoneCall temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    int pi = i + 1;
    quickSort(arr, low, pi - 1, compare);
    quickSort(arr, pi + 1, high, compare);
}

bool isMobile(const char* tariff) {
    return strcmp(tariff, "мобильный") == 0;
}

bool isNovember2021(const char* date) {
    int day, month, year;
    sscanf(date, "%d.%d.%d", &day, &month, &year);
    return (month == 11 && year == 21);
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    std::cout << "Laboratory work #8" << std::endl;
    std::cout << "Phone calls" << std::endl;
    std::cout << "Author: Evgenij Ravkovic" << std::endl << std::endl;
    
    PhoneCall calls[MAX_FILE_ROWS_COUNT];
    int count = readData("data.txt", calls);
    
    if (count == 0) {
        std::cout << "No data" << std::endl;
        return 1;
    }
    
    int choice;
    do {
        std::cout << "\n===== MENU =====" << std::endl;
        std::cout << "1. Show all calls" << std::endl;
        std::cout << "2. Filter: mobile calls" << std::endl;
        std::cout << "3. Filter: November 2021" << std::endl;
        std::cout << "4. Heap sort (duration desc)" << std::endl;
        std::cout << "5. Quick sort (number asc, cost desc)" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;
        
        PhoneCall filtered[MAX_FILE_ROWS_COUNT];
        int filteredCount = 0;
        
        switch(choice) {
            case 1:
                for (int i = 0; i < count; i++) {
                    printCall(calls[i]);
                }
                break;
                
            case 2:
                filteredCount = 0;
                for (int i = 0; i < count; i++) {
                    if (isMobile(calls[i].tariff)) {
                        filtered[filteredCount++] = calls[i];
                    }
                }
                for (int i = 0; i < filteredCount; i++) {
                    printCall(filtered[i]);
                }
                break;
                
            case 3:
                filteredCount = 0;
                for (int i = 0; i < count; i++) {
                    if (isNovember2021(calls[i].date)) {
                        filtered[filteredCount++] = calls[i];
                    }
                }
                for (int i = 0; i < filteredCount; i++) {
                    printCall(filtered[i]);
                }
                break;
                
            case 4:
                heapSort(calls, count, compareDurationDesc);
                for (int i = 0; i < count; i++) {
                    printCall(calls[i]);
                }
                break;
                
            case 5:
                quickSort(calls, 0, count - 1, compareNumberAndCost);
                for (int i = 0; i < count; i++) {
                    printCall(calls[i]);
                }
                break;
        }
    } while (choice != 0);
    
    return 0;
}
 
