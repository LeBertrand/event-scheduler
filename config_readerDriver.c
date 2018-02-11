#include "config_reader.c"

int main()
{
    get_configs();
    
    printf("Input value for ARRIVAL_MAX = %i\n", ARRIVAL_MAX);
    printf("Input value for ARRIVAL_MIN = %i\n", ARRIVAL_MIN);
    printf("Input value for QUIT_PROB = %f\n", QUIT_PROB);
    
    return 0;
}