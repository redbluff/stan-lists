/*
 * lists.c
 *
 * Code file for the lists practice for the Stanford list exercises
 * Plan is to start off with the basics and then integrate each exercise 
 * as it is completed and tested.
 *
 * Each exercise will have its own C file with the main program that will
 * run the various tests to make sure it works OK.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lists.h"


/* Initial basic functions */

/*
 * length
 * returns the length of the list. i.e the number of nodes
 */
int length(struct node* head) {
    int numNodes = 0;
    struct node* current = head;

    while(current != NULL) {
        numNodes++;
        current = current->next;
    }
    return numNodes;
}


/*
 * push
 * pushes a node before the ref of newData.
 *
 * If failure occurs the ref will be set to NULL
 */
void push(struct node** headRef, int newData) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        *headRef = NULL;
        return;
    }

    //Node alloc was good, set it up and insert
    newNode->data = newData;
    newNode->next = *headRef;
    *headRef = newNode;
}


/*
 * BuildOneTwoThree
 * Builds a list {1,2,3} returning the address of the head.
 *
 * Returns NULL on failure.
 */
struct node* BuildOneTwoThree() {
    struct node* head = NULL;
    for (int i = 3; i > 0; i--) {
        push(&head, i);
        assert(head != NULL);
    }
    return head;
}


/*
 * print
 * prints space seperated list. 
 *
 * Prints empty list message if list is empty
 */
void print(struct node* head) {
    struct node* current = head;

    if (length(current)) {
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
    } else {
        printf("List is empty!");
    }
    printf("\n");
}



/*
 * Problem 1 - Count
 * Simply counts the number of times that seartchFor is in the list
 */
int Count(struct node* head, int searchFor) {
    int itemCount = 0;
    struct node* current = head;

    while (current != NULL) {
        if (searchFor == current->data) {
            itemCount++;
        }
        current = current->next;
    }
    return itemCount;
}

