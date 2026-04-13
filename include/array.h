#ifndef ARRAY_H
#define ARRAY_H

#include "data.h"

Data * makeArray(Data * data, int size);

int addToArray(Data * array, Data * data, int index, int size);

int deleteFromArray(Data * array, int index, int size);

int destroyArray(Data * array);

int resizeArray(Data * array, int size);

void printArray(Data * array, int size);

void mergeArra(Data * A, int p, int q, int r);
void mergeSortArray(Data * A, int p, int r);

#endif
