#include "../../utils.h"

typedef struct MapEntry{
    char code[3];
    int positionLeft;
    int positionRight;
} MapEntry;


int findLocation(MapEntry** mapEntries, char* code, int size);

int main(int argc, char* argv[]){

    getFileName("input.txt");
    openFile;

    timerStart;

    size_t size = 24;

    char** lines = malloc(sizeof(char*)*1024);

    int lineCount = getLineCount(fd);

    for(int i = 0; i < lineCount; i++){
        if(i == 0){size = 512;}
        else {size = 24;} 
        lines[i] = malloc(size);
        getline(&lines[i], &size, fd);
    }

    MapEntry** mapEntries = malloc((lineCount-2)*sizeof(MapEntry**));

    for(int i = 0; i < lineCount-2; i++){
        mapEntries[i] = malloc(sizeof(MapEntry));
        sscanf(lines[i+2], "%3c", &mapEntries[i]->code);
    }

    char* leftPosition = malloc(8);
    char* rightPosition = malloc(8);
    for(int i = 2; i < lineCount; i++){
        sscanf(lines[i]+6, "(%3c, %3c)", leftPosition, rightPosition);
        mapEntries[i-2]->positionLeft = findLocation(mapEntries, leftPosition, lineCount - 2);
        mapEntries[i-2]->positionRight = findLocation(mapEntries, rightPosition, lineCount - 2);
    }

    int sizeOfInstructions = 0;
    while(lines[0][sizeOfInstructions] != '\n'){
        sizeOfInstructions++;
    }

    int endingIndex = findLocation(mapEntries, "ZZZ", lineCount - 2);
    int instructionIndex = 0;
    int currentMapEntry = findLocation(mapEntries, "AAA", lineCount - 2);
    int stepCount = 0;

    while(currentMapEntry != endingIndex){
        if(instructionIndex >= sizeOfInstructions) instructionIndex = 0;
        if(lines[0][instructionIndex] == 'L'){
            currentMapEntry = mapEntries[currentMapEntry]->positionLeft;
        } else {
            currentMapEntry = mapEntries[currentMapEntry]->positionRight;
        }
        instructionIndex++;
        stepCount++;
    }

    printf("Solution: %d\n", stepCount);

    timerEnd;

    return 0;
}

int findLocation(MapEntry** mapEntries, char* code, int size){
    for(int i = 0; i < size; i++){
        bool equal = TRUE;
        for(int j = 0; j < 3; j++){
            if(mapEntries[i]->code[j] != code[j]){
                equal = FALSE;
                break;
            }
        }
        if(equal == TRUE) return i;
    }
    return -1;
}