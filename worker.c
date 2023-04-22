// Daniel Yu 501120369 daniel1.yu@torontomu.ca
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char **argv ){
	FILE *file;
	int spid = atoi(argv[2]); // get pid of scheduler
	int pid = getpid(); // get own pid
	file = fopen(argv[1], "w"); //open file
	kill (spid, SIGRTMIN); // send signal to scheduler
	kill (pid, SIGSTOP); // stop self
	for(int i = 0; i < 40; i++){ // loop 40 times
		fprintf(file, "*"); // print in file
		fflush(file); // flush contents of file
		sleep(1); 
	}
	fclose(file); // close filw
	kill (spid, SIGRTMIN);
	exit(0);
}
