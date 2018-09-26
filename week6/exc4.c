#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigkillHandler() {
	printf("SIGKILL observed.\n");
}

void sigstopHandler() {
	printf("SIGSTOP observed.\n");
}

void sigusr1Handler() {
	printf("SIGUSR1 observed.\n");
}

int main() {
   	signal(SIGKILL, sigkillHandler);
   	signal(SIGSTOP, sigstopHandler);
   	signal(SIGUSR1, sigusr1Handler);
    	while (1) {
		sleep(1);
    	}

	return 0;
}