#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int frameCount;

int *frameAdresses;
int *frameAges;

int reference(int virtualAddr) {
    // aging
    for (int i = 0; i < frameCount; i++) {
        if (frameAges[i] != INT_MAX) {
            frameAges[i]++;
        }
    }

    // if page is found in table
    for (int i = 0; i < frameCount; i++) {
        if (frameAdresses[i] == virtualAddr) {
            frameAges[i] = 0;
            // hit
            return 0;
        }
    }

    int oldestPageIndex = 0;
    int oldestPageAge = 0;

    for (int i = 0; i < frameCount; i++) {
        if (frameAges[i] > oldestPageAge) {
            oldestPageAge = frameAges[i];
            oldestPageIndex = i;
        }
    }

    frameAdresses[oldestPageIndex] = virtualAddr;
    frameAges[oldestPageIndex] = 0;

    // miss
    return 1;
}

void initialize() {
    frameAdresses = malloc(sizeof(int) * frameCount);
    frameAges = malloc(sizeof(int) * frameCount);

    for (int i = 0; i < frameCount; i++) {
        frameAdresses[i] = -1;
        frameAges[i] = INT_MAX;
    }
}

double calculateRatio() {
    initialize();

    printf("Number of page frames: %d\n", frameCount);

    FILE *file = fopen("input.txt", "r");

    char cVal = ' ';
    int iVal = 0;

    double hits = 0;
    double misses = 0;

    for (int i = 0; i < 3882; i++) {
        cVal = fgetc(file);
        if (cVal < '0' || cVal > '9') {
            int result = reference(iVal);

            if (result == 0) {
                hits++;
            } else {
                misses++;
            }

            iVal = 0;
        }
        else {
            iVal *= 10;
            iVal += cVal - '0';
        }
    }

    fclose(file);

    return hits/misses;
}

int main() {
    frameCount = 10;
    printf("Frame Count: %d\nHit/Miss Ratio: %d\n\n", frameCount, calculateRatio());

    frameCount = 50;
    printf("Frame Count: %d\nHit/Miss Ratio: %d\n\n", frameCount, calculateRatio());

    frameCount = 100;
    printf("Frame Count: %d\nHit/Miss Ratio: %d\n\n", frameCount, calculateRatio());

    return 0;
}