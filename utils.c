#include "utils.h"

int isDigit(int ch){
    if(ch >= '0' && ch <= '9') {
        return TRUE;
    }
    return FALSE;
}

int sizeOfNumber(int number) {
    int i = 1;
    if(number < 0){
        number *= -1;
        i++;
    }
    while(number >= 10){
        number = number / 10;
        i++;
    }
    return i;
}

int sizeOfLong(long int number){
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

int stringEqual(char* str1, char* str2){
    int size = strlen(str1);
    if(size != strlen(str2)) return 0;
    for(int i = 0; i < size; i++){
        if(str1[i] != str2[i]) return 0;
    }
    return 1;
}

/* Returns first index of value in array, else returns -1 */
int intBelongsToArray(int value, int values[], int size){
    for(int i = 0; i < size; i++){
        if(value == values[i]) return i;
    }
    return -1;
}

int largestInIntArray(int values[], int size){
    int largest = 0;
    for(int i = 0; i < size; i++){
        if(values[i] > largest) largest = values[i];
    }
    return largest;
}
