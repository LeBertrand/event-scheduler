#include "Component.cpp"
#include <iostream>

int main()
{
    Component s1, s2;
    int last_serial;
    
    s1.pushJob(42);
    
    last_serial = s1.nextJob();
    // Start working on job.
    s1.setTime(15);
    
    // Something else takes 8 seconds.
    s1.advanceTime(7);
    /*
    std::cout << "Is Server 1 Idle? " << s1.Getidle << std::endl;
    std::cout << "How many jobs waiting? " << s1.Getjobs_waiting << std::endl;*/
}