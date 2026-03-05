#ifndef DATA_H
#define DATA_H

/*
Type Definitons
*/

// Basic data input for program
typedef struct Data Data;
struct Data {
    int number;
};

/*
Functions
*/

// Returns a pointer to a new data struct
Data * makeData(int inputNumber);

// Prints contents of data struct, for use in print operations
void printData(Data * data);

#endif
