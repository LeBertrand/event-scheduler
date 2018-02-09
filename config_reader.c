#include <stdio.h>
/*
 *  Read in config values from config file.
 *  Shmuel Jacobs at Temple University, Spring 2018.
 
 *  Designed to be preprocessor included in main file.
 *  Declares and sets global variables for use by sceduler.
 */
 
#ifndef CONFIGS
#define CONFIGS

const int ARRIVAL_MIN, ARRIVAL_MAX, QUIT_TIME, CPU_MIN, CPU_MAX, D1_MIN, D1_MAX,
    D2_MIN, D2_MAX;
    
const float QUIT_PROB;
void get_configs(){
    FILE* config = fopen("config", "r");
    if(config == NULL){
        puts("Unable to find config file. Ending program.");
        exit(2);
    }
}

#endif