#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>

int getLineCount(FILE* fd);
int isDigit(int ch);
int sizeOfNumber(int number);
int sizeOfLong(long int number);
int stringEqual(char* str1, char* str2);
int intBelongsToArray(int value, int values[], int size);
int largestInIntArray(int values[], int size);

typedef enum {FALSE = 0, TRUE = 1} bool;

#define timerStart clock_t __start = clock(); \
    struct timeval __startTv; \
    gettimeofday(&__startTv, NULL);
#define timerEnd clock_t __end = clock(); \
    struct timeval __endTv; \
    gettimeofday(&__endTv, NULL); \
    clock_t __cpuTime = __end - __start; \
    long double __time = ((1000000 * __endTv.tv_sec) + __endTv.tv_usec) - ((1000000 * __startTv.tv_sec) + __startTv.tv_usec); \
    printf("CPU time: %ld, in seconds: %.6Lfs\n", __cpuTime, __time/1000000);
    