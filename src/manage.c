#include "manage.h"
#include "linkedlist.h"
#include "data.h"

#include <string.h>
#include <stdio.h>

static OpenStructure * openStructureListHead = NULL; 
static int nextId = 0;

Operation getOperation(char * operationInput) {
    if (operationInput[0] == 'a') {
        if (operationInput[1] == 'd') { return ADD; 
        } else return ALGO;
    } else if (operationInput[0] == 'b') {return BUILD;
    } else if (operationInput[0] == 'd') {return DESTROY;
    } else if (operationInput[0] == 'p') {return PRINT;
    } else if (operationInput[0] == 'q') {return QUIT;
    } else return INVALID;
}

DataStructureType getStructureType(char * structureInput) {
    if (structureInput[0] == 'l') { return LINKEDLIST; 
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
            case LINKEDLIST: destroyLinkedList(currentStructure->dataStructure); break;
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
    int id = 0;

    while (token != NULL) {
        if (token[0] == '-') {
            char flag = token[1];
            char * flagValue = strtok(NULL, " \n");

            if (!flagValue) {
                printf("Error: no value after flag %c \n", flag);
                return -1;
            }

            if (flag == 't') {
                type = getStructureType(flagValue);
            } else if (flag == 'd') {
                data = makeData(atoi(flagValue));
            } else if (flag == 'i') {
                id = atoi(flagValue);
            } else {
                printf("Error: flag %c not recognized \n", flag);
                return 0;
            }
        }

        token = strtok(NULL, " \n");
    }

    switch (getOperation(operation)) {
        case BUILD: {
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
                case LINKEDLIST:
                    workingStructure->structureType = LINKEDLIST;
                    workingStructure->dataStructure = makeLinkedList(data);
                    printf("Linked list successfully built with id %u \n", nextId);
                    break;
                case UNDEFINED:
                    printf("Error: cannot build undefined data structure \n");
                    break;
                default: 
                    printf("DEBUG ERROR: no data structure type encountered during build operation \n");
                    return -1;
            }

            nextId ++;
            break;
        }
        case ADD: {
            OpenStructure * workingStructure = getStructure(id); 

            if (workingStructure == NULL) return 0;
            
            switch (workingStructure->structureType) {
                case LINKEDLIST:
                    addLLNode(getLLLastNode(workingStructure->dataStructure), data);
                    printf("Node successfully added to end of linked list with id %u \n", id);
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
                case LINKEDLIST:
                    destroyLinkedList(workingStructure->dataStructure);
                    free(workingStructure);
                    printf("Linked list at id %u successfully destroyed \n", id);
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
        case QUIT:
            endProgram(openStructureListHead);
            return 1;
        case INVALID:
            printf("Error: command not recognized");
            break;
        default:
            printf("DEBUG ERROR: problem with getOperation");
    }


    return 0;

}
