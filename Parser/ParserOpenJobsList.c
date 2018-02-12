#include "ParserOpenJobsList.h"


void insertSTN(SerialTimeNode insert_val){
    SerialTimeNode* insertion = (SerialTimeNode*) malloc(sizeof(SerialTimeNode));
    *insertion = (SerialTimeNode)
        {insert_val.time, insert_val.serial, insert_val.next};
    if(head == NullSTN){ // If list is empty, set insertion as new head.
        head = insertion;
    }
    else{
        // Otherwise, find last node before a higher timestamped node than insertion.
        SerialTimeNode* finder = head;
        while((head->next)->time < insertion->time){
            finder = finder->next;
        } // finder points to the last node before insertion's spot.
        insertion->next = finder->next;
        finder->next = insertion;
    }
}

SerialTimeNode* removeSTN(int remov_serial){
    SerialTimeNode *finder;
    if(head->serial==remov_serial){
        // Head will be return value, so hold its address.
        finder = head;
        // Set next node as head of list.
        head=head->next;
        
        return finder;
        
    } else {
        /* Iterate to find first node with greater or equal serial number,
        keeping pointer on the node before it. */
        finder = head; 
        while((finder->next)->serial < remov_serial){
            finder = finder->next;
        } 
        // Check if next node is the right job. If not, it's not here in this list at all.
        if((finder->next)->serial != remov_serial){
            return NullSTN;
        }
        // Finder now points to the last node before the one to remove.
        // Store this address for return.
        SerialTimeNode* retval = finder;
        /* Remove this node from the list, by linking the one before with the
        one after it. */
        finder->next = (finder->next)->next;
        
        return retval;
    }
}

void open_job(int itime, int iserial)
{
    SerialTimeNode* insertion = (SerialTimeNode*) malloc(sizeof(SerialTimeNode));
    insertion->time=itime;
    insertion->serial=iserial;
}

int close_job(int serial)
{
    SerialTimeNode* nd = removeSTN(serial);
    int timestamp = nd->time;
    if(timestamp != INT_MAX){
        free(nd);
    }
    return timestamp;
}