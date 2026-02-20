#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "data.h"

/* 
Type Definitions
*/

// Holds a data struct and a pointer to another ListNode struct
typedef struct ListNode ListNode;
struct ListNode {
    Data * data;
    ListNode * next;
};

/*
Functions
*/

// Takes a pointer to a data struct and returns a pointer to a new head for a linked list
ListNode * makeLinkedList(Data * input);

// Starting from head input, frees memory for every node and its data
void destroyLinkedList(ListNode * head);

// Adds a new node with "input" data after "priorNode"
int addNode(ListNode * priorNode, Data * input);

// Iterates through a linked list to return last node of structure
ListNode * getLastNode (ListNode * head);

#endif