#include "data.h"

#include <stdlib.h>
#include <stdio.h>

Data * makeData(int inputNumber) {
    Data * newData = malloc(sizeof(Data));

    newData->number = inputNumber;

    return newData;
}

void printData(Data * data) {
    printf("[%i]", data->number);
}
