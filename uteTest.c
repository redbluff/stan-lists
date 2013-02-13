/*
 * uteTest.c
 *
 * Main driver to test that utility functions are OK
 *
 */

#include <stdio.h>
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
    printf("Ended uteTest.c\n");
    return 0;
}


