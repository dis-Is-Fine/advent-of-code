#include "../../utils.h"

int searchForSymbol(int number, char* lines[], int lineCount, int x, int y);
int isSymbol(int ch);

char symbols[] = {'*', '=', '-', '$', '@', '%', '&', '#', '+', '/'};

typedef struct part {
    int id;
    int valid;
} part;

int main(int argc, char* argv[]) {

    getFileName("input.txt");
    openFile;

    timerStart;

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
            if(isDigit(ch) == 1){
                int number;
                int length;
                sscanf(lines[i]+j, "%d", &number);
                length = sizeOfNumber(number);
                if(searchForSymbol(number, lines, lineCount, j, i) == 1) {
                    sum += number;
                }
                j += sizeOfNumber(number)-1;
            }
            j++;
        } while(ch != '\n');
    }
    
    printf("Solution: %d\n", sum);

    timerEnd;

    return 0;
}

int searchForSymbol(int number, char* lines[], int lineCount, int x, int y){
    /* search on top */
    int minX = x - 1;
    int maxX = x + sizeOfNumber(number);
    int minY = y - 1;
    int maxY = y + 1;

    if (minX < 0) minX = 0;
    if (maxX > strlen(lines[x])-1) maxX = strlen(lines[x])-1;
    if (minY < 0) minY = 0;
    if (maxY > lineCount-1) maxY = lineCount - 1;

    int valid = 0;

    int symbol = 0;

    int sX = 0;
    int sY = 0;

    for (int xPos = minX ; xPos <= maxX; xPos++) {
        sX = xPos;
        if(isSymbol(lines[minY][xPos]) == 1) {valid = 1; symbol = lines[minY][xPos]; sY = minY; break;}
        if(isSymbol(lines[y][xPos]) == 1) {valid = 1; symbol = lines[y][xPos]; sY = y; break;}
        if(isSymbol(lines[maxY][xPos]) == 1) {valid = 1; symbol = lines[maxY][xPos]; sY = maxY; break;}
    }

    // if(valid == 1){
    //     printf("%d valid (found symbol %c at %d:%d)\n", number, symbol, sX+1, sY+1);
    // } else {
    //     printf("%d invalid\n", number);
    // }

    return valid;
}

int isSymbol(int ch){
    int size = sizeof(symbols);
    for(int i = 0; i <= size; i++){
        if(ch == symbols[i]) return 1;
    }
    return 0;
}