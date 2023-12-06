#include "../../utils.h"
#include <math.h>

int main(int argc, char* argv[]){
    
    if(argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return -1;
    }

    FILE* fd = fopen(argv[1], "r");

    if (fd == NULL) {
        printf("File not found\n");
        return -1;
    }

    timerStart;

    size_t size = 128;

    char* line = malloc(size);
    int** numbers = malloc(sizeof(int*));

    int lineNumber = 0;
    int numberPos = 0;
    while(getline(&line, &size, fd) != -1){
        int i = 0;
        numberPos = 0;
        numbers[lineNumber] = malloc(sizeof(int*));
        while(line[i] != '\n' && line[i] != '\0'){
            if(isDigit(line[i])){
                int number = 0;
                sscanf(line+i, "%d", &number);
                i += sizeOfNumber(number);
                numbers[lineNumber][numberPos++] = number;
            } else {
                i++;
            }
        }
        lineNumber++;
    }

    int solution = 1;

    for(int i = 0; i < numberPos; i++){
        int time = numbers[0][i];
        int record = numbers[1][i];

        /* quadratic formula is y = -(x^2) + (x*time) - record */
        /* a = -1; b = time; c = -record */
        /* formula for delta is Δ = (time^2) - (4*record) */

        double deltaRoot = sqrt(pow(time, 2) - (4 * record));
        double solutionStart = (((-time) + deltaRoot)/-2); 
        double solutionEnd = (((-time) - deltaRoot)/-2);

        solutionStart = (ceil(solutionStart) == solutionStart) ? ceil(solutionStart)+1 : ceil(solutionStart);
        solutionEnd = (ceil(solutionEnd) == solutionEnd) ? ceil(solutionEnd)-1 : (int) solutionEnd;

        int solutionCount =  solutionEnd - solutionStart+1;

        solution *= solutionCount;
    }

    printf("Solution: %d\n", solution);

    timerEnd;

    return 0;
}