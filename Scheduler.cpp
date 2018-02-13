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
#include "config_reader.c"

int ranged_rand(int, int);
bool decide_quit();
void place_new_event(EventQueue*, int* clock, int* stamp);
bool one_round_get_exe(EventQueue*, Component*,Component*,Component*, int* clock, int* serial_stamp);
int log_event(Event*);

FILE* Log;

// Format Strings for logging constants.
const char* paramstring =
    "AMN %d\nAMX %d\nCMN %d\nCMX %d\n1MN %d\n1MX %d\n2MN %d\n2MX %d\n";
const char* npstring = "SED %d\nITM %d\nQTM %d\nQPB %f\n"; 

int main()
{
    /*  Don't bother seperating into a setup function.
        Setup consists entirely of setting variables, which would have to be
        declared here and passed by location anyway. */
    
    // Create Event queue.
    EventQueue event_queue;
    
    // Create Components.
    Component cpu;
    Component disk_one;
    Component disk_two;
    
    // TODO: moving explicit clock handling out of scheduler. Event timestamp handles time implicitly.
    // Set clock to zero.
    int global_time = INIT_TIME;
    
    // Seed random numbers.
    srand(SEED);
    
    // Create stamp to give events their serial numbers. Start is arbitrary.
    int serial_stamp = 1000;
    
    // Set up and open log file.
    Log = fopen("DES-Log.csv", "w");
    
    // Setup constants
    get_configs();
    
    // Record all constants in first line of log.
    fprintf(Log, paramstring,ARRIVAL_MIN,ARRIVAL_MAX,CPU_MIN,CPU_MAX,D1_MIN,
        D1_MAX,D2_MIN,D2_MAX);
    fprintf(Log, npstring, SEED,INIT_TIME,QUIT_TIME,QUIT_PROB);
    // Print indication of log begin
    fprintf(Log, "!Start\n");
    
    // Put end of simulation in Event Queue.
    Event* conclusion = (Event*) malloc(sizeof(Event));
    conclusion->serial=999;
    conclusion->jobtype=END_SIM;
    conclusion->timestamp=QUIT_TIME;
    event_queue.insert(conclusion);
    
    // Setup Complete.
    
    // Run sim until reaching end sim.
    while(
        one_round_get_exe(&event_queue, &cpu, &disk_one, &disk_two,
            &global_time, &serial_stamp) ) {}
    
    
    // one_round_get_exe(&event_queue, &cpu, &disk_one, &disk_two, &global_time, &serial_stamp);
    // one_round_get_exe(&event_queue, &cpu, &disk_one, &disk_two, &global_time, &serial_stamp);
    // one_round_get_exe(&event_queue, &cpu, &disk_one, &disk_two, &global_time, &serial_stamp);
    
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
bool one_round_get_exe(EventQueue* eq, Component* cpu, Component* disk_one,
    Component* disk_two, int* clock, int* serial_stamp_ptr)
{
    // Generate CPU arrival
    place_new_event(eq, clock, serial_stamp_ptr);
     
    // Find next job and advance time keeping.
    Event* next = eq->getNext();
    int job_length;
    *clock = next->timestamp;
    
    //Log event
    log_event(next);
    
    // Handle job.
    switch(next->jobtype){
        
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
		    /* end time - Scheduler doesn't know the wait time.
		        It just increases timestamp by a reasonable wait. */
		    job_length = ranged_rand(CPU_MIN, CPU_MAX);
		    next->timestamp += job_length;
		
		    // Make event a cpu completion.
		    next->jobtype = JOB_FINISH_CPU;

		    // Put completion into event heap.
		    eq->insert(next);
    
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
		    /* end time - Scheduler doesn't know the wait time.
		        It just increases timestamp by a reasonable wait. */
		    job_length = ranged_rand(D1_MIN, D1_MAX);
		    next->timestamp += job_length;
		
		    // Make event a disk completion.
		    next->jobtype = JOB_FINISH_D1;

		    // Put completion into event heap.
		    eq->insert(next);
    
            break;
        
        case JOB_ARRIVE_D2:
            // TODO: Options to refactor and eliminate FIFO class.
            
            if(disk_two->Getidle()){
                // Disk idle so job doesn't wait. Set idle false.
                disk_two->Setidle(false);
            } else {
                // Put job into component queue.
                disk_two->pushJob(next->serial);
            }
            
		    // Calculate job length - calculate now only for calculating true
		    /* end time - Scheduler doesn't know the wait time.
		        It just increases timestamp by a reasonable wait. */
		    job_length = ranged_rand(D2_MIN, D2_MAX);
		    next->timestamp += job_length;
		
		    // Make event a disk completion.
		    next->jobtype = JOB_FINISH_D2;

		    // Put completion into event heap.
		    eq->insert(next);
    
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
        
        case END_SIM:
            return false;
    }
     
    return true;
}
 
/*
 *  Function creates new event and places in event queue.
 *  Takes pointer to cpu to allow insertion into queue.
 *  TODO: This is a bad way to distribute events. Can't I just fill the queue\
            during initialization, and then stop generating events?
 */
void place_new_event(EventQueue* eq, int* clock, int* serial_stamp)
{
    Event* ev = (Event*) malloc(sizeof(Event));
    // Give event next serial number available.
    ev->serial = *serial_stamp;
    (*serial_stamp)+=1;
    // Record event as occuring
    ev->timestamp = *clock + ranged_rand(ARRIVAL_MIN, ARRIVAL_MAX);
    // Record job as a CPU arrival.
    ev->jobtype = JOB_ARRIVE_CPU;
    
    eq->insert(ev);
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

int log_event(Event* ev)
{
    return fprintf(Log, "%d,%d,%d\n",
        ev->timestamp, ev->jobtype, ev->serial);
}
