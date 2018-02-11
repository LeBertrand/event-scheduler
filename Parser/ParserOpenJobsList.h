#include <stdlib.h>
#include <limits.h>

typedef struct SerialTimeNode {
    int time;
    int serial;
    SerialTimeNode* next;
} SerialTimeNode;

// Define Null Node.
SerialTimeNode* NullSTN;


SerialTimeNode* head;

void JobListInit()
{
    NullSTN->time = INT_MAX;
    NullSTN->serial = 0;
    NullSTN->next = NullSTN;
    
    head = NullSTN;
}

/*
 *  Insert given node into list, in place sorted by timestamp.
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