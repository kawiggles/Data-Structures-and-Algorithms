#include "assert.h"
#include "array.h"

#include "stdlib.h"
#include "stdio.h"

Data * makeArray(Data * data, int size) {
    ASSERT(size > 0);

    Data *array = malloc(sizeof(Data) * size);
    array[0] = *data;
    return array;
}

int addToArray(Data * array, Data * data, int index, int size) {
    ASSERT(array);
    ASSERT(index <= size);

    int i;
    if (index == -1)
        i = size - 1;
    else
        i = index;

    array[i] = *data;
    return 1;
}

int deleteFromArray(Data * array, int index, int size) {
    ASSERT(array);
    ASSERT(index <= size);

    int i;
    if (index == -1)
        i = size - 1;
    else
        i = index;

    array[i].number = 0;
    return 1;
}

int destroyArray(Data * array) {
    free(array);
    return 1;
}

void printArray(Data * data, int size) {
    printf("[");
    for (int i = 0; i < size - 1; i++)
        printf("%d, ", data[i].number);

    printf("%d]\n", data[size - 1].number);
}

void mergeArray(Data * A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    Data L[n1 + 1];
    Data R[n2 + 1];
    
    for (int i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (int i = 0; i < n2; i++)
        R[i] = A[q + i + 1];
    
    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i].number <= R[j].number)
            A[k++] = L[i++];
        else
            A[k++] = R[j++];
    }
    while (i < n1)
        A[k++] = L[i++];
    while (j < n2)
        A[k++] = R[j++];
}

void mergeSortArray(Data * A, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSortArray(A, p, q);
        mergeSortArray(A, q + 1, r);
        mergeArray(A, p, q, r);
    }
}
