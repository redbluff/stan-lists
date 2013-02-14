/*
 * uteTest.c
 *
 * Main driver to test that utility functions are OK
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lists.h"


/*
 * testEmptyList
 *
 * Just some basic tests for an emoty list
 */
void testEmptyList(void) {
    struct node* head = NULL;

    assert(length(head) == 0);

    printf("Should print the empty list message on next line\n");
    print(head);
    printf("Empty list tests finished.\n");
}


/*
 * testPush
 * Test that we can create a node with push
 * Will test multiple pushes with next test
 */
void testPush() {
    struct node* head = NULL;

    push(&head, 42);
    assert(head != NULL);
    assert(head->next == NULL);
    assert(head->data == 42);
    assert(length(head) == 1);
    DeleteList(&head);
}


/*
 * testBuildOneTwoThree
 */
void testBuildOneTwoThree(void) {
    struct node* head = BuildOneTwoThree();

    assert(head != NULL);
    assert(length(head) == 3);
    printf("BuildOneTwoThree list is: ");
    print(head);
    DeleteList(&head);
}


/*
 * testCount 
 * Tests the count item routine
 */
void testCount(void) {
    struct node* head = BuildOneTwoThree();
    assert(Count(head, 42) == 0);

    push(&head, 42);
    assert(Count(head, 42) == 1);
    push(&head, 2);
    assert(Count(head, 2) == 2);
    push(&head, 42);
    assert(Count(head, 42) == 2);
    push(&head, 42);
    assert(Count(head, 42) == 3);

    assert(!Count(NULL, 0));
    printf("Count function tested OK\n");
    DeleteList(&head);
}

   

/*
 * testGetNth
 * Basic tests for GetNth
 */
void testGetNth(void) {
    printf("Testing GetNth, should produce two error messages.\n");

    struct node* head = NULL;
    assert (!GetNth(head, 42));
    head = BuildOneTwoThree();
    assert(!GetNth(head, 42));

    assert(GetNth(head, 1) == 2);
    push(&head, 42);
    assert(GetNth(head, 3) == 3);
    assert(GetNth(head, 0) == 42);
    printf("End test GetNth.\n");
    DeleteList(&head);
}


/*
 * testDeleteList
 * Test various basic list deletions
 */
void testDeleteList(void) {
    printf("Start testDeleteList.\n");
    struct node* list = NULL;
    DeleteList(&list);
    assert(list == NULL);

    list = BuildOneTwoThree();
    DeleteList(&list);
    assert(list == NULL);
    printf("End testDeleteList.\n");
}

    
/*
 * testPop
 * Tests the POP functions, but not the NULL assert
 */
void testPop(void) {
    printf("Entering testPop.\n");
    struct node* list = BuildOneTwoThree();
    printf("List before pop... ");
    print(list);
    printf("Pop value is %d\n", Pop(&list)); 
    assert(length(list) == 2);
    printf("List now is (should be '2 3'): ");
    print(list);
    DeleteList(&list);
    printf("End testPop.\n");
}


/*
 * testInsertNth
 * Tests the various scenarios for InsertNth.
 */
void testInsertNth(void) {
    printf("Starting testInsertNth.\n");

    //No list
    struct node* list = NULL;
    printf("Next message should be a list length error...\n");
    InsertNth(&list, 23, 42);
    assert(list == NULL);

    //Build list and insert at head.
    list = BuildOneTwoThree();
    struct node* oldHead = list;
    InsertNth(&list, 0, 42);
    printf("List should be '42 1 2 3'... ");
    print(list);
    assert(length(list) == 4);
    assert(oldHead != list);

    //Insert at end
    oldHead = list;
    InsertNth(&list, 4, 666);
    printf("List should be '42 1 2 3 666'... ");
    print(list);
    assert(length(list) == 5);
    assert(oldHead == list);

    //Insert in middle
    InsertNth(&list, 2, 13);
    printf("List should be '42 1 13 2 3 666'... ");
    print(list);
    assert(length(list) == 6);
    assert(oldHead == list);


    //Now big index
    printf("Next message should be a list length error...\n");
    InsertNth(&list, 23, 42);
    assert(list == oldHead);
    assert(length(list) == 6);

    DeleteList(&list);
    printf("InsertNth test completed.\n");
}

    
/*
 * testSortedInsert
 * tests the SortedInsert function
 */
void testSortedInsert(void) {
    printf("Test SortedInsert started.\n");

    //Empty list
    struct node* list = NULL;
    struct node* node = (struct node*)malloc(sizeof(struct node));
    assert(node != NULL);
    node->data = 1;
    SortedInsert(&list, node);
    assert(length(list) == 1);
    printf("List should be '1'...");
    print(list);

    //Insert at head of list
    DeleteList(&list);
    list = BuildOneTwoThree();
    node = (struct node*)malloc(sizeof(struct node));
    assert(node != NULL);
    node->data = 1;
    SortedInsert(&list, node);
    assert(list == node);
    assert(length(list) == 4);
    printf("List should be '1 1 2 3'...");
    print(list);

    //Insert at middle of list
    node = (struct node*)malloc(sizeof(struct node));
    assert(node != NULL);
    node->data = 2;
    SortedInsert(&list, node);
    assert(length(list) == 5);
    printf("List should be '1 1 2 2 3'...");
    print(list);

    //Insert at end of list
    node = (struct node*)malloc(sizeof(struct node));
    assert(node != NULL);
    node->data = 42;
    SortedInsert(&list, node);
    assert(length(list) == 6);
    printf("List should be '1 1 2 2 3 42'...");
    print(list);

    DeleteList(&list);
    printf("SortedInsert tests ended.\n");
}


/*
 * testInsertSort
 * Test no list, one item, many, plus already sorted
 */
void testInsertSort(void) {
    printf("Starting testInsertSort.\n");

    struct node* list = NULL;
    InsertSort(&list);
    assert(!list);
    printf("Sorted empty list ok.\n");

    //Test Single Item List
    list = (struct node*)malloc(sizeof(struct node));
    list->data = 42;
    InsertSort(&list);
    assert(list->data = 42);
    printf("List should be '42'... ");
    print(list);

    //Test Multiple already sorted list
    DeleteList(&list);
    list = BuildOneTwoThree();
    InsertSort(&list);
    assert(list);
    printf("List should be '1 2 3'... ");
    print(list);
    DeleteList(&list);

    //Sort list, generate random 10 item list
    for(int i = 0; i < 10; i++) {
        push(&list, rand()%100);
    }
    printf("original list is: ");
    print(list);
    InsertSort(&list);
    assert(length(list) == 10);
    assert(list);
    printf("Check that the 10 items are in ascending order: ");
    print(list);
    DeleteList(&list);

    printf("InsertSort testing complete.\n");
}

   
/*
 * testAppend
 */
void testAppend(void) {
    printf("Starting testAppend.\n");

    //First both lists empty
    struct node* aList = NULL;
    struct node* bList = NULL;
    Append(&aList, &bList);
    assert(!aList);
    assert(!bList);
    printf("Both lists empty OK.\n");

    //Test B list Empty
    aList = BuildOneTwoThree();
    Append(&aList, &bList);
    assert(!bList);
    printf("If B empty OK list should be '1 2 3': ");
    print(aList);

    //Test list A Empty
    Append(&bList, &aList);
    assert(!aList);
    printf("If A empty OK list should be '1 2 3': ");
    print(bList);

    //Join 2 lists
    push(&aList, 4);
    push(&aList, 5);
    push(&aList, 6);
    assert(length(aList) == 3);
    Append(&aList, &bList);
    assert(!bList);
    assert(length(aList) == 6);
    printf("append OK if list is '6 5 4 1 2 3': ");
    print(aList);
    DeleteList(&aList);

    printf("Append testing finished.\n");
}

    

/*
 * main
 * main program - duh
 */
int main(int argc, char** argv) {
    printf("Starting uteTest.c\n");

    testEmptyList();
    testPush();
    testBuildOneTwoThree();

    testCount();
    testGetNth();
    testDeleteList();
    testPop();
    testInsertNth();
    testSortedInsert();
    testInsertSort();
    testAppend();
    printf("Ended uteTest.c\n");
    return 0;
}


