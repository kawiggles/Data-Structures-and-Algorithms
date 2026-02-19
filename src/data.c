#include "data.h"
#include <stdlib.h>

struct Data * makeData(int inputNumber) {
    struct Data * newData = malloc(sizeof(struct Data));

    newData->number = inputNumber;

    return newData;
}