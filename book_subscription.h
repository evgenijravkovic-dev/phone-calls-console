#ifndef BOOK_SUBSCRIPTION_H
#define BOOK_SUBSCRIPTION_H

#include "constants.h"

struct BookSubscription {
    char readerLastName[50];
    char readerFirstName[50];
    char readerMiddleName[50];
    char phoneNumber[20];
    char callDate[11];
    char callTime[9];
    int duration;
    char city[50];
};

#endif
