#ifndef ARRAY_H
#define ARRAY_H

#include "data.h"

Data * makeArray(Data *data, int size);

int addToArray(Data *array, Data *data, int index, int size);

int deleteFromArray(Data *array, int index, int size);

int destroyArray(Data *array);

void printArray(Data *array);

#endif
