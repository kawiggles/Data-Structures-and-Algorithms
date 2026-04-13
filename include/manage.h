#ifndef MANAGE_H
#define MANAGE_H

/*
Type Definitions
*/

// Defines the different data structures which can be created
typedef enum {
    ARRAY,
    LINKEDLIST,
    DOUBLELIST,
    HASHTABLE,
    UNDEFINED
} StructType;

typedef enum {
    SORT,
    INSERTSORT,
    MERGESORT,
    NOTALGO
} AlgoType;

typedef enum {
    BUILD,
    ADD,
    DELETE,
    DESTROY,
    RESIZE,
    ALGO,
    PRINT,
    PRINTALL,
    QUIT,
    HELP,
    INVALID
} Operation;

// Members of the linked list which defines the open data structures
typedef struct OpenStruct OpenStruct;
struct OpenStruct {
    // enum of the structure type
    StructType structureType;
    // Pointer to the head of the data structure.
    void * dataStruct;
    // Numerical Id to easily identify the structure
    int structureId;
    // Pointer to the next structure
    OpenStruct * nextStruct;
    // Size of struct, necessary for arrays
    int size;
};

/*
Functions
*/

// Returns an Operation enum from a string
Operation getOperation(char * input);

// Returns a DataStructType enum from a string
StructType getStructType(char * input);

// Returns an AlgoType enum from a string
AlgoType getAlgoType(char * input);

// Makes a new structure to add to the open structure linked list
OpenStruct * makeOpenStruct(int id); 

// Returns a pointer to a structure in the open structure linked list from its id
OpenStruct * getStruct(int id);

// Get's last structure in stucture linked list
OpenStruct * getLastStruct();

// Takes input from main() and runs functions
int parseInput(char * input);

// Frees memory for all open data structures
void endProgram(OpenStruct * head);

#endif
