#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int getLineCount(FILE* fd);
int isDigit(int ch);
int sizeOfNumber(int number);

typedef struct part {
    int id;
    int valid;
} part;

int main(int argc, char* argv[]) {

    if(argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return -1;
    }

    FILE* fd = fopen(argv[1], "r");

    if (fd == NULL) {
        printf("File not found\n");
        return -1;
    }

    int lineCount = getLineCount(fd);

    char* lines[lineCount];

    size_t size = 1024;

    char* lineBuf = malloc(size);
    int i = 0;
    while(getline(&lineBuf, &size, fd) != -1){
        lines[i++] = lineBuf;
        lineBuf = malloc(1024);
    }
    free(lineBuf);

    int sum = 0;

    for(int i = 0; i < lineCount; i++){
        int j = 0;
        int ch;
        do {
            ch = lines[i][j];
            if(ch = '*'){
                sum += searchForNumbers(lines, lineCount, j, i);
            }
            j++;
        } while(ch != '\n');
    }
    
    printf("%d\n", sum);

    return 0;
}

int searchForNumbers(char* lines[], int lineCount, int x, int y){
    /* search on top */
    int minX = x - 1;
    int maxX = x + 1;
    int minY = y - 1;
    int maxY = y + 1;

    if (minX < 0) minX = 0;
    if (maxX > strlen(lines[x])-1) maxX = strlen(lines[x])-1;
    if (minY < 0) minY = 0;
    if (maxY > lineCount-1) maxY = lineCount - 1;


    for (int xPos = minX ; xPos <= maxX; xPos++) {

    }
}

int isDigit(int ch){
    if(ch >= '0' && ch <= '9') {
        return 1;
    }
    return 0;
}

int sizeOfNumber(int number) {
    int i = 1;
    while(number >= 10){
        number = number / 10;
        i++;
    }
    return i;
}

int getLineCount(FILE* fd){
    int ch;
    int lineCount = 0;
    int position = ftell(fd);

    do {
        ch = fgetc(fd);
        if(ch == '\n'){
            lineCount++;
        }
    } while(ch != EOF);

    fseek(fd, position, SEEK_SET);
    return lineCount;
}