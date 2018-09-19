#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *traveler(void *arg) {
    printf("Running thread #%i now.\n", arg);
    pthread_exit(NULL);
}


int main() {
    int n = 5;
    pthread_t t;

    for (int i = 0; i < n; i++) {
        printf("Created thread #%i. Some text. Haha, funny me.\n", i);
        pthread_create(&t, NULL, traveler, (void *)i);
        pthread_join(t, NULL);
    }
}