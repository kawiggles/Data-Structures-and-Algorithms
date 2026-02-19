#ifndef DATA_H
#define DATA_H

// Basic data input for program
struct Data {
    int number;
};

// Returns a pointer to a new data struct
struct Data * makeData(int inputNumber);

#endif