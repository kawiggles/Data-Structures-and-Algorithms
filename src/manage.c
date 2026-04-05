#include "assert.h"
#include "data.h"
#include "array.h"
#include "linkedlist.h"
#include "manage.h"
#include "hashtable.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static OpenStruct * openStructListHead = NULL; 
static int nextId = 0;

Operation getOperation(char * operationInput) {
    if (operationInput[0] == 'a') {
        if (operationInput[1] == 'd') { return ADD; 
        } else return ALGO;
    } else if (operationInput[0] == 'b') {return BUILD;
    } else if (operationInput[0] == 'd') {
        if (operationInput[2] == 's') { return DESTROY;
        } else return DELETE;
    } else if (operationInput[0] == 'p') {
        if (operationInput[5] == '\0') { return PRINT; 
        } else return PRINTALL;
    } else if (operationInput[0] == 'q') {return QUIT;
    } else return INVALID;
}

StructType getStructType(char * structureInput) {
    if (structureInput[0] == 'l') { return LINKEDLIST; 
    } else if (structureInput[0] == 'a') { return ARRAY;
    } else if (structureInput[0] == 'h') { return HASHTABLE;
    } else return UNDEFINED;
}

OpenStruct * makeOpenStruct(int id) {
    OpenStruct * newStruct = malloc(sizeof(OpenStruct));
    newStruct->structureId = id;
    newStruct->nextStruct = NULL;
    newStruct->dataStruct = NULL;
    newStruct->structureType = UNDEFINED;

    return newStruct; 
}

OpenStruct * getStruct(int id) {
    OpenStruct * currentStruct = openStructListHead;

    while (currentStruct != NULL) {
        if (currentStruct->structureId == id) return currentStruct;
        currentStruct = currentStruct->nextStruct;
    }

    printf("Error: structure id not found \n");
    return NULL;
}

OpenStruct * getLastStruct() {
    OpenStruct * currentStruct = openStructListHead;

    while (currentStruct != NULL) {
        if(currentStruct->nextStruct == NULL) return currentStruct; 
        currentStruct = currentStruct->nextStruct;
    }

    printf("Error: no list of structures found \n");
    return NULL;
}

void endProgram(OpenStruct * head) {
    OpenStruct * currentStruct = head;
    OpenStruct * nextStruct;

    while (currentStruct != NULL) {
        nextStruct = currentStruct->nextStruct;

        switch (currentStruct->structureType) {
            case ARRAY: destroyArray(currentStruct->dataStruct); break;
            case LINKEDLIST: destroyLinkedList(currentStruct->dataStruct); break;
            case HASHTABLE: destroyHashTable(currentStruct->dataStruct); break;
            case UNDEFINED:  printf("Error: Undefined data structured encountered \n"); break;
            default: printf("DEBUG ERROR: problem with endProgram() \n");
        }

        free(currentStruct);
        currentStruct = nextStruct;
    }
}

int parseInput(char * input) {
    char * operation = strtok(input, " \n");
    
    if (operation == NULL) return 0;
    
    char * token = strtok(NULL, " \n");
    StructType type = UNDEFINED;
    Data * data = NULL;
    int size = 0;
    int id = 0;
    int index = -1;

    while (token != NULL) {
        if (token[0] == '-') {
            char flag = token[1];
            char * flagValue = strtok(NULL, " \n");

            if (!flagValue) {
                printf("Error: no value after flag -%c \n", flag);
                return 0;
            }

            if (flag == 't') {
                type = getStructType(flagValue);
            } else if (flag == 'd') {
                data = makeData(atoi(flagValue));
            } else if (flag == 'i') {
                id = atoi(flagValue);
            } else if (flag == 'n') {
                index = atoi(flagValue);
            } else if (flag == 's') {
                size = atoi(flagValue);
            } else {
                printf("Error: flag %c not recognized \n", flag);
                return 0;
            }
        }

        token = strtok(NULL, " \n");
    }

    switch (getOperation(operation)) {
        case BUILD: {
            if (!data) {
                printf("Error: no data to add to new structure \n");
                return 0;
            }

            OpenStruct * workingStruct;

            if (openStructListHead == NULL) {
                openStructListHead = makeOpenStruct(nextId);
                workingStruct = openStructListHead;
            } else {
                workingStruct = getLastStruct();
                workingStruct->nextStruct = makeOpenStruct(nextId);
                workingStruct = workingStruct->nextStruct;
            }

            switch (type) {
                case ARRAY:
                    workingStruct->structureType = ARRAY;
                    workingStruct->dataStruct = makeArray(data, size);
                    workingStruct->size = size;
                    printf("Array successfully built with id %u and size %d\n", nextId, size);
                    nextId++;
                    break;
                case LINKEDLIST:
                    workingStruct->structureType = LINKEDLIST;
                    workingStruct->dataStruct = makeLinkedList(data);
                    printf("Linked list successfully built with id %u \n", nextId);
                    nextId++;
                    break;
                case HASHTABLE:
                    workingStruct->structureType = HASHTABLE;
                    workingStruct->dataStruct = makeHashTable(data);
                    printf("Hash table successfully built with id %u \n", nextId);
                    nextId++;
                case UNDEFINED:
                    printf("Error: cannot build undefined data structure \n");
                    break;
                default: 
                    printf("DEBUG ERROR: no data structure type encountered during build operation \n");
                    return -1;
            }
            break;
        }
        case ADD: {
            if (!data) {
                printf("Error: no data to add to selected structure\n");
                return 0;
            }
            
            OpenStruct * workingStruct = getStruct(id); 

            if (workingStruct == NULL) {
                printf("Error: no data structure at selected index\n");
                return 0;
            }
            
            switch (workingStruct->structureType) {
                case ARRAY:
                    addToArray(workingStruct->dataStruct, data, index, workingStruct->size);
                    printf("Element successfully added to array at id %u\n", id);
                    break;
                case LINKEDLIST:
                    addToLinkedList(workingStruct->dataStruct, data, index);
                    printf("Node successfully added to linked list at id %u \n", id);
                    break; 
                case HASHTABLE:
                    addToHashTable(workingStruct->dataStruct, data);
                    printf("Element successfully added to hash table at id %u \n", id);
                    break;
                case UNDEFINED:
                    printf("Error: selected structure is an undefined type \n");
                    break;
                default:
                    printf("DEBUG ERROR: empty structure \n");
                    return -1;
            }

            break;
        }
        case DELETE: {
            OpenStruct * workingStruct = getStruct(id);

            if (workingStruct == NULL) return 0;

            switch (workingStruct->structureType) {
                case ARRAY:
                    deleteFromArray(workingStruct->dataStruct, index, workingStruct->size);
                    break;
                case LINKEDLIST: {
                    LinkedListNode ** head = (LinkedListNode **) &workingStruct->dataStruct;
                    deleteFromLinkedList(head, index);
                    break;
                }
                case HASHTABLE:
                    deleteFromHashTable(workingStruct->dataStruct, data);
                    break;
                case UNDEFINED:
                    printf("Error: selected structure is an undefined type \n");
                    break;
                default:
                    printf("DEBUG ERROR: empty structure \n");
                    return -1;
            }

            break;
        }
        case DESTROY: {
            OpenStruct ** workingPointer = &openStructListHead;

            while (*workingPointer != NULL && (*workingPointer)->structureId != id) {
                workingPointer = &(*workingPointer)->nextStruct;
            }

            if (*workingPointer == NULL) {
                printf("Error: structure id not found \n");
                break;
            }

            OpenStruct * workingStruct = *workingPointer;
            *workingPointer = workingStruct->nextStruct;

            switch (workingStruct->structureType) {
                case ARRAY:
                    destroyArray(workingStruct->dataStruct);
                    free(workingStruct);
                    printf("Array at id %u successfully destroyed\n", id);
                    break;
                case LINKEDLIST:
                    destroyLinkedList(workingStruct->dataStruct);
                    free(workingStruct);
                    printf("Linked list at id %u successfully destroyed \n", id);
                    break;
                case HASHTABLE:
                    destroyHashTable(workingStruct->dataStruct);
                    free(workingStruct);
                    printf("Hash table at id %u successfully destroyed \n", id);
                    break;
                case UNDEFINED:
                    printf("Error: selected structure is undefined \n");
                    break;
                default:
                    printf("DEBUG ERROR: empty structure \n");
                    return -1;
            }

            break;
        }

        case ALGO:

            break;
        case PRINT: {
            OpenStruct * workingStruct = getStruct(id);
            
            if (workingStruct == NULL) return 0;

            switch (workingStruct->structureType) {
                case ARRAY:
                    printf("Printing Array at id %u... \n", id);
                    printArray(workingStruct->dataStruct, workingStruct->size);
                    break;
                case LINKEDLIST:
                    printf("Printing Linked List at id %u... \n", id);
                    printLinkedList(workingStruct->dataStruct);
                    break;
                case UNDEFINED:
                    printf("Error: selected structure is undefined \n");
                    break;
                default:
                    printf("DEBUG ERROR: emptry structure \n");
                    return -1;
            }

            break;
        }
        case PRINTALL: {
            OpenStruct * currentStruct = openStructListHead;
            if (!currentStruct) return 0;

            int listIndex = 1;

            while (currentStruct != NULL) {
                printf("ID %i: ", currentStruct->structureId);
                
                switch (currentStruct->structureType) {
                    case ARRAY:
                        printf("Array \n    ");
                        printArray(currentStruct->dataStruct, currentStruct->size);
                        break;
                    case LINKEDLIST:
                        printf("Linked List \n    ");
                        printLinkedList(currentStruct->dataStruct);
                        break;
                    case HASHTABLE:
                        printf("Hash Table \n    ");
                        printHashTable(currentStruct->dataStruct);
                        break;
                    case UNDEFINED:
                        printf("Undefined Struct Type \n");
                        break;
                }

            currentStruct = currentStruct->nextStruct;
            }

            break;
        }
        case QUIT:
            endProgram(openStructListHead);
            return 1;
        case INVALID:
            printf("Error: command not recognized");
            break;
        default:
            printf("DEBUG ERROR: problem with getOperation");
            return -1;
    }


    return 0;

}
