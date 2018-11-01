#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <memory.h>
#include <unistd.h>

int main() {
    char* text = "This is a nice day";

    size_t size = strlen(text) + 1;

    FILE *f = fopen("ex1.txt", "w");
    ftruncate(fileno(f), size - 1);
    fclose(f);

    int file = open("ex1.txt", O_RDWR);

    char *map;
    map = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, file, 0);

    for (size_t i = 0; i < size; i++) {
        map[i] = text[i];
    }

    return 0;
}