#include "../../utils.h"

char** lines;
int* expandedVertical;
int* expandedHorizontal;
int expandedVerticalCount;
int expandedHorizontalCount;
int lineCount;
int lineLength;

typedef struct Cords{
    int y;
    int x;
} Cords;

int main(int argc, char* argv[]){

    getFileName("input.txt");
    openFile;

    timerStart;

    lineCount = getLineCount(fd);
    lines = malloc(sizeof(char*)*lineCount);

    size_t size = 512;

    /* Read all lines from input */
    for(int i = 0; i < lineCount; i++){
        lines[i] = malloc(size);
        if(getline(&lines[i], &size, fd) == -1) break;
    }

    lineLength = strlen(lines[0])-1;

    expandedVertical = malloc(sizeof(int)*lineCount);
    expandedHorizontal = malloc(sizeof(int)*lineLength);

    int i = 0;
    expandedVerticalCount = 0;

    while(i < lineCount){
        bool empty = TRUE;
        for(int a = 0; a < lineLength; a++){
            if(lines[i][a] != '.') {empty = FALSE; break;}
        }
        i++;
        if(empty == FALSE) continue;
        expandedVertical[expandedVerticalCount] = i-1;
        expandedVerticalCount++; 
    }
    i = 0;
    expandedHorizontalCount = 0;
    
    while(i < lineLength){
        bool empty = TRUE;
        for(int a = 0; a < lineCount; a++){
            if(lines[a][i] != '.') {empty = FALSE; break;}
        }
        i++;
        if(empty == FALSE) continue;
        expandedHorizontal[expandedHorizontalCount] = i-1;
        expandedHorizontalCount++;
    }

    Cords** galaxyNumbers = malloc(sizeof(int)*lineCount*lineLength);
    int galaxyCount = 0;
    i = 0;
    for(int a = 0; a < lineCount; a++){
        for(int b = 0; b < lineLength; b++){
            if(lines[a][b] == '#'){
                Cords* cords = malloc(sizeof(Cords));
                cords->y = a;
                cords->x = b;
                galaxyNumbers[i] = cords;
                galaxyCount++;
                i++;
            }
        }
    }

    long solution = 0;

    for(int a = 0; a < galaxyCount; a++){
        for(int b = 0; b < galaxyCount; b++){
            int start; int end;
            if(galaxyNumbers[a]->y >= galaxyNumbers[b]->y){
                start = galaxyNumbers[b]->y;
                end = galaxyNumbers[a]->y;
            } else {
                start = galaxyNumbers[a]->y;
                end = galaxyNumbers[b]->y;
            }
            for(int x = start; x < end; x++){
                if(intBelongsToArray(x, expandedVertical, expandedVerticalCount) == -1){solution++; continue;}
                solution += 1000000;
            }
            if(galaxyNumbers[a]->x >= galaxyNumbers[b]->x){
                start = galaxyNumbers[b]->x;
                end = galaxyNumbers[a]->x;
            } else {
                start = galaxyNumbers[a]->x;
                end = galaxyNumbers[b]->x;
            }
            for(int x = start; x < end; x++){
                if(intBelongsToArray(x, expandedHorizontal, expandedHorizontalCount) == -1){solution++; continue;}
                solution += 1000000;
            }
        }
    }

    // for(int i = 0; i < lineCountExpanded; i++){
    //     for(int j = 0; j < lineLengthExpanded; j++){
    //         printf("%c", linesExpanded[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("Solution: %ld\n", solution/2);

    timerEnd;

    return 0;
}