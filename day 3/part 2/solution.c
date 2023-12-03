#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int getLineCount(FILE* fd);
int isDigit(int ch);
int sizeOfNumber(int number);
int searchForNumbers(char* lines[], int lineCount, int x, int y);
int checkChar(char* lines[], int x, int y);

typedef struct part {
    int id;
    int valid;
} part;

int main(int argc, char* argv[]) {

    // if(argc != 2) {
    //     printf("Usage: %s <input_file>\n", argv[0]);
    //     return -1;
    // }

    FILE* fd = fopen("input.txt", "r");

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
        int ch;
        int lineLength = strlen(lines[i]);
        for(int j = 0; j < lineLength; j++){
            ch = lines[i][j];
            if(ch == '*'){
                sum += searchForNumbers(lines, lineCount, j, i);
            }
        }
    }
    
    printf("%d\n", sum);

    return 0;
}

int searchForNumbers(char* lines[], int lineCount, int x, int y){
    int minX = x - 1;
    int maxX = x + 1;
    int minY = y - 1;
    int maxY = y + 1;

    if (minX < 0) minX = 0;
    if (maxX > strlen(lines[y])-1) maxX = strlen(lines[y])-1;
    if (minY < 0) minY = 0;
    if (maxY > lineCount-1) maxY = lineCount - 1;

    int numberCount = 0;
    int ratio = 0;

    printf("found %c at %d:%d, numbers: ", lines[y][x], x+1, y+1);

    if(x == 92 && y == 11){
        x = 98;
    }

    int previousNumber = 0;

    for (int yPos = minY ; yPos <= maxY; yPos++) {
        for(int xPos = minX; xPos <= maxX; xPos++){
            int number = checkChar(lines, xPos, yPos);
            if(number < 0 || number == previousNumber) {continue;}
            previousNumber = number;
            numberCount++;
            printf("%d ", number);
            if(ratio == 0){
                ratio = number;
            } else {
                ratio = number * ratio;
            }
        }
    }

    if(numberCount == 2) {
        printf("| two numbers found\n");
        return ratio;
    }
    
    printf("| %d numbers found\n", numberCount);
    return 0;
}

int checkChar(char* lines[], int x, int y){
    char ch = lines[y][x];
    if(x < 0) return -1; 
    if(isDigit(ch) == 1) {
        int number = checkChar(lines, x-1, y);
        if(number == -1) {
            int number;
            sscanf(lines[y]+x, "%d", &number);
            return number;
        } else {
            return number;
        }
    }
    return -1;
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
    int lineCount = 1;
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
