#include "LinkedListQueue.h"

/*
 *  Programmer  -   Shmuel Jacobs
 *  Date - February 6
 *  Operating Systems and Sytems Programming
 
 
 *  Component class models a computer component in a system managed by a
 *  scheduler. Class relies on scheduler, to avoid redundant bookkeeping.
 *  Class can't do its own bookkeeping.
 */

#ifndef COMPONENT_H
#define COMPONENT_H


class Component
{
    public:
        /** Default constructor */
        Component();
        /** Default destructor */
        ~Component();
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        Component& operator=(const Component& other);

        /**
         * \return The current value of idle
         */
        bool Getidle() { return idle; }

        /**
         * \return The number of jobs currently in queue.
         */
        int Getjobs_waiting() { return qu.Getlength(); }

        /*
         *  Add job to wait queue. Only use if not idle. If idle, don't handle
            job at all. Scheduler should immediately put its completion in the
            heap and increase the wait time.
         */
        void pushJob(int serial);
        
        /*
         *  Move head job out of queue and begin working.
         */
        int nextJob();
        
        /*
         *  Allow scheduler to schedule new job. Scheduler generates random
         *  number of ticks for job length, and sends it back to this method.
         */
        void increaseTime(int ticks);
        /*
         *  Acknowledge time. Decrease wait_time by number of ticks input.
         */
        void advanceTime(int ticks);
        
        // Mark component idle. For call by scheduler.
        inline void Setidle(bool);
        
        inline int getTime() { return current_wait; }
        
    protected:

    private:
        // Integer Queue storing serial numbers of waiting jobs
        LinkedListQueue qu;
        // Flag indicating whether component is in use.
        bool idle;
        
        // Number of jobs in queue is supplied by queue's method get_length.
        
        // Number of ticks until finishing current job and queued jobs.
        unsigned int current_wait;
};

#endif // COMPONENT_H
