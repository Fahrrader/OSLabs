#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>

void handler() {
	exit(0);
}

int main() {
	int pipes[2];
    	pipe(pipes);

    	printf("Parent forks child 1.\n");
    	int pid1 = fork();

    	if (pid1 == 0) {
        	sleep(1);
        	int pid2;
        	read(pipes[0], &pid2, sizeof(int));
        	close(pipes[0]);
        	printf("Child 1 acquired PID. Pid = %d.\n", pid2);
        	sleep(3);
        	printf("Child 1 stops child 2.\n");
        	kill(pid2, SIGSTOP);
        	sleep(1);
        	printf("Child 1 continues child 2.\n");
        	kill(pid2, SIGCONT);
        	sleep(1);
        	printf("Child 1 terminates child 2.\n");
        	kill(pid2, SIGINT);
    	} else {
        	printf("Parent forks child 2.\n");
        	int pid2 = fork();

        	if (pid2 == 0) {
	            	signal(SIGINT, handler);

	            	while (1) {
	                	sleep(1);
			}
	        } else {
	            	printf("Parent assigns PID to child 1. Pid = %d.\n", pid2);
	            	write(pipes[1], &pid2, sizeof(int));
	            	close(pipes[1]);
	            	printf("Parent begins waiting for child 2.\n");
	            	int status = 0;
	            	waitpid(pid2, &status, 0);
	        	printf("Parent finished waiting.\n");
		}
	}

	return 0;
}