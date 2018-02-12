#include "ParserOpenJobsList.h"

SerialTimeNode* removeSTN(int remov_serial){
    SerialTimeNode *finder, *scout;
    if(head->serial==remov_serial){
        // Head will be return value, so hold its address.
        finder = head;
        // Set next node as head of list.
        head=head->next;
        
        return finder;
        
    } else {
        /* Iterate to find first node with greater or equal serial number,
        keeping pointer on the node before it. Stop if null node reached. */
        finder = head; 
        scout = finder->next;
        while(scout->serial < remov_serial && scout->serial != 0){
            finder = finder->next;
            scout=scout->next;
        } 
        // Check if next node is the right job. If not, it's not here in this list at all.
        if(scout->serial != remov_serial){
            return NullSTN;
        }
        // Finder now points to the last node before the one to remove.
        // Store this address for return.
        SerialTimeNode* retval = finder;
        /* Remove this node from the list, by linking the one before with the
        one after it. */
        finder->next = scout->next;
        
        return retval;
    }
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