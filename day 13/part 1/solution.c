#include "../../utils.h"

int lineCount;
char** mirrorLines;

int handleMirror(int lineCount);
int checkHorizontal(int lineCount);
int checkVertical(int lineCount);

int main(int argc, char* argv[]){

    getFileName("input.txt");
    openFile;

    timerStart;

    mirrorLines = malloc(sizeof(char*)*30);
    lineCount = getLineCount(fd);

    size_t size = 64;

    for(int i = 0; i < 30; i++){
        mirrorLines[i] = malloc(size);
    }

    int index = 0;
    int subIndex = 0;
    int solution = 0;
    while(index <= lineCount){
        getline(&mirrorLines[subIndex], &size, fd);
        index++;
        if(mirrorLines[subIndex][0] != '\n') {subIndex++; continue;}
        solution += handleMirror(subIndex);
        subIndex = 0;
    }

    printf("Solution: %d\n", solution);

    timerEnd;

    return 0;
}

int handleMirror(int lineCount){
    int solution = checkHorizontal(lineCount);
    solution += checkVertical(lineCount);
    return solution;
}

int checkHorizontal(int lineCount){
    for(int i = 0; i < lineCount/2; i++){
        bool valid = TRUE;
        for(int j = 0; j <= i; j++){
            if(!stringEqual(mirrorLines[i-j], mirrorLines[i+j+1])){
                valid = FALSE;
                break;
            }
        }
        if(valid) return (i+1)*100;
    }
    char** tempLines = malloc(sizeof(char*)*lineCount);
    for(int i = 0; i < lineCount; i++){
        tempLines[i] = malloc(sizeof(char)*strlen(mirrorLines[i]));
        memcpy(tempLines[i], mirrorLines[i], strlen(mirrorLines[i]));
    }
    reverseArray((void**) tempLines, lineCount);

    for(int i = 0; i < lineCount/2; i++){
        bool valid = TRUE;
        for(int j = 0; j <= i; j++){
            if(!stringEqual(tempLines[i-j], tempLines[i+j+1])){
                valid = FALSE;
                break;
            }
        }
        if(valid) return (lineCount-i-1)*100;
    }

    return 0;
}

int checkVertical(int lineCount){
    int lineLength = strlen(mirrorLines[0]);
    for(int i = 0; i < lineLength/2; i++){
        bool valid = TRUE;
        for(int j = 0; j <= i; j++){
            if(!columnEqual(mirrorLines, i-j, i+j+1, lineCount)){
                valid = FALSE;
                break;
            }
        }
        if(valid) return i+1;
    }
    char** tempLines = malloc(sizeof(char*)*lineCount);
    for(int i = 0; i < lineCount; i++){
        tempLines[i] = malloc(sizeof(char)*strlen(mirrorLines[i]));
        memcpy(tempLines[i], mirrorLines[i], strlen(mirrorLines[i]));
        reverseString(tempLines[i]);
    }

    for(int i = 0; i < lineLength/2; i++){
        bool valid = TRUE;
        for(int j = 0; j <= i; j++){
            if(!columnEqual(tempLines, i-j, i+j+1, lineCount)){
                valid = FALSE;
                break;
            }
        }
        if(valid) return (lineLength-i-2);
    }

    return 0;
}
