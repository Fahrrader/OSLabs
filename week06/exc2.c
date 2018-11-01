#include <stdio.h>
#include <memory.h>
#include <unistd.h>

int main() {
    	char in[] = "Marquet\n";

    	int pipes[2];
    	pipe(pipes);
	
	int pid = fork();
	if (pid == 0) {
	        write(pipes[1], in, sizeof(in) + 1);
	} else {
		sleep(1);
		char out[strlen(in)];
		read(pipes[0], out, sizeof(out) + 1);
		printf("%s", out);
    	}

	return 0;
}