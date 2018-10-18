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

    // look for page in the table
    for (int i = 0; i < frameCount; i++) {
        if (frameAdresses[i] == virtualAddr) {
            frameAges[i] = 0;
            // yay! hit
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

    // everything failed. miss
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

void calculateRatio() {
    initialize();

    printf("Number of page frames: %d\n", frameCount);

    FILE *file = fopen("input.txt", "r");

    char cVal = ' ';
    int iVal = 0;
    int result;
    int hits = 0, misses = 0;

    for (int i = 0; i < 3882; i++) {
        cVal = fgetc(file);
        if (cVal < '0' || cVal > '9') {
            result = reference(iVal);

            if (result == 0) {
                hits++;
            } else {
                misses++;
            }

            iVal = 0;
        } else {
            iVal *= 10;
            iVal += cVal - '0';
        }
    }

    printf("Frame Count: %d\nHit/Miss Ratio: %d/%d\n\n", frameCount, hits, misses);

    fclose(file);
}

int main() {
    frameCount = 10;
    calculateRatio();

    frameCount = 50;
    calculateRatio();

    frameCount = 100;
    calculateRatio();

    scanf("%d", frameCount);

    return 0;
}