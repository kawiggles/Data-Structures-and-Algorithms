#ifndef DATA_H
#define DATA_H

/*
Type Definitons
*/

// Basic data input for program
typedef struct {
    int number;
} Data;

/*
Functions
*/

// Returns a pointer to a new data struct
Data * makeData(int inputNumber);

#endif