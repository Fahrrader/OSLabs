#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <memory.h>
#include <unistd.h>

int main(void)
{
    FILE *file = fopen("ex1.txt", "r");
    struct stat st;
    stat("ex1.txt", &st);
    off_t sSize = st.st_size;
    fclose(file);

    *file = fopen("ex1.memcpy.txt", "w");
    ftruncate(fileno(file), sSize);
    fclose(file);

    int source = open("ex1.txt", O_RDWR);
    int destination = open("ex1.memcpy.txt", O_RDWR);

    char *sMap, *dMap;
    sMap = mmap(NULL, sSize, PROT_READ|PROT_WRITE, MAP_SHARED, source, 0);
    dMap = mmap(NULL, sSize, PROT_READ|PROT_WRITE, MAP_SHARED, destination, 0);

    memcpy(dMap, sMap, sSize);

    return 0;
}