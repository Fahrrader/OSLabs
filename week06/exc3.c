#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler() {
	printf("SIGINT intercepted.\n");
}

int main() {
   	signal(SIGINT, handler);
    	while (1) {
		sleep(1);
    	}

	return 0;
}