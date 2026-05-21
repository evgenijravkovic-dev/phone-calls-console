#include "file_reader.h"
#include <fstream>
#include <iostream>
#include <cstring>

int readData(const char* filename, PhoneCall* calls) {
    std::ifstream file(filename);
    if (!file.is_open()) return 0;
    
    int count = 0;
    while (count < MAX_FILE_ROWS_COUNT &&
           file >> calls[count].number
                >> calls[count].date
                >> calls[count].time
                >> calls[count].duration
                >> calls[count].tariff
                >> calls[count].costPerMinute) {
        count++;
    }
    return count;
}

void printCall(const PhoneCall& call) {
    std::cout << call.number << " | "
              << call.date << " | "
              << call.time << " | "
              << call.duration << " | "
              << call.tariff << " | "
              << call.costPerMinute << " руб/мин" << std::endl;
}
