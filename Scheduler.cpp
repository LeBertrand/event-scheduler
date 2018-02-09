/*
 *  Main file for Discrete Event simulator project.
 *  Shmuel Jacobs at Temple University, Spring 2018.
 
 *  Initialization has all been placed inside main function.
 *  New serial numbers represent entirely new jobs entering the system
    (as opposed to the event created when a job moves from one component to
    another), and only occur in the place_new_event function. This doesn't
    complicate logging, because the log will look for the matching completion of
    every job that opens, so future openings are no problem.
 *  Main logic of a single pass is in one_round_get_exe, which gets the next
    event and handles it.
 */


#include "Component.cpp"
#include "EventQueue.h"
#include "EventQueue.cpp"
#include "Event.c"
#include "config.h"
#include <time.h>

int ranged_rand(int, int);
bool decide_quit();
void place_new_event(Component*);
void one_round_get_exe(EventQueue*, Component*,Component*,Component*);

int global_time;
int serial_stamp;

int main()
{
    /*  Dont bother seperating into a setup function.
        Setup consists entirely of setting variables, which would have to be
        declared here and passed by location anyway. */
    
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
    
    // Setup Complete.
    
    one_round_get_exe(&event_queue, &cpu, &disk_one, &disk_two);
    
    
    return 0;
}

/*
 *  Main loop. Four major steps in each pass:
 *      Generate new CPU arrival.
 *      Find next job and advance time keeping.
 *      Handle event.
 *      Check if simulation over.
 */
 
 /*  Generally, I've tried to use member methods because I consider it easier to
    code without passing pointers to member objects. However, Object Oriented
    Scheduler class seemed more trouble than it was worth, so Scheduler does
    pass pointers to its own fields. */
 void one_round_get_exe(EventQueue* eq, Component* cpu, Component* disk_one, Component* disk_two)
 {
     // Generate CPU arrival
     place_new_event(cpu);
     
    // Find next job and advance time keeping.
    Event* next = eq->getNext();
    int job_length
    
    // Handle job.
    switch(next->jobtype){
        // TODO: Standardized logging step in all cases.
        case JOB_ARRIVE_CPU:
            // TODO: All logic relies on current_wait being 0 when the queue is
            //  empty. Can I totally factor out the idle flag?
            if(cpu->Getidle()){
                // CPU idle so job doesn't wait. Set idle false.
                cpu->Setidle(false);
            } else {
                // Put job into component queue.
                cpu->pushJob(next->serial);
            }
		
		    // Calculate job length - calculate now only for calculating true
		    // end time - EventQueue doesn't know the wait time, only queue lengths.
		    job_length = ranged_rand(CPU_MIN, CPU_MAX);
		    next->timestamp = global_time + job_length + cpu->getTime();
		
		    // Make event a cpu completion.
		    next->jobtype = JOB_FINISH_CPU;

		    // Put completion into event heap.
		    eq->pushJob(next);
    
            break;
            
        case JOB_FINISH_CPU:
            // TODO: For stats log, we're counting the job as done, because we're interested in throughput. If not, I can change this part.
            // Log completion
            
            // Record if CPU just went idle.
            if(cpu->Getjobs_waiting()==0){
                cpu->Setidle(true);
            }
            // Pop CPU queue to preserve length.
            cpu->nextJob();
            
            // Decide where the job goes
            if(!decide_quit()){
                // Job goes to disk. Choose one.
                if(disk_one->Getjobs_waiting() <= disk_two->Getjobs_waiting()){
                    // Make event a disk 1 arrival
                    next->jobtype = JOB_ARRIVE_D1;
                    // Calculate job length - see similar comment above
                    job_length = ranged_rand(D1_MIN, D1_MAX);
                } else {
                    // Make event a disk 2 arrival
                    next->jobtype = JOB_ARRIVE_D2;
                    // Calculate job length - see similar comment above
                    job_length = ranged_rand(D2_MIN, D2_MAX);
                }
                // Job arrival at disk ready to go. Time stays the same.
                eq->insert(next);
            }
            else {
                // Log completion or something?
                // TODO: Figure out if anything needs to happen here.
            }
            
            break;
            
        case JOB_ARRIVE_D1:
            // TODO: See above thoughts on refactoring in first case.
            if(disk_one->Getidle()){
                // Disk idle so job doesn't wait. Set idle false.
                disk_one->Setidle(false);
            } else {
                // Put job into component queue.
                disk_one->pushJob(next->serial);
            }
            
		    // Calculate job length - calculate now only for calculating true
		    // end time - EventQueue doesn't know the wait time, only queue lengths.
		    job_length = ranged_rand(D1_MIN, D1_MAX);
		    next->timestamp = global_time + job_length + disk_one->getTime();
		
		    // Make event a disk completion.
		    next->jobtype = JOB_FINISH_D1;

		    // Put completion into event heap.
		    eq->pushJob(next);
    
            break;
        
        case JOB_ARRIVE_D2:
            // TODO: See above thoughts on refactoring in first case.
            if(disk_two->Getidle()){
                // Disk idle so job doesn't wait. Set idle false.
                disk_two->Setidle(false);
            } else {
                // Put job into component queue.
                disk_two->pushJob(next->serial);
            }
            
		    // Calculate job length - calculate now only for calculating true
		    // end time - EventQueue doesn't know the wait time, only queue lengths.
		    job_length = ranged_rand(D2_MIN, D2_MAX);
		    next->timestamp = global_time + job_length + disk_two->getTime();
		
		    // Make event a disk completion.
		    next->jobtype = JOB_FINISH_D2;

		    // Put completion into event heap.
		    eq->pushJob(next);
    
            break;
        
        case JOB_FINISH_D1:
            // Record if Disk just went idle.
            if(disk_one->Getjobs_waiting()==0){
                disk_one->Setidle(true);
            }
            // Pop disk queue to preserve length.
            disk_one->nextJob();
            
            break;
            
        case JOB_FINISH_D2:
            // Record if Disk just went idle.
            if(disk_two->Getjobs_waiting()==0){
                disk_two->Setidle(true);
            }
            // Pop disk queue to preserve length.
            disk_two->nextJob();
            
            break;
            
    }
     
    return;
}
 
/*
 *  Function creates new event and places in event queue.
 *  Takes pointer to cpu to allow insertion into queue.
 *  TODO: This is a bad way to distribute events. Can't I just fill the queue\
            during initialization, and then stop generating events?
 */
void place_new_event(Component* cpu)
{
    Event* ev = (Event*) malloc(sizeof(Event));
    // Give event next serial number available.
    ev->serial = serial_stamp++;
    // Record event as occuring
    ev->timestamp = global_time + ranged_rand(ARRIVAL_MIN, ARRIVAL_MAX);
    // Record job as a CPU arrival.
    ev->jobtype = JOB_ARRIVE_CPU;
    
}

/*
 *  Return random int in range [min,max).
 */
int ranged_rand(int min, int max)
{
    return (rand()%(max-min)) + min;
}

/*
 *  Randomly decide whether job is done.
    Get random number in [1,100]. If higher than QUIT_PROB then quit.
 */
bool decide_quit()
{
    int roll = ranged_rand(0,101);
    return (roll > QUIT_PROB*100);
}
