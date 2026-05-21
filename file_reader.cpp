#include "file_reader.h"
#include <fstream>
#include <iostream>
#include <cstring>

int readData(const char* filename, BookSubscription* records) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return 0;
    }
    
    int count = 0;
    while (count < MAX_FILE_ROWS_COUNT && 
           file >> records[count].readerLastName 
                >> records[count].readerFirstName 
                >> records[count].readerMiddleName
                >> records[count].phoneNumber 
                >> records[count].callDate 
                >> records[count].callTime
                >> records[count].duration 
                >> records[count].city) {
        count++;
    }
    
    file.close();
    return count;
}

void printRecord(const BookSubscription& record) {
    std::cout << record.readerLastName << " "
              << record.readerFirstName << " "
              << record.readerMiddleName << " | "
              << record.phoneNumber << " | "
              << record.callDate << " | "
              << record.callTime << " | "
              << record.duration << " сек | "
              << record.city << std::endl;
}
