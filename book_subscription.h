#ifndef BOOK_SUBSCRIPTION_H
#define BOOK_SUBSCRIPTION_H

#include "constants.h"

struct PhoneCall {
    char number[20];
    char date[11];
    char time[9];
    char duration[9];
    char tariff[20];
    double costPerMinute;
};

#endif
