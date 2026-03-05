#include "data.h"
#include "linkedlist.h"

#include <stdlib.h>
#include <stdio.h>

LinkedListNode * makeLinkedList(Data * input) {
    LinkedListNode * head = malloc(sizeof(LinkedListNode));

    head->data = input;
    head->next = NULL;

    return head;
}

int addLLNode(LinkedListNode * priorNode, Data * input) {
    if (priorNode == NULL) return -1;

    LinkedListNode * newNode = malloc(sizeof(LinkedListNode));
    if (newNode == NULL) return -1;

    newNode->data = input;
    newNode->next = priorNode->next;
    priorNode->next = newNode;

    return 0;
}

void destroyLinkedList(LinkedListNode * head) {
    LinkedListNode * currentNode = head;
    LinkedListNode * nextNode;
    
    while (currentNode != NULL) {
        nextNode = currentNode->next;
        free(currentNode->data);
        free(currentNode);
        currentNode = nextNode;
    }
}

LinkedListNode * getLLLastNode(LinkedListNode * head) {
    LinkedListNode * currentNode = head;

    while (currentNode->next != NULL) currentNode = currentNode->next;

    return currentNode;
}

void printLinkedList(LinkedListNode * head) {
    LinkedListNode * currentNode = head;

    while (currentNode->next != NULL) {
        printData(currentNode->data);
        printf(" -> ");
        currentNode = currentNode->next;
    }

    printData(currentNode->data);
    printf("\n");
}

