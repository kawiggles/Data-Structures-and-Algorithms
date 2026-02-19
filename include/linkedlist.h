#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "data.h"

// Holds a data struct and a pointer to another ListNode struct
struct ListNode {
    struct Data * data;
    struct ListNode * next;
};

// Takes a pointer to a data struct and returns a pointer to a new head for a linked list
struct ListNode * makeLinkedList(struct Data * input);

// Starting from head input, frees memory for every node and its data
void destroyLinkedList(struct ListNode * head);

// Adds a new node with "input" data after "priorNode"
int addNode(struct ListNode * priorNode, struct Data * input);

#endif