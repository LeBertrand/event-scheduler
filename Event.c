//
// Created by Shmuel Jacobs on 1/28/2018.
//
#ifndef EVENT_T
#def EVENT_T

typedef enum {
    JOB_ARRIVE_CPU, JOB_CPU_D1, JOB_CPU_D2, JOB_D2_CPU, JOB_D1_CPU, JOB_NULL
} EventCode ;

typedef struct {
    int serial;
    EventCode jobtype;
    int timestamp;
} Event;

#endif // EVENT_T
