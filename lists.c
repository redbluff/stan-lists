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


/*
 * GetNth - Get the Nth item and return its data.
 *          If the list is empty or the index is too large, print and return 0.
 *          This is less than optimal, but I don't want to stop the run on
 *          testing.
 *
 *          C indexing is used for node access.
 */
int GetNth(struct node* head, int index) {
    int len = length(head);
    if (!len || len <= index) {
        printf("Index is invalid, length of list %d, index %d\n",len, index);
        return 0;
    }
    struct node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}


/*
 * DeleteList
 * Walks the list and deletes all nodes, setting head to NULL
 * Assumes that nodes are allocated by MALLOC and FREE always works
 */
void DeleteList(struct node** headRef) {
    struct node* current = *headRef;
    while(current != NULL) {
        *headRef = current->next;
        free(current);
        current = *headRef;
    }
}



/*
 * Pop
 * Pops the head of the list and returns the data
 *
 * Asserts on NULL list. Assumes nodes allocated by MALLOC and that FREE always
 * works.
 */
int Pop(struct node** headRef) {
    struct node* current = *headRef;

    //This should be better but is OK for our purposes
    assert(current != NULL);

    int retval = current->data;
    *headRef = current->next;
    free(current);
    return retval;
}


/*
 * InsertNth
 * Inserts the data at the Nth index of the updated list.
 *
 * If index is too large prints a message and returns without changing the list
 */
void InsertNth(struct node** headRef, int index, int data) {
    int len = length(*headRef);
    if (index > len) { 
        printf("Index is too large for list, list size %d, index %d.\n", len, index);
        return;
    }

    struct node* current = *headRef;

    //Two cases, if index is 0, simply push it. If not, then walk the list
    if (!index) {
        push(headRef, data);
    } else {
        struct node* prev;
        for (int i = 0; i < index; i++) {
            prev = current;
            current = current->next;
        }
        push(&current, data);
        prev->next = current;
    }
}


/*
 * SortedInsert
 * Inserts node into monotonically ascending list.
 *
 * Assumes list is sorted ascending and that dupes are allowed.
 */ 
void SortedInsert(struct node** headRef, struct node* newNode) {
    struct node* current = *headRef;
    struct node* prev = NULL;
    int data = newNode->data;

    //Walk the list until we find the insertion point, unless list is empty
    if (current) {
        while(current && current->data < data) {
            prev = current;
            current = current->next;
        }
    }

    //If it is at the start of the list we need to fix the head pointer
    if (!prev) {
        *headRef = newNode;
    } else {
        prev->next = newNode;
    }
    newNode->next = current;
}



/*
 * InsertSort
 * Sorts a list in place using pointer manipulation
 */
void InsertSort(struct node** headRef) {
    //If an empty list simply return
    if (!headRef) {
        return;
    }

    struct node* sortedList = NULL;
    struct node* current = *headRef;

    //Bump the head and then add the current to the new list
    while(current) {
        *headRef = current->next;
        current->next = NULL;
        SortedInsert(&sortedList, current);
        current = *headRef;
    }
    *headRef = sortedList;
}


/*
 * Append
 * Appends list B to List A, setting B to NULL on return
 */
void Append(struct node** aRef, struct node** bRef) {
    //Check if A is empty
    if (!(*aRef)) {
        *aRef = *bRef;
        *bRef = NULL;
        return;
    }

    //Check if B is NULL
    if (!(*bRef)) {
        return;
    }

    //Walk list A until end and then splice in list B
    struct node* current = *aRef;
    while(current->next) {
        current = current->next;
    }
    current->next = *bRef;
    *bRef = NULL;
}


/*
 * FrontBackSplit
 * Takes a source list and splits half way. If an odd node exists, it goes to
 * the front list. Note this invalidates the source list.
 */
void FrontBackSplit(struct node* source, struct node** frontRef, struct node** backRef) {
    *frontRef = *backRef = NULL;

    //If an empty list, nothing to do
    if (!source) {
        return;
    }

    //Init the two pointers, slow to node 0, fast to node 1
    struct node* slowPtr = source;
    struct node* fastPtr = source->next;

    //If the list is only one node, return now
    if (!fastPtr) {
        *frontRef = source;
        return;
    }

    //Walk the list, with the fast pointer jumping 2 nodes
    while(fastPtr->next) {
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next;
        if (fastPtr && fastPtr->next) {
            fastPtr = fastPtr->next;
        }
    }

    //Set the list pointers and split the lists
    *frontRef = source;
    *backRef = slowPtr->next;
    slowPtr->next = NULL;
}


/*
 * RemoveDuplicates
 * Removes duplicate data nodes from a monotonically ascending list.
 */
void RemoveDuplicates(struct node* head) {

    //If a zero or single node list, then return as nothing to do
    if (!(head && head->next)) {
        return;
    }

    struct node* current = head;
    struct node* delNode = NULL;

    //Walk the list, deleting dupes as we go
    while(current->next) {
        if (current->data == current->next->data) {
            delNode = current->next;
            current->next = delNode->next;
            free(delNode);
        } else {
            current = current->next;
        }
    }
}


/*
 * MoveNode
 * Moves the first node of src to dest
 */
void MoveNode(struct node** destRef, struct node** srcRef) {

    //If src is empty then just return
    if (!(*srcRef)) {
        return;
    }

    //Simply pop the first node off the src and add it to the dest
    struct node* moved = *srcRef;
    *srcRef = moved->next;
    moved->next = *destRef;
    *destRef = moved;
}




