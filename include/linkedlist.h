#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "data.h"

/* 
Type Definitions
*/

// Holds a data struct and a pointer to another LinkedListNode struct
typedef struct LinkedListNode LinkedListNode;
struct LinkedListNode {
    Data * data;
    LinkedListNode * next;
};

/*
Functions
*/

// Takes a pointer to a data struct and returns a pointer to a new head for a linked list
LinkedListNode * makeLinkedList(Data * input);

// Starting from head input, frees memory for every node and its data
void destroyLinkedList(LinkedListNode * head);

// Adds a new node with "input" data after "priorNode"
int addLLNode(LinkedListNode * node, Data * input, int index);

// Deletes a node in a linked list
int deleteLLNode(LinkedListNode ** node, int index);

// Iterates through a linked list to return last node of structure
LinkedListNode * getLLLastNode (LinkedListNode * head);

// Prints a linked list
void printLinkedList(LinkedListNode * head);
#endif
