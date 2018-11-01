#include <stdio.h>

void swap(int *a, int *b) {
	int c = *a;
	*a = *b;
	*b = c;
}

void bubble_sort(int a[], int count) {
	int n = count;
	int swapped = 1;
	while (swapped) {
		swapped = 0;
		for (int i = 1; i < n; i++) {
			if (a[i-1] > a[i]) {
				swap(&a[i-1], &a[i]);
				swapped = 1;
			}
		}
		n--;
	}
}

int main() {
	return 0;
}