#include <stdio.h>
#include <string.h>

int main() {
	char* string;
	
	scanf("%s", string);
	
	for (int len = strlen(string)-1; len >= 0; len--) {
		printf("%c", string[len]);
	}
	
	return 0;
}