#ifndef ST_STRUCT
#define ST_STRUCT

typedef struct SerialTimeNode {
    int serial;
    int time;
    struct SerialTimeNode *next;
} SerialTimeNode;
#endif

/*
 *  Implement Linked list of open jobs. Data structure to be used only to record
    what jobs are open. Use Linked list of custom nodes, because edits will be
    frequent and list should usually be short enough that sorting is longer than
    traversing. Assume that lower timestamps are most likely to be searched, and
    insert before next lowest timestamp.
 *  Another issue of convenience. Rather than scanning below every job opening
    for the corresponding closing, as Excel might, this system throws away old
    rows, and keeps only the necessary information: a pairing of open jobs and
    times they opened.
 */

#include <stdlib.h>
#include <limits.h>

#ifndef OPENJOBS_H
#define OPENJOBS_H

// Define Null Node.
SerialTimeNode* NullSTN;

SerialTimeNode *head, *last;

void JobListInit(SerialTimeNode* NullNode)
{
    NullNode->time = INT_MAX;
    NullNode->serial = 0;
    NullNode->next = NullNode;
    
    head = NullSTN;
}

/*
 *  Insert given node into list, in place sorted by timestamp.
 *  Designed to allow passing literals. Function allocates more memory and
    copies literal into it.
 */
void insertSTN(SerialTimeNode insert_val);

/*
 *  Perform linear search for listing with given serial, then remove from list,
    and return node containing listing. Does not free memory.
 *  For internal use.
 */
SerialTimeNode* removeSTN(int remov_serial);

/*
 *  Use this function externally.
 *  Find job by serial number. Removes node, frees memory, returns timestamp.
 */
int close_job(int serial);

/*
 *  Use this function externally. Inserts job in list. Allocates memory and inserts.
 */
void open_job(int time, int serial);

#endif