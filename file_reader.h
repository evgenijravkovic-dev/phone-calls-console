#ifndef FILE_READER_H
#define FILE_READER_H

#include "book_subscription.h"

int readData(const char* filename, PhoneCall* calls);
void printCall(const PhoneCall& call);

#endif
