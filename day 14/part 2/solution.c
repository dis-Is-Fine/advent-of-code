#include "../../utils.h"

#define CYCLES_COUNT 1000000000

char** lines;
int lineCount;
int lineLength;
int* arrayVertical;
int* arrayHorizontal;

int findCycle(int numberV, int numberH, int arraySize);
bool moveLinesNorth();
bool moveLinesWest();
bool moveLinesSouth();
bool moveLinesEast();

int main(int argc, char* argv[]){
    getFileName("input.txt");
    openFile;

    timerStart;

    lineCount = getLineCount(fd);
    lines = malloc(sizeof(char*) * lineCount);
    arrayVertical = calloc(10000, sizeof(int));
    arrayHorizontal = calloc(10000, sizeof(int));

    size_t size = 512;

    for(int i = 0; i < lineCount; i++){
        lines[i] = malloc(sizeof(char) * size);
        if(getline(&lines[i], &size, fd) == -1) break;
    }

    lineLength = strlen(lines[0]);
    int topOfArray = 0;
    int cycleStart;
    int cycleLength;

    for(int iter = 0; iter < CYCLES_COUNT; iter++){
        while(moveLinesNorth() == FALSE);
        while(moveLinesWest() == FALSE);
        while(moveLinesSouth() == FALSE);
        while(moveLinesEast() == FALSE);

        int verticalCheck = 0;
        int horizontalCheck = 0;
        
        for(int i = 0; i < lineCount; i++){
            int rockCount = 0;
            for(int j = 0; j < lineLength; j++){
                if(lines[i][j] == 'O') rockCount++;
            }
            verticalCheck += rockCount * (lineCount-i);
        }

        for(int i = 0; i < lineLength; i++){
            int rockCount = 0;
            for(int j = 0; j < lineCount; j++){
                if(lines[j][i] == 'O') rockCount++;
            }
            horizontalCheck += rockCount * (lineCount-i);
        }

        int indexV = intBelongsToArray(verticalCheck, arrayVertical, topOfArray);
        int indexH = intBelongsToArray(horizontalCheck, arrayHorizontal, topOfArray);
        arrayVertical[topOfArray] = verticalCheck;
        arrayHorizontal[topOfArray++] = horizontalCheck;
        if(indexV == -1 || indexH == -1) continue;

        int tmp = findCycle(verticalCheck, horizontalCheck, topOfArray);

        if(tmp == -1) continue;
        cycleStart = indexV;
        cycleLength = tmp;
        break;
    }

    int solution = arrayVertical[(CYCLES_COUNT - cycleStart + cycleLength)%cycleLength + cycleStart];

    printf("Solution: %d\n", solution);

    timerEnd;

    return 0;
}

int findCycle(int numberV, int numberH, int arraySize){
    int cycleStartV = intBelongsToArray(numberV, arrayVertical, arraySize);
    int cycleEndV = intBelongsToArray(numberV, arrayVertical+cycleStartV+1, arraySize-cycleStartV-1) + cycleStartV + 1;
    if(cycleStartV == -1 || (cycleEndV-cycleStartV-1) == -1) return -1;
    if((cycleEndV + cycleEndV - (cycleStartV + cycleStartV)) >= arraySize) return -1;
    for(int i = cycleStartV; i < cycleEndV - cycleStartV; i++){
        if(arrayVertical[i] != arrayVertical[i+(cycleEndV-cycleStartV)]) return -1;
    }
    int cycleStartH = intBelongsToArray(numberH, arrayHorizontal, arraySize);
    int cycleEndH = intBelongsToArray(numberH, arrayHorizontal+cycleStartH+1, arraySize-cycleStartH-1) + cycleStartH + 1;
    if(cycleStartH == -1 || (cycleEndH - cycleStartH - 1) == -1) return -1;
    if(cycleStartH != cycleStartV || cycleEndH != cycleEndV) return -1;
    if((cycleEndH + cycleEndH - (cycleStartH + cycleStartH)) >= arraySize) return -1;
    for(int i = cycleStartV; i < cycleEndV - cycleStartV; i++){
        if(arrayVertical[i] != arrayVertical[i+(cycleEndV-cycleStartV)]) return -1;
    }
    return cycleEndV - cycleStartV;
}

bool moveLinesNorth(){
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

bool moveLinesWest(){
    bool end = TRUE;
    int lineLength = strlen(lines[0]);
    for(int i = 0; i < lineCount; i++){
        for(int j = 1; j < lineLength-1; j++){
            if(lines[i][j] != 'O') continue;
            if(lines[i][j-1] != '.') continue;
            end = FALSE;
            lines[i][j-1] = 'O';
            lines[i][j] = '.';
        }
    }
    return end;
}

bool moveLinesSouth(){
    bool end = TRUE;
    int lineLength = strlen(lines[0]);
    for(int i = lineCount-2; i >= 0; i--){
        for(int j = 0; j < lineLength; j++){
            if(lines[i][j] != 'O') continue;
            if(lines[i+1][j] != '.') continue;
            end = FALSE;
            lines[i+1][j] = 'O';
            lines[i][j] = '.';
        }
    }
    return end;
}

bool moveLinesEast(){
    bool end = TRUE;
    int lineLength = strlen(lines[0]);
    for(int i = 0; i < lineCount; i++){
        for(int j = lineLength-2; j >= 0; j--){
            if(lines[i][j] != 'O') continue;
            if(lines[i][j+1] != '.') continue;
            end = FALSE;
            lines[i][j+1] = 'O';
            lines[i][j] = '.';
        }
    }
    return end;
}
