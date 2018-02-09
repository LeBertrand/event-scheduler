//
// Created by Shmuel Jacobs on 1/28/2018.
//
#ifndef EVENT_T
#define EVENT_T

typedef enum {
    JOB_ARRIVE_CPU, JOB_FINISH_CPU, JOB_ARRIVE_D1, JOB_FINISH_D1, JOB_ARRIVE_D2, JOB_FINISH_D2, JOB_NULL
} EventCode ;

typedef struct {
    int serial;
    EventCode jobtype;
    int timestamp;
} Event;

/*
Event getNullEvent(){
    return (Event) {-1; JOB_NULL; QUIT_TIME*2};
} */

#endif // EVENT_T
