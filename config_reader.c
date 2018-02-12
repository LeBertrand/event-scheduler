#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 *  Read in config values from config file.
 *  Shmuel Jacobs at Temple University, Spring 2018.
 
 *  Designed to be preprocessor included in main file.
 *  Declares and sets global variables for use by sceduler.
 
 *  Must be included before any dummy configs. Include guard designed to prevent
    multiple declarations of constants, so dummy declarations will stop this 
    from executing.
 */
 
#ifndef CONFIGS
#define CONFIGS

int ARRIVAL_MIN, ARRIVAL_MAX, INIT_TIME, QUIT_TIME, CPU_MIN, CPU_MAX, D1_MIN, D1_MAX,
    D2_MIN, D2_MAX, SEED;
    
float QUIT_PROB;
void get_configs(){
    FILE* config = fopen("config", "r");
    
    if(config == NULL){
        puts("Unable to find config file. Ending program.");
        exit(2);
    }
    /* Initialize counter to make sure enough configs read in. Not a good fail-
    safe, but the best I can think of. */
    int num_configs_set = 0;
    
    // Read in each line of file.
    char config_line[11];
    while(fgets(config_line, 11, config)){
        /* Can't easily switch on string, and don't want to use numbered
        config codes, because editing config would be harder. */
        
        if(!strncmp(config_line,"AMX",3)){
            /* Find number from fifth character in line until NL. Atoi should
            stop reading when it hits non-numeric char at \n. */
            ARRIVAL_MAX = atoi(config_line+4);
            num_configs_set++;
        }
        else if(!strncmp(config_line,"AMN",3)){
            ARRIVAL_MIN = atoi(config_line+4);
            num_configs_set++;
        } else if(!strncmp(config_line,"ITM",3)){
            INIT_TIME = atof(config_line+4);
            num_configs_set++;
        } else if(!strncmp(config_line,"QTM",3)){
            QUIT_TIME = atoi(config_line+4);
            num_configs_set++;
        } else if(!strncmp(config_line,"CMX",3)){
            CPU_MAX = atoi(config_line+4);
            num_configs_set++;
        } else if(!strncmp(config_line,"CMN",3)){
            CPU_MIN = atoi(config_line+4);
            num_configs_set++;
        } else if(!strncmp(config_line,"1MX",3)){
            D1_MAX = atoi(config_line+4);
            num_configs_set++;
        } else if(!strncmp(config_line,"1MN",3)){
            D1_MIN = atoi(config_line+4);
            num_configs_set++;
        } else if(!strncmp(config_line,"2MX",3)){
            D2_MIN = atoi(config_line+4);
            num_configs_set++;
        } else if(!strncmp(config_line,"2MN",3)){
            D2_MIN = atoi(config_line+4);
            num_configs_set++;
        } else if(!strncmp(config_line,"QPB",3)){
            QUIT_PROB = atof(config_line+4);
            num_configs_set++;
        } else if(!strncmp(config_line,"SED",3)){
            SEED = atof(config_line+4);
            num_configs_set++;
        }
    } // Now leaving loop. Done reading file.
    
    
    // Configs all read in? Last check before configs are trusted.
    if(num_configs_set != 12){
        printf("%d configs read in. Correct \"config\" in this dir.\n", num_configs_set);
        exit(2);
    }
    // Close file.
    fclose(config);
}

#endif