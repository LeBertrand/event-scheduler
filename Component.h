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

        /** Access idle
         * \return The current value of idle
         */
        bool Getidle() { return idle; }
        /** Set idle
         * \param val New value to set
         */
        void Setidle(bool val) { idle = val; }
        /** Access jobs_waiting
         * \return The current value of jobs_waiting
         */
        int Getjobs_waiting() { return jobs_waiting; }
        /** Set jobs_waiting
         * \param val New value to set
         */
        void Setjobs_waiting(int val) { jobs_waiting = val; }
        
        void pushJob(int serial);
        
        void advanceTime(int ticks);

    protected:

    private:
        // Integer Queue storing serial numbers of waiting jobs
        LinkedListQueue* qu;
        // Flag indicating whether component is in use.
        bool idle;
        // Number of jobs in queue is supplied by memeber method get_length.
};

#endif // COMPONENT_H
