// #define DEV_MODE
#include "../../utils.h"

char** linesExpanded;
int lineCountExpanded;
int lineLengthExpanded;

int main(int argc, char* argv[]){

    getFileName("input.txt");
    openFile;

    timerStart;

    int lineCount = getLineCount(fd);
    char** lines = malloc(sizeof(char*)*lineCount);

    size_t size = 512;

    /* Read all lines from input */
    for(int i = 0; i < lineCount; i++){
        lines[i] = malloc(size);
        if(getline(&lines[i], &size, fd) == -1) break;
    }

    int lineLength = strlen(lines[0])-1;

    char** tempLines = malloc(sizeof(char*)*lineCount*2);

    int i = 0;
    int j = 0;
    lineCountExpanded = lineCount;

    /* Expand lines vertically */
    while(i < lineCount){
        bool empty = TRUE;
        for(int a = 0; a < lineLength; a++){
            if(lines[i][a] != '.') {empty = FALSE; break;}
        }
        tempLines[j] = malloc(sizeof(char)*lineLength);
        memcpy(tempLines[j], lines[i], lineLength);
        i++; j++;
        if(empty == FALSE) continue;
        tempLines[j] = malloc(sizeof(char)*lineLength);
        memset(tempLines[j], '.', lineLength);
        j++; lineCountExpanded++;
    }

    /* Free space for orginal file */
    for(int a = 0; a < lineCount; a++){
        free(lines[a]);
    }
    free(lines);
    
    /* Allocate space for final data */
    linesExpanded = malloc(sizeof(char*)*lineCountExpanded);
    for(int a = 0; a < lineCountExpanded; a++){
        linesExpanded[a] = malloc(sizeof(char)*lineLength*2+1);
    }

    i = 0;
    j = 0;
    lineLengthExpanded = lineLength;
    /* Expand lines horizontally */
    while(i < lineLength){
        bool empty = TRUE;
        for(int a = 0; a < lineCountExpanded; a++){
            if(tempLines[a][i] != '.') {empty = FALSE; break;}
        }
        for(int a = 0; a < lineCountExpanded; a++){
            linesExpanded[a][j] = tempLines[a][i];
        }
        i++; j++;
        if(empty == FALSE) continue;
        for(int a = 0; a < lineCountExpanded; a++){
            linesExpanded[a][j] = '.';
        }
        j++; lineLengthExpanded++; 
    }

    /* Free space for temporary data */
    for(int a = 0; a < lineCount*2; a++){
        free(tempLines[a]);
    }
    free(tempLines);

    int** galaxyNumbers = malloc(sizeof(int*)*lineCountExpanded);
    i = 0;
    for(int a = 0; a < lineCountExpanded; a++){
        galaxyNumbers[a] = malloc(sizeof(int)*lineLengthExpanded);
        for(int b = 0; b < lineLengthExpanded; b++){
            if(linesExpanded[a][b] == '#') galaxyNumbers[a][b] = i++;
            else galaxyNumbers[a][b] = -1;
        }
    }

    int solution = 0;

    for(int a = 0; a < lineCountExpanded; a++){
        for(int b = 0; b < lineLengthExpanded; b++){
            for(int c = 0; c < lineCountExpanded; c++){
                for(int d = 0; d < lineLengthExpanded; d++){
                    if(galaxyNumbers[a][b] == -1) continue;
                    if(galaxyNumbers[c][d] == -1) continue;
                    int number1 = galaxyNumbers[a][b];
                    int number2 = galaxyNumbers[c][d];
                    int temp;
                    if(a >= c) temp = a-c; else temp = c-a;
                    if(b >= d) temp += b-d; else temp += d-b;
                    solution += temp;
                }
            }
        }
    }

    // for(int i = 0; i < lineCountExpanded; i++){
    //     for(int j = 0; j < lineLengthExpanded; j++){
    //         printf("%c", linesExpanded[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("Solution: %d\n", solution/2);

    timerEnd;

    return 0;
}