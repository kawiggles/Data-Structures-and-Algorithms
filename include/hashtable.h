#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "data.h"
#include "stdint.h"
#include "stdlib.h"

typedef struct {
    const char * key;
    Data * data;
} htEntry;

typedef struct {
    htEntry * entries;
    size_t capacity;
    size_t length;
} hashTable;

hashTable * makeHashTable(Data * data);

int addToHashTable(hashTable * ht, Data * data);

int deleteFromHashTable(hashTable * ht, Data * data);

int destroyHashTable(hashTable * ht);

void printHashTable(hashTable * ht);

#endif
