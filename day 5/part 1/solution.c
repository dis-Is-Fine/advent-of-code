#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../utils.h"

long int* seedList;
char** lines;
char* mapNames[] = {"seed-to-soil map:\n", "soil-to-fertilizer map:\n",
                "fertilizer-to-water map:\n", "water-to-light map:\n",
                "light-to-temperature map:\n", "temperature-to-humidity map:\n",
                "humidity-to-location map:\n"};
int mapBeginningLines[8];
int seedCount;
int lineCount;
FILE* fd;

long int handleSeed(int seedNumber);

int main(int argc, char *argv[]) {

    // if(argc != 2) {
    //     printf("Usage: %s <input_file>\n", argv[0]);
    //     return -1;
    // }

    fd = fopen("input.txt", "r");

    if (fd == NULL) {
        printf("File not found\n");
        return -1;
    }

    lineCount = getLineCount(fd);

    seedList = malloc(sizeof(int)*50);
    lines = malloc(sizeof(char*)*lineCount-1);

    for(int i = 0; i < lineCount; i++){
        size_t size = 320;
        lines[i] = malloc(size);
        getline(&lines[i], &size, fd);
    }

    int seedLineSize = strlen(lines[0]);

    int seedLineIndex = strlen("seeds: ");
    seedCount = 0;

    /* Search for all seed numbers and store them in seedList */
    while(seedLineIndex < seedLineSize) {
        if(isDigit(lines[0][seedLineIndex]) == 1){
            long int number;
            sscanf((char*) (lines[0] + seedLineIndex), "%ld", &number);
            seedList[seedCount] = number; 
            seedCount++;
            seedLineIndex += sizeOfLong(number);
        } else {
        seedLineIndex++;
        }
    }

    for(int i = 0; i < lineCount; i++){
        char* line = lines[i];
        for(int j = 0; j < sizeof(mapNames)/sizeof(char*); j++){
            if(stringEqual(mapNames[j], line) == 1){
                mapBeginningLines[j] = i;
            }
        }
    }
    mapBeginningLines[7] = lineCount;

    long int lowestLocation = 0;
    for(int i = 0; i < seedCount; i++){
        long int location = handleSeed(i);
        if(location < lowestLocation || i == 0) lowestLocation = location;
    }

    printf("Solution %ld", lowestLocation);

}

long int handleSeed(int seedNumber){
    long int seed = seedList[seedNumber];
    
    for(int i = 0; i < sizeof(mapBeginningLines)/sizeof(int); i++){
        for(int line = mapBeginningLines[i]+1; line < mapBeginningLines[i+1]; line++){
            long int destination = 0;
            long int source = 0;
            long int length = 0;
            sscanf(lines[line], "%ld %ld %ld", &destination, &source, &length);
            if(seed >= source && seed <= source+length){
                long int move = destination - source;
                seed = seed + move;
                break;
            }
        }
    }

    return seed;
}