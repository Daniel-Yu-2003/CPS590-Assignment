// Daniel Yu 501120369 daniel1.yu@torontomu.ca
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>
#include <math.h>
#include "queue.h"

int count = 0;
int time = 0;

void handler(int signum, siginfo_t *siginfo, void *c){ // handler for signal
	count++; 
	enqueue(siginfo->si_pid); // qneue the pid of signal caller
}

void handler2(int signum, siginfo_t *siginfo, void *c){
	dequeue();
}

int main(int argc, char **argv){
	int W = atoi(argv[1]); // set and initialize values
	time = atoi(argv[2]);
	int signum; 
	struct sigaction sa; 
	sa.sa_sigaction = handler; // set sigaction to the function
	sa.sa_flags = SA_SIGINFO; // set the flag
	
	makeArr(W);

	while (count != W){ // check if all workers has sent signal
		signum = sigaction(SIGRTMIN, &sa, NULL); // catch signal from worker
	}

	sa.sa_sigaction = handler2;

	while (emptyQueue() == -1){ // while queue not empty
		if(strcmp(argv[3],"RR") == 0){ // round robin
			int workerpid = getValue(W); // get front of queue
			kill (workerpid, SIGCONT); // let worker run
			sleep(time);	// sleep for timeslice
			kill (workerpid, SIGSTOP); // suspend worker after timeslice
			signum = sigaction(SIGRTMIN, &sa, NULL);
		}
		if(strcmp(argv[3],"L7") == 0){ // lucky seven
			int workerpid = getValue(W);	// get front from queue			
			int lenpid = log10(workerpid) + 1; // get length of pid
			char spid[lenpid]; // initialize array of char of length of pid size
			if(lenpid > 4){
				lenpid = 4;
			}
			sprintf(spid, "%d", workerpid); // turn the pid into an array of char
			for(int i = 0; i < lenpid; i++){ // loop length of pid times
				if(spid[lenpid-i] == '7'){ // check if each char in array equals 4
					time = time * 2; // time multiply 2 when it does
					break; // exit out of loop
				}
			}
			kill (workerpid, SIGCONT); // let worker run
			sleep(time); // sleep for timeslice
			kill (workerpid, SIGSTOP);
			signum = sigaction(SIGRTMIN, &sa, NULL);
			time = atoi(argv[2]); // reset time
			
				
		}

	}
	printf("done");
	exit(0);
}

