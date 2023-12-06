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

    size_t size = 128;

    char* line = malloc(size);
    long int* numbers = malloc(sizeof(int*));

    int linePosition = 0;
    while(getline(&line, &size, fd) != -1){
        int i = 0;
        long int lineNumber = 0;

        while(line[i] != '\n' && line[i] != '\0'){
            if(isDigit(line[i])){
                long int number = 0;
                sscanf(line+i, "%ld", &number);
                i += sizeOfNumber(number);
                lineNumber *= powl(10, sizeOfNumber(number));
                lineNumber += number;
            } else {
                i++;
            }
        }
        numbers[linePosition++] = lineNumber;
    }

    long int time = numbers[0];
    long int record = numbers[1];

    /* quadratic formula is y = -(x^2) + (x*time) - record */
    /* a = -1; b = time; c = -record */
    /* formula for delta is Δ = (time^2) - (4*record) */

    long double deltaRoot = sqrtl(powl(time, 2) - (4 * record));
    long double solutionStart = (((-time) + deltaRoot)/-2); 
    long double solutionEnd = (((-time) - deltaRoot)/-2);

    solutionStart = (ceill(solutionStart) == solutionStart) ? ceill(solutionStart)+1 : ceill(solutionStart);
    solutionEnd = (ceill(solutionEnd) == solutionEnd) ? ceill(solutionEnd)-1 : (long int) solutionEnd;

    long int solution =  solutionEnd - solutionStart+1;

    printf("Solution: %ld\n", solution);

    return 0;
}