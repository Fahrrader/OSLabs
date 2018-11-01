#include <stdio.h>
#include <string.h>

void swap(int *a, int *b) {
	int c = *a;
	*a = *b;
	*b = c;
}

int main(int argn, char *args[]) {
	int a, b;
	
	printf("Enter two integers to test swapping function:\n");
	scanf("%i%i", &a, &b);
	swap(&a, &b);
	
	return 0;
}