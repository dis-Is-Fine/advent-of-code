#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    if(argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return -1;
    }

    char* numbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    int sum = 0;
    char first_num = -1;
    char last_num = -1;

    FILE *fd = fopen(argv[1], "r");

    if(fd == NULL) {
        printf("File not found\n");
        return -1;
    }

    char *buf = malloc(300);
    
    while(fscanf(fd, "%s\n", buf) != EOF) {
        int i = 0;
        /* for each character in the line */
        while(buf[i] != 0){
            /* if the character is a digit */
            if(buf[i] >= '0' && buf[i] <= '9') {
                /* if the first number is not set */
                if(first_num == -1){
                    /* set the first number */
                    first_num = buf[i] - '0';
                }
                /* set the last number */
                last_num = buf[i] - '0';
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
                    if(first_num == -1){
                        first_num = j;
                    }
                    last_num = j;
                    i++;
                    break;
                }
            }
            i++;
        }
        int total = first_num*10 + last_num;
        // printf("current line: %s\nleftmost: %d rightmost: %d, total: %d\n", buf, first_num, last_num, total);
        fflush(stdout);
        sum += total;
        first_num = -1;
        last_num = -1;
        memset(buf, 0, 300);
    }

    printf("Solution: %d\n", sum);

    free(buf);

    return 0;
}