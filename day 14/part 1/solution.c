#include "../../utils.h"

char** lines;
int lineCount;
int lineLength;

bool moveLines();

int main(int argc, char* argv[]){
    getFileName("input.txt");
    openFile;

    timerStart;

    lineCount = getLineCount(fd);
    lines = malloc(sizeof(char*) * lineCount);
    size_t size = 512;

    for(int i = 0; i < lineCount; i++){
        lines[i] = malloc(sizeof(char) * size);
        if(getline(&lines[i], &size, fd) == -1) break;
    }

    lineLength = strlen(lines[0]);
    while(TRUE){
        if(moveLines() == TRUE) break;
    }

    int solution = 0;

    for(int i = 0; i < lineCount; i++){
        int rockCount = 0;
        for(int j = 0; j < lineLength; j++){
            if(lines[i][j] == 'O') rockCount++;
        }
        solution += rockCount * (lineCount-i);
    }

    printf("Solution: %d\n", solution);

    timerEnd;

    return 0;
}

bool moveLines(){
    bool end = TRUE;
    int lineLength = strlen(lines[0]);
    for(int i = 1; i < lineCount; i++){
        for(int j = 0; j < lineLength; j++){
            if(lines[i][j] != 'O') continue;
            if(lines[i-1][j] != '.') continue;
            end = FALSE;
            lines[i-1][j] = 'O';
            lines[i][j] = '.';
        }
    }
    return end;
}