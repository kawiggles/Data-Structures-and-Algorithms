#include "data.h"
#include "linkedlist.h"
#include <stdlib.h>

ListNode * makeLinkedList(Data * input) {
    ListNode * head = malloc(sizeof(ListNode));

    head->data = input;
    head->next = NULL;

    return head;
}

int addNode(ListNode * priorNode, Data * input) {
    if (priorNode == NULL) return -1;

    ListNode * newNode = malloc(sizeof(ListNode));
    if (newNode == NULL) return -1;

    newNode->data = input;
    newNode->next = priorNode->next;
    priorNode->next = newNode;

    return 0;
}

void destroyLinkedList(ListNode * head) {
    ListNode * currentNode = head;
    ListNode * nextNode;
    
    while (currentNode != NULL) {
        nextNode = currentNode->next;
        free(currentNode->data);
        free(currentNode);
        currentNode = nextNode;
    }
}

ListNode * getLastNode(ListNode * head) {
    ListNode * currentNode = head;

    while (currentNode->next != NULL) currentNode = currentNode->next;

    return currentNode;
}