#include "Component.cpp"
#include "EventQueue.h"
#include "EventQueue.cpp"
#include "Event.c"
#include "config.h"
#include <time.h>

void place_event_new(Component*);
void loop();
int find_next_up();

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
    
    loop();
    
    
    return 0;
}

/*
 *  Main loop. Four major steps in each pass:
 *      Generate new CPU arrival.
 *      Find next job and advance time keeping.
 *      Handle event.
 *      Check if simulation over.
 */
 void loop()
 {
     return;
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

/*
 *  Find next q
 */
int find_next_up()
{
    
}