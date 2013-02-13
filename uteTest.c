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
    printf("Ended uteTest.c\n");
    return 0;
}


