/*
 * DES Proj. Event Queue file. Allow array to resize itself to allocate space for more event.
 * Store Event pointers in dynamic array.
 * Implement heap on array to sort events by time stamp.
 *
 * Implementation of Dynamic memory and heap of struct pointers is case specific, since this case doesn't need
 * complicated behavior like shrinking or shifting, and generalizeable code would be more complicated to use for an
 * array of structs.
 */
#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "Event.c"

void arraySwap(Event**, int, int);

class EventQueue
{
    public:
        /* Set up empty EventQueue. */
        EventQueue();

        /*
         * Insert item at end of array.
         * Contains book-keeping, so can be used externally.
         */
        bool append(Event* entry);

        /*
         *  Pop head event from event queue.
         *  Replace event with null and return event.
         */
        Event* getNext();

        // Free up queue and null object, and tear down instance.
        ~EventQueue();

    protected:

    private:

        // Store current number of items and current space allocated.
        int num_items, length;
        // Pointer to allocated space storing array
        Event** data;
        // Null Pointer used to backfill empty values in allocated array.
        Event* NullEventPtr;

        /* Allocate twice as much space for array. */
        bool reSpace();

        /* Insert item at index.
         * entry - Event pointer to put in array.
         * place - index to set in array.
         * Return - true if set was successful, otherwise false. */
        bool setEntry(Event*, int);

        /*
         * Sort list by ascending time stamps, with element out of
         * place in bottom row. Heap sort on array.
         */
        void heapUp();

        /*
         * Sort list by ascending time stamps, with element out of
         * place in front. Heap sort on array.
         */
        void heapDown();
};





#endif // EVENTQUEUE_H
