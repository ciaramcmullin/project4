/**
Ciara McMullin
04 May 2018
A program that displays the content of home directory regardless of the actual currently working directory
**/
#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"


int main() {
	// get home enviroment and linux commands to display content
	char * home = getenv("HOME");
	char * argv[] = {"ls", "-l", home, NULL};
	char * envp[] = {0};

	// check if home directory was found
	if(envp == NULL){
		printf("HOME DIRECTORY NOT FOUND");
		exit(1);
	}

	//printf("home directory %s\n", *envp);
	// create fork using pid_t wrapper 
	pid_t pid = fork();

	// check to see if fork failed
	if( pid < 0){
		perror("fork error");
		exit (1);
	}

	// if fork didnt fail...
	if(pid == 0){

		//printf("home directory %s\n", *envp);
		//printf("argv %s\n", *argv);

		// check to see if execve valid
		if(execve("/bin/ls",argv, envp) > 0){
			// execute program
			execve("/bin/ls", argv, envp);

		}
		// if execve not valid
		else {
			unix_error("Execve error");
		}
	}

	// wait for child to terminate
	Wait(NULL);
	//exit(1);

	// return 0 for success
	return 0;


}