#include "ParserOpenJobsList.h"
#include "NodeStruct"


void insertSTN(SerialTimeNode insert_val){
    SerialTimeNode* insertion = (SerialTimeNode*) malloc(sizeof(SerialTimeNode));
    insertion->time = insert_val.time;
    insertion->serial = insert_val.serial;
    insertion->next = insert_val.next;
    
    if(head == NullSTN){ // If list is empty, set insertion as new head.
        head = insertion;
        head->next = NullSTN;
    } else if(insertion->time < head->time){
        // Insertion becomes new head.
        insertion->next = head;
        head = insertion;
    } else {
        // Otherwise, find last node before a higher timestamped node than insertion.
        SerialTimeNode *finder = head;
        SerialTimeNode* scout = finder->next;
        
        // Go to end of the line.
        while(finder->next != NullSTN && scout->time < insertion->time){
            finder = scout;
            scout = scout->next;
        } // finder points to the last node before insertion's spot.
        insertion->next = finder->next;
        finder->next = (SerialTimeNode*) insertion;
    }
}

SerialTimeNode* removeSTN(int remov_serial){
    SerialTimeNode *finder, *scout;
    if(head->serial==remov_serial){
        // Getting first item in list.
        
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
        while(scout->serial != remov_serial && scout->serial != 0){
            finder = scout;
            scout=scout->next;
        } 
        // Check if next node is the right job. If not, it's not here in this list at all.
        if(scout->serial != remov_serial){
            return NullSTN;
        } /* Finder now points to the last node before the one to remove.
            Scout points to the one sought. */
        
        /* Remove this node from the list, by linking the one before with the
        one after it. */
        finder->next = scout->next;
        
        return scout;
    }
}

void open_job(int itime, int iserial)
{
    SerialTimeNode insertion;// = (SerialTimeNode*) malloc(sizeof(SerialTimeNode));
    insertion.time=itime;
    insertion.serial=iserial;
    insertSTN(insertion);
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