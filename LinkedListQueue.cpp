#include "LinkedListQueue.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>

LinkedListQueue::LinkedListQueue()
{
    // Constructor - set up empty list
    head = NULL;
    // Shortcut to last node, to make pushing quicker.
    last = NULL;

    length = 0;

    name = (char*) malloc(14);
    strcpy(name, "Unnamed Queue");
}

LinkedListQueue::LinkedListQueue(char* msg)
{
    // Constructor - set up empty list
    head = NULL;
    last = NULL;

    length = 0;

    name = (char*) malloc(14);
    if(name == NULL){
        exit(3);
    }
    strcpy(name, msg);
}

LinkedListQueue::~LinkedListQueue()
{
    /* Iterate through list, freeing each node by popping it. */
    while(head != NULL){
        pop();
    }
}

void LinkedListQueue::push(int x){
    Node* insertion = (Node*) malloc(sizeof(Node));
    if(insertion == NULL){
        printf("Unable to allocate space for %s.\n", name);
    }
    insertion->data = x;
    insertion->next = NULL;
    if(head==NULL){
        head = insertion;
        last = insertion;
    } else {
        last->next = insertion;
        last = insertion;
    }
    length++;
}

int LinkedListQueue::pop()
{
    /*  Inelegant solution. Replace with exception. */
    if(head==NULL) return -1;
    // Create pointer for use later to free Node.
    Node* take = head;
    // Hang on to return value before freeing.
    int val = take->data;
    // Move head to next node.
    head = head->next;
    length--;
    // Free space from node that was head.
    free(take);
    return val;
}

inline int LinkedListQueue::peek()
{
    return head->data;
}