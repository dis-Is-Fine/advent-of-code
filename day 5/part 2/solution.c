#include "../../utils.h"
#include <pthread.h>

long int* seedList;
char** lines;
char* mapNames[] = {"seed-to-soil map:\n", "soil-to-fertilizer map:\n",
                "fertilizer-to-water map:\n", "water-to-light map:\n",
                "light-to-temperature map:\n", "temperature-to-humidity map:\n",
                "humidity-to-location map:\n"};
long int mapBeginningLines[8];
int seedPairCount;
int lineCount;
long int** values;
FILE* fd;

long int* handleSeed(int* sNumber);
long int getLocation(long int seed);

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return -1;
    }

    fd = fopen(argv[1], "r");

    if (fd == NULL) {
        printf("File not found\n");
        return -1;
    }

    lineCount = getLineCount(fd);

    seedList = malloc(sizeof(int)*50);
    lines = malloc(sizeof(char*)*lineCount-1);
    values = malloc(sizeof(long int*));

    for(int i = 0; i < lineCount; i++){
        size_t size = 320;
        lines[i] = malloc(size);
        getline(&lines[i], &size, fd);
    }

    int seedLineSize = strlen(lines[0]);

    int seedLineIndex = strlen("seeds: ");
    seedPairCount = 0;

    /* Search for all seed numbers and store them in seedList */
    while(seedLineIndex < seedLineSize) {
        if(isDigit(lines[0][seedLineIndex]) == 1){
            long int number;
            sscanf((char*) (lines[0] + seedLineIndex), "%ld", &number);
            seedList[seedPairCount] = number; 
            seedPairCount++;
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

    for(int i = 0; i < lineCount; i++){
        values[i] = malloc(sizeof(long int)*3);
        sscanf(lines[i], "%ld %ld %ld", values[i], values[i]+1, values[i]+2);
    }

    long int lowestLocation = 0;
    int arg[seedPairCount/2];
    pthread_t threads[seedPairCount/2];

    for(int i = 0; i < seedPairCount/2; i++){
        arg[i] = i*2;
        pthread_create(&threads[i], NULL, (void*(*)(void*))handleSeed, &arg[i]);
    }

    for(int i = 0; i < seedPairCount/2; i++){
        long int* location;
        pthread_join(threads[i], (void**) &location);
        if(*location < lowestLocation || i == 0) lowestLocation = *location;
    }

    printf("Solution: %ld", lowestLocation);

}

long int* handleSeed(int* sNumber){
    int seedNumber = *sNumber;
    long int firstSeed = seedList[seedNumber];
    long int lastSeed = firstSeed + seedList[seedNumber+1];

    long int location = 0;
    long int lowestLocation = 0;

    long int seedCount = lastSeed-firstSeed;
    printf("Starting working on pair %d\n", seedNumber/2);
    for(long int i = firstSeed; i <= lastSeed; i++){
        location = getLocation(i);
        long int seedNo = i - firstSeed; 
        if(seedNo%10000000 == 0) printf("Pair %d, %d/%d\n", seedNumber/2, seedNo, seedCount); 
        if(location < lowestLocation || i == firstSeed) lowestLocation = location;
    }

    long int* retval = malloc(sizeof(long int));
    *retval = lowestLocation;

    printf("Pair %d of %d finished\n", seedNumber/2, seedPairCount/2-1);

    pthread_exit(retval);
}

long int getLocation(long int seed){
    for(int i = 0; i < sizeof(mapBeginningLines)/sizeof(long int) - 1; i++){
        long int maxVal = mapBeginningLines[i+1];
        for(int line = mapBeginningLines[i]+1; line < maxVal; line++){
            if(seed >= values[line][1] && seed <= values[line][1]+values[line][2]){
                long int move = values[line][0] - values[line][1];
                seed = seed + move;
                break;
            }
        }
    }
    return seed;
}