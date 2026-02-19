#include "manage.h"
#include "linkedlist.h"
#include "data.h"

#include <stdlib.h>

int initOpenDataStructures (DataStructureType type, Data * data) {

    switch (type) {
        case LinkedList: 
            makeLinkedList(data);
            break;
        default:
            break;
    }

}

void endProgram(openStructure * head) {

}