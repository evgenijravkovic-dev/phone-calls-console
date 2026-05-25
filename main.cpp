#include <iostream>
#include <cstring>
#include "book_subscription.h"
#include "file_reader.h"
#include "constants.h"

int compareByDuration(const void* a, const void* b) {
    return ((BookSubscription*)a)->duration - ((BookSubscription*)b)->duration;
}

int compareByCity(const void* a, const void* b) {
    return strcmp(((BookSubscription*)a)->city, ((BookSubscription*)b)->city);
}

void bubbleSort(BookSubscription* arr, int n, int (*compare)(const void*, const void*)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(&arr[j], &arr[j + 1]) > 0) {
                BookSubscription temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void quickSort(BookSubscription* arr, int low, int high, int (*compare)(const void*, const void*)) {
    if (low >= high) return;
    
    BookSubscription pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (compare(&arr[j], &pivot) < 0) {
            i++;
            BookSubscription temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    BookSubscription temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    int pi = i + 1;
    quickSort(arr, low, pi - 1, compare);
    quickSort(arr, pi + 1, high, compare);
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    std::cout << "Лабораторная работа №8. Телефонные звонки" << std::endl;
    std::cout << "Автор: Евгений Равкович" << std::endl << std::endl;
    
    BookSubscription records[MAX_FILE_ROWS_COUNT];
    int count = readData("data.txt", records);
    
    if (count == 0) {
        std::cout << "Нет данных" << std::endl;
        return 1;
    }
    
    int choice;
    do {
        std::cout << "\n===== МЕНЮ =====" << std::endl;
        std::cout << "1. Вывод всех записей" << std::endl;
        std::cout << "2. Сортировка по длительности (пузырьком)" << std::endl;
        std::cout << "3. Сортировка по городу (быстрая)" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выбор: ";
        std::cin >> choice;
        
        switch(choice) {
            case 1:
                for (int i = 0; i < count; i++)
                    printRecord(records[i]);
                break;
            case 2:
                bubbleSort(records, count, compareByDuration);
                std::cout << "\nОтсортировано по длительности:" << std::endl;
                for (int i = 0; i < count; i++)
                    printRecord(records[i]);
                break;
            case 3:
                quickSort(records, 0, count - 1, compareByCity);
                std::cout << "\nОтсортировано по городу:" << std::endl;
                for (int i = 0; i < count; i++)
                    printRecord(records[i]);
                break;
        }
    } while (choice != 0);
    
    return 0;
}
