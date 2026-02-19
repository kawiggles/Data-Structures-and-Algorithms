#include "data.h"
#include <stdlib.h>

Data * makeData(int inputNumber) {
    Data * newData = malloc(sizeof(Data));

    newData->number = inputNumber;

    return newData;
}