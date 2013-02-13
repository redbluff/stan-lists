/*
 * lists.h
 *
 * Header file for my practice on the Stanford linked list problems
 *
 * The plan is to start off with the basic functions and then gradually add
 * functions as they are tested.
 *
 */

// The basic node structure
// The data is a simple integer

struct node {
    int data;
    struct node* next;
};


// Function prototypes

int length(struct node* head); //Finds and returns the number of nodes
struct node* BuildOneTwoThree(); //Builds a list 1, 2, 3
void push(struct node** headRef, int newData); //Pushes a new node in at the ref
void print(struct node* head); // Prints space sperated list

//Problem 1 - Count
int Count(struct node* head, int searchFor);

//Problem 2 - GetNth
int GetNth(struct node* head, int index);

//Problem 3 - DeleteList
void DeleteList(struct node** headRef);
