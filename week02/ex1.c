#include <stdio.h>
#include <float.h>
#include <limits.h>

int main() {
	int a = INT_MAX;
	float b = FLT_MAX;
	double c = DBL_MAX;
	
	printf("Values and sizes of:\nint = %i, %lu bytes\nfloat = %f, %lu bytes\ndouble = %f, %lu bytes",
		a, sizeof(a), b, sizeof(b), c, sizeof(c));
	
	return 0;
}