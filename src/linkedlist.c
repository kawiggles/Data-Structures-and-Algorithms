#include "assert.h"
#include "data.h"
#include "linkedlist.h"

#include <stdlib.h>
#include <stdio.h>

LinkedListNode * makeLinkedList(Data * input) {
    ASSERT(input);
    LinkedListNode * head = malloc(sizeof(LinkedListNode));

    head->data = input;
    head->next = NULL;

    return head;
}

int addToLinkedList(LinkedListNode * node, Data * input, int index) {
    ASSERT(node);
    LinkedListNode * priorNode = node;

    if (index == -1) {
        priorNode = getLastLinkedListNode(node);
    } else {
        for (int i = 0; i < index; i++) {
            if (priorNode->next) {
                priorNode = priorNode->next;
            } else {
                printf("Error: no node at index %i \n", index);
                return 0;
            }
        }
    }

    LinkedListNode * newNode = malloc(sizeof(LinkedListNode));
    ASSERT(newNode);

    newNode->data = input;
    newNode->next = priorNode->next;
    priorNode->next = newNode;

    return 1;
}

int deleteFromLinkedList(LinkedListNode **node, int index) {
    ASSERT(*node);

    if (!(*node)->next) {
        printf("Error: only one node in structure, use 'destroy' to remove this structure \n");
        return 0;
    }

    if (index == -1) {
        LinkedListNode * prior = *node;
        while (prior->next->next)
            prior = prior->next;
        free(prior->next->data);
        free(prior->next);
        prior->next = NULL;
        return 1;
    } else {
        LinkedListNode ** pointer = node;

        for (int i = 0; i < index && *pointer; i++)
            pointer = &(*pointer)->next;

        if (*pointer == NULL) {
            printf("Error: node to destroy not found at index %i \n", index);
            return 0;
        }

        LinkedListNode * target = *pointer;
        *pointer = target->next;
        free(target->data);
        free(target);
        return 1;
    }
}

void destroyLinkedList(LinkedListNode * head) {
    ASSERT(head);
    LinkedListNode * currentNode = head;
    LinkedListNode * nextNode;
    
    while (currentNode) {
        nextNode = currentNode->next;
        free(currentNode->data);
        free(currentNode);
        currentNode = nextNode;
    }
}

LinkedListNode * getLastLinkedListNode(LinkedListNode * head) {
    ASSERT(head);
    LinkedListNode * currentNode = head;

    while (currentNode->next)
        currentNode = currentNode->next;

    return currentNode;
}

void printLinkedList(LinkedListNode * head) {
    ASSERT(head);
    LinkedListNode * currentNode = head;

    while (currentNode->next) {
        printData(currentNode->data);
        printf(" -> ");
        currentNode = currentNode->next;
    }

    printData(currentNode->data);
    printf("\n");
}

DoubleListNode * makeDoubleList(Data * input) {
    ASSERT(input);
    DoubleListNode * head = malloc(sizeof(DoubleListNode));

    head->data = input;
    head->next = NULL;
    head->prev = NULL;

    return head;
}

void destroyDoubleList(DoubleListNode * head) {
    ASSERT(head);
    DoubleListNode * currentNode = head;
    DoubleListNode * nextNode = head->next;
    
    while (currentNode) {
        nextNode = currentNode->next;
        free(currentNode->data);
        free(currentNode);
        currentNode = nextNode;
    }
}

int addToDoubleList(DoubleListNode * node, Data * input, int index) {
    ASSERT(node);
    DoubleListNode * priorNode = node;

    if (index == -1) {
        priorNode = getLastDoubleListNode(node);
    } else {
        for (int i = 0; i < index; i++) {
            if (priorNode->next) {
                priorNode = priorNode->next;
            } else {
                printf("Error: no node at index %i \n", index);
                return 0;
            }
        }
    }

    DoubleListNode * newNode = malloc(sizeof(DoubleListNode));
    ASSERT(newNode);

    newNode->data = input;
    if (priorNode->next) {
        newNode->next = priorNode->next;
        priorNode->next->prev = newNode;
    } else {
        newNode->next = NULL;
    }
    newNode->prev = priorNode;
    priorNode->next = newNode;

    return 1;
}

DoubleListNode * getLastDoubleListNode(DoubleListNode * head) {
    ASSERT(head);
    DoubleListNode * currentNode = head;

    while (currentNode->next)
        currentNode = currentNode->next;

    return currentNode;
}

int deleteFromDoubleList(DoubleListNode * node, int index) {
    ASSERT(node);
    DoubleListNode * priorNode = node;
    
    if (!node->next) {
        printf("Error: only one node in structure, use 'destroy' to remove this structure \n");
        return 0;
    }

    if (index == -1) {
        priorNode = getLastDoubleListNode(node);
        priorNode->prev->next = NULL;
        free(priorNode->data);
        free(priorNode);
        return 1;
    } else {
        for (int i = 0; i < index; i++) {
            if (priorNode->next) {
                priorNode = priorNode->next;
            } else {
                printf("Error: no node at index %i \n", index);
                return 0;
            }
        }
    }

    ASSERT(priorNode);

    priorNode->prev->next = priorNode->next;
    priorNode->next->prev = priorNode->prev;
    free(priorNode->data);
    free(priorNode);
    return 1;
}

void printDoubleList(DoubleListNode * head) {
    ASSERT(head);
    DoubleListNode * current = head;

    while (current->next) {
        printData(current->data);
        printf(" <-> ");
        current = current->next;
    }

    printData(current->data);
    printf("\n");
}
