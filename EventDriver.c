#include <stdio.h>
#include <stdlib.h>
#include "Event.c"

int main()
{
	Event first, second, last;
	first.serial = 266811;
	first.jobtype = JOB_ARRIVE_CPU;
	first.timestamp = 7;

	printf("Event Occured: Serial - %d, Job Code - %d, Ticks - %d\n",
		first.serial, first.jobtype, first.timestamp);
	return EXIT_SUCCESS;
}
