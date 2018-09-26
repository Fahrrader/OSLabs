#include <stdio.h>
#include <memory.h>
#include <unistd.h>

int main() {
    	char in[] = "Marquet\n";
    	char out[strlen(in)];

    	int pipes[2];
    	pipe(pipes);

   	write(pipes[1], in, sizeof(in) + 1);
    	read(pipes[0], out, sizeof(out) + 1);
	printf("%s", out);

	return 0;
}