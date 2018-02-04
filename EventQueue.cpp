#include "EventQueue.h"
#include <cstdlib>
#include "Event.c"

const int QUIT_TIME = 10000;
//Event NullEvent = (Event) {-1; JOB_NULL; QUIT_TIME*2}; replaced with get null event method in method.c
EventQueue::EventQueue()
{
    // Constructor - Set queue empty
    num_items = 0, length = 2;
    data = (Event**) malloc(2*sizeof(Event*));
    NullEventPtr = (Event*) malloc(sizeof(Event*));
// TODO (Shmuel Jacobs#1#): Create Destructor to clean up allocated space
    NullEventPtr->serial = -1;
    NullEventPtr->jobtype = JOB_NULL;
    NullEventPtr->timestamp = QUIT_TIME*2;
}

bool EventQueue::reSpace()
{
    // Allocate new space to store event queue.
    Event** temp = (Event**) malloc(2*length* sizeof(Event*));
    // Check for failed allocation
    if(temp==NULL){
        return false;
    }
    length *= 2;

    // Copy into new array.
    int i;
    for(i = 0; i < num_items; i++){
        temp[i] = data[i];
    }
    // Beyond new data, fill empty space with null events to allow sorting.
    for(;i < length; i++){
        temp[i] = NullEventPtr;
    }
    // Free old array
    free(data);

    // Set pointer to new array.
    data = temp;

    return true;
}

bool EventQueue::setEntry(Event* entry, int place)
{
    // Check for space. Allocate if necessary.
    if(length <= place){
        if(!reSpace()){
            // Failed to allocate more space.
            return false;
        }
    }
    // Reset selected entry.
    data[place] = entry;

    return true;
}

bool EventQueue::append(Event* entry)
{
    // Put entry after filled places in list, and record one more place filled.
    bool worked = setEntry(entry, num_items++);
    // Reheap
    heapUp();
    
    return worked;
}

Event* EventQueue::getNext()
{
    // Get pointer to next event.
    Event* head = data[0];
    // Remove next event from queue.
    setEntry(NullEventPtr,0);
    // Reheap.
    heapUp();

    return head;
}
void EventQueue::heapUp(){
    int i;
    for(i = num_items - 1; i > 0; i/=2){
        if(data[i]->timestamp < data[i/2]->timestamp){
            arraySwap(data, i, i/2);
        }
    }
}

void EventQueue::heapDown()
{
    // current holds location of spot to fill next
    int current = 0, left_child;

    // While current node has children, swap down the heap.
    while(left_child < num_items){ // Inside loop, there is always at least one child.
        left_child = 2*current + 1;
        // Case: right child exists and is greater than both left child and current. Swap right.
        if(left_child + 1 < num_items && data[left_child + 1]->timestamp > data[left_child]->timestamp
           && data[current]->timestamp > data[left_child + 1]->timestamp){
            arraySwap(data, current, left_child + 1);
            // Reset current to right child.
            current = left_child + 1;
        }
        // Case left child is greater, or no right child exists. Check if left is
        // greater than current, and if so swap left.
        else if(data[left_child]->timestamp > data[current]->timestamp){
            arraySwap(data, current, left_child);
            current = left_child;
        }
        // No children with greater values.
        else break;
    }
}

/*
// TODO (Shmuel Jacobs#1#): Finish
Event* EventQueue::getNext()
{
    Event* next_up = data[0];
    data[0];
} */

/*
 * Case specific swap pointers function. Get pointer from 'second', move pointer
 * from first to second, and set old 'second' to first.
 */
void inline arraySwap(Event** data, int first, int second)
{
    // Get the pointer stored in the second position.
	Event* temp = *(data + second);
	*(data + second) = *(data + first);
	*(data + first) = temp;
}

/*
 * Free all allocated space and tear down instance.
 */
 EventQueue::~EventQueue(){
    // Free space given to null event.
    free(NullEventPtr);
    // Free space used by all events in the queue.
    // Free all spots in the queue.
    delete[] data;
 }
