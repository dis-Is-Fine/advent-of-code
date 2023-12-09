#include "../../utils.h"

long lineCount;
long** numberArray;
long* arraySize;

long handleLine(int lineNumber);
void reverseArray(long* array, int arraySize);

int main(int argc, char* argv[]){

    getFileName("input.txt");
    openFile;

    timerStart;

    lineCount = getLineCount(fd);

    size_t size = 256;

    char* lineBuf = malloc(size);

    numberArray = malloc(sizeof(long*)*lineCount);
    arraySize = malloc(sizeof(long)*lineCount);

    int currentLine = 0;
    /* Parse the input file */
    while(getline(&lineBuf, &size, fd)!= -1){
        long i = 0;
        arraySize[currentLine] = 0;
        numberArray[currentLine] = malloc(sizeof(long)*32);
        while(lineBuf[i] != '\n'){
            if(isDigit(lineBuf[i]) == TRUE || lineBuf[i] == '-'){
                sscanf(lineBuf+i, "%d", &numberArray[currentLine][arraySize[currentLine]]);
                i += sizeOfNumber(numberArray[currentLine][arraySize[currentLine]]);
                arraySize[currentLine]++;
            } else {
                i++;
            }
        }
        currentLine++;
    }

    free(lineBuf);

    for(int i = 0; i < lineCount; i++){
        reverseArray(numberArray[i], arraySize[i]);
    }

    long solution = 0;
    for(int i = 0; i < lineCount; i++){
        solution += handleLine(i);
    }

    printf("Solution: %d\n", solution);

    timerEnd;

    return 0;
}

long handleLine(int lineNumber){
    long* subArrays[32000];
    long a = 1;
    bool end = FALSE;
    long lastArraySize = arraySize[lineNumber];
    subArrays[0] = malloc(sizeof(long)*lastArraySize);
    memcpy(subArrays[0], numberArray[lineNumber], sizeof(long)*lastArraySize);

    while(end == FALSE){
        end = TRUE;
        subArrays[a] = malloc(sizeof(long)*lastArraySize);
        for(long j = 0; j < lastArraySize-1; j++){
            subArrays[a][j] = subArrays[a-1][j] - subArrays[a-1][j+1];
            if(subArrays[a][j] != 0) end = FALSE;
        }
        printf("\n");
        lastArraySize--;
        a++;
    }

    long arrayCount = a-1;
    for(long i = arrayCount-1; i >= 0; i--){
        subArrays[i][lastArraySize+1] = subArrays[i][lastArraySize] - subArrays[i+1][lastArraySize];
        lastArraySize++;
    }

    int temp = arraySize[lineNumber]+1;
    for(long i = 0; i < a; i++){
        for(long j = 0; j < temp; j++){
            if(j == (temp - 1)) {
                printf("\x1b[1;32m%d\x1b[0m", subArrays[i][j]);
            } else {
                printf("%d ", subArrays[i][j]);
            }
        }
        printf("\n");
        temp--;
    }

    return subArrays[0][lastArraySize];
}

void reverseArray(long* array, int arraySize){
    long temp = 0;
    for(int i = 0; i < arraySize/2; i++){
        temp = array[i];
        array[i] = array[arraySize-i-1];
        array[arraySize-i-1] = temp;
    }
}