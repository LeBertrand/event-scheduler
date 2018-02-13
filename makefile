CC=gcc

CFLAGS=-c

CLEANUP=rm -rf *.o *.gch

#	Makefile by Shmuel Jacobs, February 12 2018.
#	Lab 1 Operating Systems Spring 2018.
#	I ended up just '#include'ing everything instead of linking, so this make
#	isn't really necessary. I use the optimize flag because I wasn't meticulous
#	and this loop is going to run 1000 times.
#	The only thing really achieved in this makefile is that it makes obvious that
#	Scheduler.cpp is the main class that runs all the others.

# Compile command
compile:
	g++ -o DESimulator.exe Scheduler -O1
	
# remove object
clean:
	$(CLEANUP)