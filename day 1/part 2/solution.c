#include "../../utils.h"

int main(int argc, char *argv[]) {
    
    getFileName("input.txt");
    openFile;

    /* String lookup table for each number */
    char* numbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    int sum = 0;

    char firstDigit = -1; /* First digit in the line */
    char lastDigit = -1;  /* Last tdigit in the line */

    timerStart;

    char *buf = malloc(300);
    
    while(fscanf(fd, "%s\n", buf) != EOF) {
        int i = 0;
        /* for each character in the line */
        while(buf[i] != 0){
            /* if the character is a digit */
            if(buf[i] >= '0' && buf[i] <= '9') {
                /* if the first number is not set, set the first number */
                if(firstDigit == -1){
                    firstDigit = buf[i] - '0';
                }
                /* set the last number */
                lastDigit = buf[i] - '0';
            }
            /* if the character is not a digit */
            for(int j = 0; j < 10; j++) {
                int size = strlen(numbers[j]);
                int k = 0;
                /* j = number string selector; k = character in string */
                while(k < size){
                    if(buf[i+k] != numbers[j][k]) break;
                    k++;
                }
                /* if string matches*/
                if(k == size){
                    if(firstDigit == -1){
                        firstDigit = j;
                    }
                    lastDigit = j;
                    i++;
                    break;
                }
            }
            i++;
        }
        int totalNumber = firstDigit*10 + lastDigit;
        // printf("current line: %s\nleftmost: %d rightmost: %d, totalNumber: %d\n", buf, firstDigit, lastDigit, totalNumber);
        fflush(stdout);
        sum += totalNumber;
        firstDigit = -1;
        lastDigit = -1;
        memset(buf, 0, 300);
    }

    printf("Solution: %d\n", sum);

    free(buf);

    timerEnd;

    return 0;
}