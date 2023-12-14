#define DEV_MODE
#include "../../utils.h"

int processLine(char* line, int lineSize);
bool checkIsLineValid(char* line, int lineSize);
void numberToBinaryStr(int number, char* Buf, int minSize);
int strLenSpace(char* str);

int main(int argc, char* argv[]){
    getFileName("example.txt");
    openFile;

    timerStart;

    printf("This is still work in progress, results aren't correct\n");
    sleep(2);

    size_t size = 512;
    char* lineBuf = malloc(size);
    char* tempBuf = malloc(size);
    int length = 0;
    int index = 0;

    int solution = 0;
    while(getline(&lineBuf, &size, fd)!= -1){
        index = 0;
        for(int i = 0; i < 5; i++){
            sscanf(lineBuf, "%s", tempBuf+index);
            length = strlen(tempBuf+index);
            index += length;
            tempBuf[index++] = '?';
        }
        tempBuf[index-1] =  ' ';
        for(int i = 0; i < 5; i++){
            sscanf(lineBuf+length+1, "%s", tempBuf+index);
            index += strlen(tempBuf+index);
            tempBuf[index++] = ',';
        }
        tempBuf[index-1] = '\0';
        printf("%s\n", tempBuf);

        int temp = processLine(tempBuf, (int) strlen(tempBuf));
        printf("%d\n\n", temp);
        solution += temp;
    }

    printf("Solution: %d\n", solution);

    timerEnd;

    return 0;
}

int processLine(char* line, int lineSize){
    int lineSizeSprings = strLenSpace(line);
    int* unknownLocations = malloc(sizeof(int)*lineSizeSprings);
    int unknownLocationCount = 0;
    for(int i = 0; i < lineSizeSprings; i++){
        if(line[i] == '?') {
            unknownLocations[unknownLocationCount] = unknownLocationCount;
            unknownLocationCount++;
        }
    }
    int posibilities = 1 << unknownLocationCount;
    char* tempLine = malloc(lineSize);
    memcpy(tempLine, line, lineSize);
    char binaryNum[128];
    int validCount = 0;

    for(int i = 0; i < posibilities; i++){
        numberToBinaryStr(i, binaryNum, unknownLocationCount);
        int a = 0;
        for(int j = 0; j < lineSizeSprings; j++){
            if(tempLine[j] != '?') continue;
            tempLine[j] = (binaryNum[a] == '0') ? '.' : '#';
            a++;
        }
        if(checkIsLineValid(tempLine, lineSize)) validCount++;
        memcpy(tempLine, line, lineSize);
    }

    free(tempLine);

    // printf("%s: %d\n\n", line, validCount);

    return validCount;
}

bool checkIsLineValid(char* line, int lineSize){
    int numbers[lineSize];
    char springLine[lineSize];
    sscanf(line, "%s ", springLine);
    int index = strlen(springLine)+1;
    int maxIndex = strlen(springLine);
    int numberIndex = 0;
    while(TRUE){
        if(sscanf(line+index, "%d", &numbers[numberIndex]) != 1) break;
        index += sizeOfNumber(numbers[numberIndex++]);
        if(line[index] != ',') break;
        index++;
    }

    int maxNumberIndex = numberIndex-1;
    numberIndex = 0;
    index = 0;
    bool valid = TRUE;
    while(index < maxIndex){
        if(line[index] != '#'){index++; continue;}
        if(numberIndex > maxNumberIndex) break;
        char tempBuf[lineSize];
        sscanf(line+index, "%[#]", tempBuf);
        if((int) strlen(tempBuf) != numbers[numberIndex]) {valid = FALSE; break;}
        index += strlen(tempBuf);
        numberIndex++;
    }

    if(numberIndex-1 != maxNumberIndex) valid = FALSE;

    while(index < maxIndex){
        if(line[index] == '#') {valid = FALSE; break;}
        index++;
    }

    // if(valid) printf("\x1b[1;32m%s\x1b[0m\n", line);
    // else printf("%s\n", line);

    return valid;
}

void numberToBinaryStr(int number, char* buf, int minSize){ 
    for (int i = 0; i < minSize; i++)   
        buf[i] = (number & (int)1<<(minSize-i-1)) ? '1' : '0';
    buf[minSize]='\0';
}

int strLenSpace(char* str){
    int i = 0;
    while(str[i] != ' ') i++;
    return i;
}