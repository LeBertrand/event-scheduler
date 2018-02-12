#include "ParserOpenJobsList.h"

void insertSTN(SerialTimeNode insert_val){
    SerialTimeNode* insertion = (SerialTimeNode*) malloc(sizeof(SerialTimeNode));
    insertion->time = insert_val.time;
    insertion->serial = insert_val.serial;
    insertion->next = insert_val.next;
    
    if(head == NullSTN){ // If list is empty, set insertion as new head.
        head = insertion;
    }
    else{
        // Otherwise, find last node before a higher timestamped node than insertion.
        SerialTimeNode *finder = head;
        
        // Logic of looking for node is complicated, so created a found flag.
        char found = 0;
        while(!found){
            SerialTimeNode* scout = (SerialTimeNode*) finder->next;
            if(scout->time > insertion->time){
                // Found another node with a lower time stamp. Keep going.
                finder = scout;
            } else {
                // Finder now points to last node before insertion.
                found = 1;
            }
        } // finder points to the last node before insertion's spot.
        insertion->next = finder->next;
        finder->next = (SerialTimeNode*) insertion;
    }
}


void open_job(int itime, int iserial)
{
    SerialTimeNode insertion;// = (SerialTimeNode*) malloc(sizeof(SerialTimeNode));
    insertion.time=itime;
    insertion.serial=iserial;
    insertSTN(insertion);
}
