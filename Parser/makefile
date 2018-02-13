CC=gcc

CFLAGS=-c

CLEANUP=rm -rf *.o

all: makeRanLib

makeRanLib: makeLib
	ranlib libParserJobs.a

makeLib: open_job.o close_job.o
	ar rc libParserJobs.a open_job.o close_job.o

open_job.o: open_job.c
	$(CC) $(CFLAGS) open_job.c
	
close_job.o: close_job.c
	$(CC) $(CFLAGS) close_job.c
	
# Compile command
compile:
	gcc Parser.c -o stat-reporter.exe
	
# remove object
clean:
	$(CLEANUP)