/**
Ciara Mcmullin
04 May 2018
An alarm clock program that uses fork, pause, signal, and alarm 
**/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include "csapp.h"

// alarm clock handler
void ALARMhandler(int sig){
	signal(SIGALRM, SIG_IGN);
	signal(SIGALRM, ALARMhandler);
}

int main (int argc, char ** argv) {

	// printf("starting alarm...\n");
	// argv[0] is remind_me
	// argv[1] is the time in minutes
	// argv[2] is the message
	
	// get process ID of remind me and display to console
	pid_t pid;

	// check if pid is valid/...
	if((pid = getppid())<0){
		perror("unable to get pid...");
	}
	else {
		printf("%s process-id %d\n ", argv[0], pid);
	}

	// create fork
	pid_t p = Fork();

	// child process...
	if (p == 0) {

		//printf("child process!!!");

		char message[argc];
		// check if message is empty
		if(argc == 2){
			strcpy(message, "your alarm with no message is going off!!");
		}

		else {
			// message variable
			strcpy(message, argv[2]);
		}

		// if more than one word
		if(argc > 3) {
			int i = 3;
			while(i < argc){
				strcat(message, " ");
				strcat(message, argv[i]);
				i++;
			}
		}

		int alarmTime = stringToInt(argv[1]);
		//printf("%d\n", alarmTime);
		// set signal alarm and pause
		signal(SIGALRM, ALARMhandler);
		alarm(alarmTime);
		pause();
		printf("%s\n", message); 

	}

	// parent process...
	else {
		//printf("parent process!!!");
		exit(1);
	}	
	
	return 0;
}


// string to integer conversion function
int stringToInt(char * a) {

	int c, sign, offset, n;
	// if negative...
	if (a[0] == '-') {
    	sign = -1;
  	}
 	// sign of number
  	if (sign == -1) { 
   		offset = 1;
  	}
  	else {
    	offset = 0;
  	}
 
  	n = 0;

  	for (c = offset; a[c] != '\0'; c++) {
    	n = n * 10 + a[c] - '0';
  	}

  	if (sign == -1) {
    	n = -n;
  	}
  	return n;
	}
