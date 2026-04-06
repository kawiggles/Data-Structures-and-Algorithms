#include "algo.h"
#include "array.h"
#include "manage.h"

#include <stdio.h>

void sort(OpenStruct * structure) {
    switch (structure->structureType) {
        case ARRAY:
            mergeSortArray(structure->dataStruct, 0, structure->size - 1);
            printf("Array at index %u sorted using mergeSort \n", structure->structureId);
            break;
        default:
            printf("Error unknown data structure passed to sort \n");
    }
}

void mergeSort(OpenStruct * structure) {
    switch(structure->structureType) {
        case ARRAY:
            mergeSortArray(structure->dataStruct, 0, structure->size - 1);
            printf("Array at index %u sorted using mergeSort \n", structure->structureId);
            break;
        default:
            printf("Error: unknown data struct passed to mergeSort\n");
    }

}

void insertSort(OpenStruct * structure) {

}
