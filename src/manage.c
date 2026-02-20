#include "manage.h"
#include "linkedlist.h"
#include "data.h"

#include <stdlib.h>
#include <string.h>

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

void endProgram(OpenStructure * head) {
    OpenStructure * currentStructure = head;
    OpenStructure * nextStructure;

    while (currentStructure != NULL) {
        nextStructure = currentStructure->nextStructure;

        switch (currentStructure->structureType) {
            case LINKEDLIST: destroyLinkedList(currentStructure->dataStructure); break;
            case UNDEFINED:  printf("Error: Undefined data structured encountered"); break;
            default: printf("DEBUG ERROR: problem with endProgram()");
        }

        free(currentStructure);
        currentStructure = nextStructure;
    }
}

int parseInput(char * input) {
    char * token = strtok(input, " \n");
    if (token == NULL) return 0;

    if (strcmp(token, "buildstruct") == 0) {
        char * operation = strtok(NULL, " \n");
        token = strtok(NULL, " \n");

        DataStructureType type = UNDEFINED;
        Data * data = NULL;
        int id = 0;

        while (token != NULL) {
            if (token[0] == '-') {
                char flag = token[1];
                char * flagValue = strtok(NULL, " \n");

                if (!flagValue) {
                    printf("Error: no value after flag %c", flag);
                    return -1;
                }

                if (flag == 't') {
                    type = getStructureType(flagValue);
                } else if (flag == 'd') {
                    data = makeData(atoi(flagValue));
                } else if (flag == 'i') {
                    id = atoi(flagValue);
                } else {
                    printf("Error: flag %c not recognized", flag);
                    return -1;
                }
            }
            token = strtok(NULL, " \n");
        }

        OpenStructure * currentStructure = openStructureListHead;

        switch (getOperation(operation)) {
            case BUILD: {
                if (currentStructure == NULL) {
                    openStructureListHead = makeOpenStructure(nextId);
                } else {
                    while (currentStructure->nextStructure != NULL) {
                        currentStructure = currentStructure->nextStructure;
                    }
                    currentStructure->nextStructure = makeOpenStructure(nextId);
                    currentStructure = currentStructure->nextStructure;
                }

                if (type == LINKEDLIST) {
                    currentStructure->structureType = LINKEDLIST;
                    currentStructure->dataStructure = makeLinkedList(data);
                    printf("Linked List successfully built with id %u", nextId);
                } else if (type == UNDEFINED) {
                    printf("Error: cannot build undefined data structure");
                    return -1;
                } else {
                    printf("DEBUG ERROR: no data structure type encountered during build operation");
                    return -1;
                }
                nextId ++;
                break;
            }
            case ADD:
                while (currentStructure->structureId != id) {
                    currentStructure = currentStructure->nextStructure;

                    if (currentStructure == NULL) {
                        printf("Error: structure id not found");
                        return 0;
                    }
                }

                if (currentStructure->structureType == LINKEDLIST) {

                }
                break;
            case DESTROY:

                break;
            case ALGO:

                break;
            case PRINT:

                break;
            case QUIT:
                endProgram(openStructureListHead);
                return 1;
            case INVALID:
                printf("Error: command not recognized");
                break;
            default:
                printf("DEBUG ERROR: problem with getOperation");
        }

    }

    return 0;

}