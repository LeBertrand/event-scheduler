#include "Component.cpp"
#include <iostream>

int main()
{
    Component s1;
    int last_serial;
    
    s1.pushJob(42);
    
    last_serial = s1.nextJob();
    // Start working on job.
    s1.increaseTime(15);
    
    s1.pushJob(43);
    s1.increaseTime(5);
    // Something else takes 8 seconds.
    s1.advanceTime(7);
    
    s1.pushJob(44);
    s1.increaseTime(25);
    s1.advanceTime(50);
    
    s1.nextJob();
    s1.nextJob();
    s1.nextJob();
    
    s1.pushJob(45);
    s1.pushJob(46);
}