#include "Component.cpp"
#include "EventQueue.h"
#include "EventQueue.cpp"
#include "Event.c"
#include "config.h"
#include <time.h>

void place_event_new(Component*);

int global_time;
int serial_stamp;

int main()
{
    // Create Event queue.
    EventQueue event_queue;
    
    // Create Components.
    Component cpu;
    Component disk_one;
    Component disk_two;
    
    // Set clock to zero.
    global_time = 0;
    
    // Seed random numbers.
    srand(time(NULL));
    
    // Create stamp to give events their serial numbers. Start is arbitrary.
    serial_stamp = 1000;
    
}

/*
 *  Function creates new event and places in event queue.
 *  Takes pointer to cpu to allow insertion into queue.
 */
void place_new_event(Component* cpu)
{
    Event* ev = (Event*) malloc(sizeof(Event));
    // Give event next serial number available.
    ev->serial = serial_stamp++;
    // Record event as occuring
    ev->timestamp = global_time +
        (rand() % (ARRIVAL_MAX - ARRIVAL_MIN) + ARRIVAL_MIN);
    // Record job as a CPU arrival.
    ev->jobtype = JOB_ARRIVE_CPU;
    
}