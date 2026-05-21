#include "processing.h"
#include <cstdio>

double calculateAverageCostPerSecond(const PhoneCall* calls, int size) {
    if (size <= 0 || calls == nullptr) {
        return 0.0;
    }
    
    double totalCost = 0.0;
    int totalSeconds = 0;
    
    for (int i = 0; i < size; i++) {
        int h, m, s;
        sscanf(calls[i].duration, "%d:%d:%d", &h, &m, &s);
        int seconds = h * 3600 + m * 60 + s;
        totalSeconds += seconds;
        totalCost += seconds * (calls[i].costPerMinute / 60.0);
    }
    
    if (totalSeconds == 0) return 0.0;
    return totalCost / totalSeconds;
}
