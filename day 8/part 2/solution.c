#include "../../utils.h"

typedef struct MapEntry{
    char code[3];
    int positionLeft;
    int positionRight;
} MapEntry;

MapEntry** mapEntries;

long long LCM(long long a,long long b);
long long GCD(long long int a, long long int b);
int findLocation(char* code, int size);
int* findLocationEnd(char endChar, int size, int* returnSize);

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

    mapEntries = malloc((lineCount-2)*sizeof(MapEntry*));

    for(int i = 0; i < lineCount-2; i++){
        mapEntries[i] = malloc(sizeof(MapEntry));
        sscanf(lines[i+2], "%3c", (char*) &mapEntries[i]->code);
    }

    char* leftPosition = malloc(8);
    char* rightPosition = malloc(8);
    for(int i = 2; i < lineCount; i++){
        sscanf(lines[i]+6, "(%3c, %3c)", leftPosition, rightPosition);
        mapEntries[i-2]->positionLeft = findLocation(leftPosition, lineCount - 2);
        mapEntries[i-2]->positionRight = findLocation(rightPosition, lineCount - 2);
    }

    int sizeOfInstructions = 0;
    while(lines[0][sizeOfInstructions] != '\n'){
        sizeOfInstructions++;
    }

    int arraySize = 0;
    int* endingIndex = findLocationEnd('Z', lineCount - 2, &arraySize);
    int* currentMapEntry = findLocationEnd('A', lineCount - 2, &arraySize);
    int instructionIndex = 0;
    int* stepCounts = malloc(sizeof(int)*6);

    int i = 0;
    int stepCount = 0;
    for(int i = 0; i < arraySize; i++){
        instructionIndex = 0;
        stepCount = 0;
        for(;;){
            if(mapEntries[currentMapEntry[i]]->code[2] == 'Z'){
                break;
            }
            if(instructionIndex >= sizeOfInstructions) instructionIndex = 0;
            if(lines[0][instructionIndex] == 'L'){
                currentMapEntry[i] = mapEntries[currentMapEntry[i]]->positionLeft;
            } else{
                currentMapEntry[i] = mapEntries[currentMapEntry[i]]->positionRight;
            }
            instructionIndex++;
            stepCount++;
        }
        stepCounts[i] = stepCount;
    }
    
    long long solution = 1;
    for(int i = 0; i < arraySize; i++){
        solution = LCM(solution, stepCounts[i]);
    }

    printf("Solution: %lld\n", solution);

    timerEnd;

    return 0;
}

long long GCD(long long int a, long long int b){        
    if(b==0)
        return a;
    return GCD(b,a%b);
}

long long LCM(long long a,long long b){     
    if(a>b)
        return (a/GCD(a,b))*b;
    else
        return (b/GCD(a,b))*a;    
} 

int* findLocationEnd(char endChar, int size, int* returnSize){
    int locationArray[256] = {0};
    int arraySize = 0;
    for(int i = 0; i < size; i++){
        if(mapEntries[i]->code[2] == endChar){
            locationArray[arraySize] = i;
            arraySize++;
        }
    }
    int* returnArray = malloc(sizeof(int)*arraySize);
    memcpy(returnArray, locationArray, sizeof(int)*arraySize);
    *returnSize = arraySize;
    return returnArray;
}

int findLocation(char* code, int size){
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