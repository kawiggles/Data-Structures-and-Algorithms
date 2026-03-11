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

int addLLNode(LinkedListNode * node, Data * input, int index) {
    if (node == NULL) return -1;
    
    LinkedListNode * priorNode = node;
    if (index == -1) {
        priorNode = getLLLastNode(node);
    } else {
        for (int i = 0; i < index; i++) {
            if (priorNode->next != NULL) { 
                priorNode = priorNode->next;
            } else {
                printf("Error: no node at index %i \n", index);
                return 0;
            }
        }
    }

    LinkedListNode * newNode = malloc(sizeof(LinkedListNode));
    if (newNode == NULL) return -1;

    newNode->data = input;
    newNode->next = priorNode->next;
    priorNode->next = newNode;

    return 0;
}

int deleteLLNode(LinkedListNode **node, int index) {
    if (*node == NULL) return -1;
    
    if ((*node)->next == NULL) {
        printf("Error: only one node in structure, use 'destroy' to remove this structure \n");
        return 0;
    }

    if (index == -1) {
        LinkedListNode * prior = *node;
        while (prior->next->next != NULL) {
            prior = prior->next;
        }
        free(prior->next->data);
        free(prior->next);
        prior->next = NULL;
        return 0;
    } else {
        LinkedListNode ** pointer = node;

        for (int i = 0; i < index && *pointer != NULL; i++) {
            pointer = &(*pointer)->next;
        }

        if (*pointer == NULL) {
            printf("Error: node to destroy not found at index %i \n", index);
            return 0;
        }

        LinkedListNode * target = *pointer;
        *pointer = target->next;
        free(target->data);
        free(target);
        return 0;
    }
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

int getLLLength(LinkedListNode * head) {
    LinkedListNode * current;
    int length = 0;
    while (current->next) {
        length++;
        current = current->next;
    }
    return length;
}
