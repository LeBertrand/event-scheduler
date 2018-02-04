#include <cstdlib>
#include <cstdio>
#include "Event.c"
#include "EventQueue.h"
#include "EventQueue.cpp"

int main()
{
    EventQueue *qu = new EventQueue();
    Event* testEvents[5];
    Event* retrieved ;
    
    testEvents[0] = (Event*) malloc(sizeof(Event));
    testEvents[0]->serial = 1003;
    testEvents[0]->jobtype = JOB_ARRIVE_CPU;
    testEvents[0]->timestamp = 7;
    
    testEvents[1] = (Event*) malloc(sizeof(Event));
    testEvents[1]->serial = 1004;
    testEvents[1]->jobtype = JOB_CPU_D1;
    testEvents[1]->timestamp = 20;
    
    testEvents[2] = (Event*) malloc(sizeof(Event));
    testEvents[2]->serial = 1005;
    testEvents[2]->jobtype = JOB_D1_CPU;
    testEvents[2]->timestamp = 29;

    /* Add and remove  single event.
    qu->append(testEvents[1]);
    Event* retrieved = qu->getNext();
    printf("Retrieved event serial - %d, job code - %d, timestamp - %d\n\n",
        retrieved->serial,retrieved->jobtype,retrieved->timestamp); */
    
    /* Add 2, 1, 3 to queue then retrieve all. */
    qu->append(testEvents[1]);
    qu->append(testEvents[0]);
    qu->append(testEvents[2]);
    
    retrieved = qu->getNext();
    printf("Retrieved event serial - %d, job code - %d, timestamp - %d\n\n",
        retrieved->serial,retrieved->jobtype,retrieved->timestamp);
    retrieved = qu->getNext();
    printf("Retrieved event serial - %d, job code - %d, timestamp - %d\n\n",
        retrieved->serial,retrieved->jobtype,retrieved->timestamp);
    retrieved = qu->getNext();
    printf("Retrieved event serial - %d, job code - %d, timestamp - %d\n\n",
        retrieved->serial,retrieved->jobtype,retrieved->timestamp);
    
    return EXIT_SUCCESS;
}
