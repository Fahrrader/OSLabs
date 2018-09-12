#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
	
    for ( ; ; ) {
        printf("\n");
        scanf("%s", command);
        system(command);
    }
	
	return 0;
}