#ifndef RESTRICTED_H
#define RESTRICTED_H

#include "data.h"

typedef struct Stack Stack;
struct Stack {
    Data ** data;
    int top;
    int size;
};

Stack * makeStack(Data * input, int size);

int pushStack(Stack * stack, Data * data, int size);

typedef struct Queue Queue;

typedef struct Deque Deque;

#endif
