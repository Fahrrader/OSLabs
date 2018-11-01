#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int n = 0, pid = fork();
	
    if (pid > 0)
        printf("Hello from parent %d\n", pid);
    else if (pid == 0)
        printf("Hello from child %d\n", pid);
	
    return 0;
}