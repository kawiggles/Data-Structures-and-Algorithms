#ifndef MANAGE_H
#define MANAGE_H

#include "data.h"

/*
Type Definitions
*/

// Defines the different data structures which can be created
typedef enum {
    LinkedList
} DataStructureType;

// Members of the linked list which defines the open data structures
typedef struct {
    // Pointer to the head of the data structure.
    void * dataStructure;
    // Numerical Id to easily identify the structure
    int Id;
    // Pointer to the next structure
    struct openStructureListNode * next;
} openStructure;

/*
Functions
*/

/* Takes input from main() and runs functions */
void parseInput(char * input);

// Initalizes the list of data structures used by the program
int initOpenStructuresList(DataStructureType type, Data * data);

// Adds a new data structure member to a data structure
int addOpenStructuresList(DataStructureType type, Data * data);

// Frees memory for all open data structures
void endProgram(openStructure * head);

#endif