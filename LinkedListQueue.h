#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*
 *  Node structure for linked list.
 *  Consists of pointer to next entry and data point.
 *  Not safe for general use - doesn't check if empty before popping.
 */
typedef struct Node {
    Node* next;
    int data;
} Node;

class LinkedListQueue
{
    public:
        LinkedListQueue();
        LinkedListQueue(char*);
        ~LinkedListQueue();
        //LinkedList(const LinkedList& other);

        void push(int);
        int pop(void);
        inline int peek(void);

        // Return the number of entries in queue.
        inline unsigned int Getlength() { return length; }

    protected:

    private:
        unsigned int length;
        Node* head;
        Node* last;
        char* name;
};

#endif // LINKEDLIST_H
