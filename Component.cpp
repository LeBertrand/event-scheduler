#include "Component.h"
#include "LinkedListQueue.cpp"

Component::Component()
{
    // Make empty queue.
    LinkedListQueue qu;
    // No wait time before beginning job.
    current_wait = 0;
}

Component::~Component()
{
    // Free up queue space.
    delete &qu;
}

Component& Component::operator=(const Component& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void Component::pushJob(int serial)
{
    // Insert job in queue by pushing its serial number.
    qu.push(serial);
    // Processor is now busy.
    idle = false;
}

int Component::nextJob()
{
    if(qu.Getlength()==0){
        // Queue is empty. Return 'null job'.
        return 0;
    }
    return qu.pop();
    /*
    Understand this function: Job isn't gone. It's now in process in this
    Component. Event Scheduler is responsible to record its completion by
    immediately putting its completion in event heap and setting wait time in
    this component. Job exists as a completion in event queue, and as time on
    the clock in this Component.
     */
}

inline void Component::Setidle(bool state)
{
    idle = state;
}

void Component::increaseTime(int ticks)
{
    current_wait += ticks;
}

void Component::advanceTime(int ticks)
{
    current_wait -= ticks;
}