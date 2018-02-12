#include "EventQueue.cpp"
#include <stdio.h>

FILE* Log;
int serial_stamp = 1000;

int log_event(Event* ev)
{
    return fprintf(Log, "%d,%d,%d\n",
        ev->timestamp, ev->jobtype, ev->serial);
}

int main(){
    
    Log = fopen("EQueu-tests.csv", "w");
    
    Event *ev1, *ev2, *ev3, *ev4, *ev5, *retrieved;
    EventQueue eq;
    
    ev1 = (Event*) malloc(sizeof(Event));
    ev1->timestamp=100;
    ev1->serial=serial_stamp++;
    ev1->jobtype=JOB_ARRIVE_CPU;
    
    ev2 = (Event*) malloc(sizeof(Event));
    ev2->timestamp=50;
    ev2->serial=serial_stamp++;
    ev2->jobtype=JOB_ARRIVE_CPU;
    
    ev3 = (Event*) malloc(sizeof(Event));
    ev3->timestamp=40;
    ev3->serial=serial_stamp++;
    ev3->jobtype=JOB_ARRIVE_CPU;
    
    ev4 = (Event*) malloc(sizeof(Event));
    ev4->timestamp=30;
    ev4->serial=serial_stamp++;
    ev4->jobtype=JOB_ARRIVE_CPU;
    
    ev5 = (Event*) malloc(sizeof(Event));
    ev5->timestamp=500;
    ev5->serial=serial_stamp++;
    ev5->jobtype=JOB_ARRIVE_CPU;
    
    eq.insert(ev1);
    eq.insert(ev2);
    eq.insert(ev4);
    eq.insert(ev5);
    
    
    retrieved = eq.getNext();
    printf("Event retrieved. Time is %d, serial is %d, Jobtype is %d.\n\n",
        retrieved->timestamp, retrieved->serial, retrieved->jobtype);
    log_event(retrieved);
        
    eq.insert(ev3);
    retrieved = eq.getNext();
    printf("Event retrieved. Time is %d, serial is %d, Jobtype is %d.\n\n",
        retrieved->timestamp, retrieved->serial, retrieved->jobtype);
    log_event(retrieved);
    
    retrieved = eq.getNext();
    printf("Event retrieved. Time is %d, serial is %d, Jobtype is %d.\n\n",
        retrieved->timestamp, retrieved->serial, retrieved->jobtype);
    log_event(retrieved);
    
    fclose(Log);
    
    return 0;
}