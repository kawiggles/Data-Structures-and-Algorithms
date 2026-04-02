#include "manage.h"
#include "array.h"
#include "linkedlist.h"
#include "hashtable.h"
#include "data.h"

#include <string.h>
#include "stdlib.h"
#include <stdio.h>

static OpenStructure * openStructureListHead = NULL; 
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

DataStructureType getStructureType(char * structureInput) {
    if (structureInput[0] == 'l') { return LINKEDLIST; 
    } else if (structureInput[0] == 'a') { return ARRAY;
    } else if (structureInput[0] == 'h') { return HASHTABLE;
    } else return UNDEFINED;
}

OpenStructure * makeOpenStructure(int id) {
    OpenStructure * newStructure = malloc(sizeof(OpenStructure));
    newStructure->structureId = id;
    newStructure->nextStructure = NULL;
    newStructure->dataStructure = NULL;
    newStructure->structureType = UNDEFINED;

    return newStructure; 
}

OpenStructure * getStructure(int id) {
    OpenStructure * currentStructure = openStructureListHead;

    while (currentStructure != NULL) {
        if (currentStructure->structureId == id) return currentStructure;
        currentStructure = currentStructure->nextStructure;
    }

    printf("Error: structure id not found \n");
    return NULL;
}

OpenStructure * getLastStructure() {
    OpenStructure * currentStructure = openStructureListHead;

    while (currentStructure != NULL) {
        if(currentStructure->nextStructure == NULL) return currentStructure; 
        currentStructure = currentStructure->nextStructure;
    }

    printf("Error: no list of structures found \n");
    return NULL;
}

void endProgram(OpenStructure * head) {
    OpenStructure * currentStructure = head;
    OpenStructure * nextStructure;

    while (currentStructure != NULL) {
        nextStructure = currentStructure->nextStructure;

        switch (currentStructure->structureType) {
            case ARRAY: destroyArray(currentStructure->dataStructure); break;
            case LINKEDLIST: destroyLinkedList(currentStructure->dataStructure); break;
            case HASHTABLE: destroyHashTable(currentStructure->dataStructure); break;
            case UNDEFINED:  printf("Error: Undefined data structured encountered \n"); break;
            default: printf("DEBUG ERROR: problem with endProgram() \n");
        }

        free(currentStructure);
        currentStructure = nextStructure;
    }
}

int parseInput(char * input) {
    char * operation = strtok(input, " \n");
    
    if (operation == NULL) return 0;
    
    char * token = strtok(NULL, " \n");
    DataStructureType type = UNDEFINED;
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
                type = getStructureType(flagValue);
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

            OpenStructure * workingStructure;

            if (openStructureListHead == NULL) {
                openStructureListHead = makeOpenStructure(nextId);
                workingStructure = openStructureListHead;
            } else {
                workingStructure = getLastStructure();
                workingStructure->nextStructure = makeOpenStructure(nextId);
                workingStructure = workingStructure->nextStructure;
            }

            switch (type) {
                case ARRAY:
                    workingStructure->structureType = ARRAY;
                    workingStructure->dataStructure = makeArray(data, size);
                    workingStructure->size = size;
                    printf("Array successfully built with id %u\n", nextId);
                    nextId++;
                    break;
                case LINKEDLIST:
                    workingStructure->structureType = LINKEDLIST;
                    workingStructure->dataStructure = makeLinkedList(data);
                    printf("Linked list successfully built with id %u \n", nextId);
                    nextId++;
                    break;
                case HASHTABLE:
                    workingStructure->structureType = HASHTABLE;
                    workingStructure->dataStructure = makeHashTable(data);
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
            
            OpenStructure * workingStructure = getStructure(id); 

            if (workingStructure == NULL) {
                printf("Error: no data structure at selected index\n");
                return 0;
            }
            
            switch (workingStructure->structureType) {
                case ARRAY:
                    addToArray(workingStructure->dataStructure, data, index, workingStructure->size);
                    printf("Element successfully added to array at id %u\n", id);
                    break;
                case LINKEDLIST:
                    addToLinkedList(workingStructure->dataStructure, data, index);
                    printf("Node successfully added to linked list at id %u \n", id);
                    break; 
                case HASHTABLE:
                    addToHashTable(workingStructure->dataStructure, data);
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
            OpenStructure * workingStructure = getStructure(id);

            if (workingStructure == NULL) return 0;

            switch (workingStructure->structureType) {
                case ARRAY:
                    deleteFromArray(workingStructure->dataStructure, index, workingStructure->size);
                    break;
                case LINKEDLIST: {
                    LinkedListNode ** head = (LinkedListNode **) &workingStructure->dataStructure;
                    deleteFromLinkedList(head, index);
                    break;
                }
                case HASHTABLE:
                    deleteFromHashTable(workingStructure->dataStructure, data);
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
            OpenStructure ** workingPointer = &openStructureListHead;

            while (*workingPointer != NULL && (*workingPointer)->structureId != id) {
                workingPointer = &(*workingPointer)->nextStructure;
            }

            if (*workingPointer == NULL) {
                printf("Error: structure id not found \n");
                break;
            }

            OpenStructure * workingStructure = *workingPointer;
            *workingPointer = workingStructure->nextStructure;

            switch (workingStructure->structureType) {
                case ARRAY:
                    destroyArray(workingStructure->dataStructure);
                    free(workingStructure);
                    printf("Array at id %u successfully destroyed\n", id);
                    break;
                case LINKEDLIST:
                    destroyLinkedList(workingStructure->dataStructure);
                    free(workingStructure);
                    printf("Linked list at id %u successfully destroyed \n", id);
                    break;
                case HASHTABLE:
                    destroyHashTable(workingStructure->dataStructure);
                    free(workingStructure);
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
            OpenStructure * workingStructure = getStructure(id);
            
            if (workingStructure == NULL) return 0;

            switch (workingStructure->structureType) {
                case LINKEDLIST:
                    printf("Printing Linked List at id %i... \n", id);
                    printLinkedList(workingStructure->dataStructure);
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
            OpenStructure * currentStructure = openStructureListHead;
            if (!currentStructure) return 0;

            int listIndex = 1;

            while (currentStructure != NULL) {
                printf("ID %i: ", currentStructure->structureId);
                
                switch (currentStructure->structureType) {
                    case ARRAY:
                        printf("Array \n    ");
                        break;
                    case LINKEDLIST:
                        printf("Linked List \n    ");
                        printLinkedList(currentStructure->dataStructure);
                        break;
                    case UNDEFINED:
                        printf("Undefined Structure Type \n");
                        break;
                }

            currentStructure = currentStructure->nextStructure;
            }

            break;
        }
        case QUIT:
            endProgram(openStructureListHead);
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
