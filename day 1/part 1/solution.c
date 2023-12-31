#include "../../utils.h"

int main(int argc, char *argv[]) {

    getFileName("input.txt");
    openFile;

    int sum = 0;

    char firstDigit = -1; /* First digit in the line */
    char lastDigit = -1;  /* Last digit in the line */

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
                /* always set the last number */
                lastDigit = buf[i] - '0';
            }
            i++;
        }
        int totalNumber = firstDigit*10 + lastDigit;
        // printf("current line: %s\n leftmost: %d rightmost: %d, totalNumber: %d\n", buf, firstDigit, lastDigit, totalNumber);
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