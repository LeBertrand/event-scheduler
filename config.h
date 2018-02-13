/*
 *  Dummy config values, to be used for testing scheduler.
 *  Real config will be read in from file. Include guard matches real configs,
    so this won't be included.
 */
 
 
#ifndef CONFIGS
#define CONFIGS

const int ARRIVAL_MIN = 10, ARRIVAL_MAX = 200, QUIT_TIME = 10000, CPU_MIN = 5,
    CPU_MAX = 100, D1_MIN = 15, D1_MAX = 80, D2_MIN = 15, D2_MAX = 80;

#endif