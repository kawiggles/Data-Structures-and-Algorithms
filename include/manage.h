#ifndef MANAGE_H
#define MANAGE_H

#include "data.h"
#include <stdlib.h>

/*
Type Definitions
*/

// Defines the different data structures which can be created
typedef enum {
    LINKEDLIST,
    UNDEFINED
} DataStructureType;

typedef enum {
    BUILD,
    ADD,
    DESTROY,
    ALGO,
    PRINT,
    QUIT,
    INVALID
} Operation;

// Members of the linked list which defines the open data structures
typedef struct OpenStructure OpenStructure;
struct OpenStructure {
    // enum of the structure type
    DataStructureType structureType;
    // Pointer to the head of the data structure.
    void * dataStructure;
    // Numerical Id to easily identify the structure
    int structureId;
    // Pointer to the next structure
    OpenStructure * nextStructure;
};

/*
Functions
*/

// Returns an Operation enum from a string
Operation getOperation(char * operationInput);

// Returns a DataStructureType enum from a string
DataStructureType getStructureType(char * structureInput);

// Makes a new structure to add to the open structure linked list
OpenStructure * makeOpenStructure(int id); 

// Returns a pointer to a structure in the open structure linked list from its id
OpenStructure * getStructure(int id);

// Get's last structure in stucture linked list
OpenStructure * getLastStructure();

// Takes input from main() and runs functions
int parseInput(char * input);

// Frees memory for all open data structures
void endProgram(OpenStructure * head);

#endif