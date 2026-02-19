#include "data.h"
#include "linkedlist.h"
#include <stdlib.h>

struct ListNode * makeLinkedList(struct Data * input) {
    struct ListNode * head = malloc(sizeof(struct ListNode));

    head->data = input;
    head->next = NULL;

    return head;
}

void destroyLinkedList(struct ListNode * head) {
    struct ListNode * currentNode = head;
    struct ListNode * nextNode;
    
    while (currentNode != NULL) {
        nextNode = currentNode->next;
        free(currentNode->data);
        free(currentNode);
        currentNode = nextNode;
    }
}

int addNode(struct ListNode * priorNode, struct Data * input) {
    if (priorNode == NULL) return -1;

    struct ListNode * newNode = malloc(sizeof(struct ListNode));
    if (newNode == NULL) return -1;

    newNode->data = input;
    newNode->next = priorNode->next;
    priorNode->next = newNode;

    return 0;
}