#ifndef FILE_READER_H
#define FILE_READER_H

#include "book_subscription.h"

int readData(const char* filename, BookSubscription* records);
void printRecord(const BookSubscription& record);

#endif
