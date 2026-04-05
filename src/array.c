#include "array.h"

#include "stdlib.h"
#include "stdio.h"

Data * makeArray(Data * data, int size) {
    if (size <= 0) {
        printf("Error: array size can't be less than 1");
        return NULL;
    }
    Data *array = malloc(sizeof(Data) * size);
    array[0] = *data;
    return array;
}

int addToArray(Data * array, Data * data, int index, int size) {
    if (array == NULL) return 0;

    if (index >= size) return 0;

    array[index] = *data;
    return 1;
}

int deleteFromArray(Data * array, int index, int size) {
    if (array == NULL) return 0;

    if (index >= size) return 0;

    array[index].number = 0;
    return 1;
}

int destroyArray(Data * array) {
    free(array);
    return 1;
}

void printArray(Data * data, int size) {
    printf("[");
    for (int i = 0; i < size - 1; i++) {
        printf("%d, ", data[i]);
    }
    printf("%d]\n", data[size - 1]);
}
