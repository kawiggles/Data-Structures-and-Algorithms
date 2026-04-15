#include "assert.h"
#include "restricted.h"

#include <stdlib.h>
#include <stdio.h>

Stack * makeStack(Data * input, int size) {
    ASSERT(size > 0);

    Stack * stack = malloc(sizeof(Stack));
    stack->size = size;
    
    if (input) {
        stack->data[0] = input;
        stack->top = 0;
    } else {
        stack->top = -1;
    }

    return stack;
}

int pushStack(Stack * stack, Data * data, int size) {
    ASSERT(stack);
   
}
