#include "../../utils.h"

int calculateHASH(char* sequence);

int main(int argc, char* argv[]){

    getFileName("input.txt");
    openFile;

    timerStart;

    size_t size = 65000;
    char* lineBuf = malloc(size);
    getline(&lineBuf, &size, fd);
    int lineSize = strlen(lineBuf);

    int index = 0;
    int inputIndex = 0;
    int solution = 0;
    char inputBuf[256];
    while(index < lineSize+1){
        if(lineBuf[index] != ',' && lineBuf[index] != '\0' && lineBuf[index] != '\n') {
            inputBuf[inputIndex] = lineBuf[index];
            index++;
            inputIndex++;
            continue;
        }
        inputBuf[inputIndex] = '\0';
        solution += calculateHASH(inputBuf);
        inputIndex = 0;
        index++;
    }

    printf("Solution: %d\n", solution);

    timerEnd;

    return 0;
}

int calculateHASH(char* sequence){
    int i = 0;
    int currentHash = 0;
    while(sequence[i] != '\0'){
        currentHash += (int) sequence[i];
        currentHash *= 17;
        currentHash = currentHash % 256;
        i++;
    }
    return currentHash;
}