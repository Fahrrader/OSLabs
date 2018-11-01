#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int buffer = 0;

void *producer() {
    int n = 1;
    while (1) {
        if (buffer == 0) {
            buffer = n;
            printf("Produced %d\n", n);
            n++;
        }
    }
}

void *consumer() {
    int n = 0;
    while (1) {
        if (buffer != 0) {
            n = buffer;
            printf("Consumed %d\n", n);
            buffer = 0;
        }
    }
}

int main() {
    pthread_t p_tid, c_tid;

    pthread_create(&p_tid, NULL, producer, NULL);
    pthread_create(&c_tid, NULL, consumer, NULL);
    pthread_join(p_tid, NULL);
    pthread_join(c_tid, NULL);
}