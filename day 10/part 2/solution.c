#define DEV_MODE
#include "../../utils.h"

char** lines;
bool** pathLocations;
int lineCount;
int lineLength;
int startX;
int startY;

#define DIR_UP 0
#define DIR_RIGHT 1
#define DIR_DOWN 2
#define DIR_LEFT 3

int checkValidPipe(char pipe, int direction);
char getNextChar(int currentX, int currentY, int direction);
void setCurrentPos(int* currentX, int* currentY, int direction);

int main(int argc, char* argv[]){
   getFileName("input.txt");
   openFile;

   timerStart;

   lineCount = getLineCount(fd);
   
   size_t size = 512;
   lines = malloc(sizeof(char*)*lineCount);
   pathLocations = malloc(sizeof(char*)*lineCount);

   for(int i = 0; i < lineCount; i++){
      lines[i] = malloc(size);
      pathLocations[i] = calloc(size, sizeof(bool));
      if(getline(&lines[i], &size, fd) == -1) break;
      int j = 0;
      while(lines[i][j] != '\n'){
         if(lines[i][j] == 'S'){
            startX = j; startY = i;
	      }
	      j++;
      }
   }

   lineLength = 0;
   while(lines[0][lineLength] != '\n'){
      lineLength++;
   }

   int currentX = startX;
   int currentY = startY;
   pathLocations[startY][startX] = TRUE;
   int direction;
   /* Check for initial direction */
   for(int i = 0; i < 4; i++){
      char nextChar = getNextChar(startX, startY, i);
      if(nextChar == -1) continue;
      direction = checkValidPipe(nextChar, i);
      if(direction == -1) continue;
      setCurrentPos(&currentX, &currentY, i);
      pathLocations[currentY][currentX] = TRUE;
      break;
   }

   int pathLength = 1;
   int maxPathLength = lineCount * lineLength;
   int previousDirection = direction;
   while(pathLength < maxPathLength){
      char nextChar = getNextChar(currentX, currentY, direction);
      if(nextChar == -1) {
         printf("Bad input data\n"); exit(-1);}
      if(nextChar == 'S') {pathLength++; break;}
      direction = checkValidPipe(nextChar, direction);
      if(direction == -1) {printf("Something's sad"); exit(-1);}
      setCurrentPos(&currentX, &currentY, previousDirection);
      pathLocations[currentY][currentX] = TRUE;
      previousDirection = direction;
      pathLength++;
   }

   // for(int i = 0; i < lineCount; i++){
   //    for(int j = 0; j < lineLength; j++){
   //          if(lines[i][j] != '-' && lines[i][j] != '|') lines[i][j] = 'C';
   //    }
   // }

   lines[startY][startX] = '|';
   if(checkValidPipe(getNextChar(startX, startY, DIR_UP), DIR_UP) != -1){
      if(checkValidPipe(getNextChar(startX, startY, DIR_DOWN), DIR_DOWN) != -1) goto startConverted;
   }
   lines[startY][startX] = '-';
   if(checkValidPipe(getNextChar(startX, startY, DIR_LEFT), DIR_LEFT) != -1){
      if(checkValidPipe(getNextChar(startX, startY, DIR_RIGHT), DIR_RIGHT) != -1) goto startConverted;
   }
   lines[startY][startX] = 'L';
   if(checkValidPipe(getNextChar(startX, startY, DIR_RIGHT), DIR_RIGHT) != -1){
      if(checkValidPipe(getNextChar(startX, startY, DIR_UP), DIR_UP) != -1) goto startConverted;
   }
   lines[startY][startX] = 'F';
   if(checkValidPipe(getNextChar(startX, startY, DIR_RIGHT), DIR_RIGHT) != -1){
      if(checkValidPipe(getNextChar(startX, startY, DIR_DOWN), DIR_DOWN) != -1) goto startConverted;
   }
   lines[startY][startX] = 'J';
   if(checkValidPipe(getNextChar(startX, startY, DIR_LEFT), DIR_LEFT) != -1){
      if(checkValidPipe(getNextChar(startX, startY, DIR_UP), DIR_UP) != -1) goto startConverted;
   }
   lines[startY][startX] = '7';
   if(checkValidPipe(getNextChar(startX, startY, DIR_LEFT), DIR_LEFT) != -1){
      if(checkValidPipe(getNextChar(startX, startY, DIR_DOWN), DIR_DOWN) != -1) goto startConverted;
   }   
   // lines[startY][startX] = 'C';

   startConverted: int insideCount = 0;
   for(int i = 0; i < lineCount; i++){
      for(int j = 0; j < lineLength; j++){
         if(pathLocations[i][j] == TRUE) continue;
         int cutCount = 0;
         int cornerDirection;
         bool onLine = FALSE;
         for(int k = i; k >= 0; k--){
            if(pathLocations[k][j] == TRUE){
               if(lines[k][j] == 'F' || lines[k][j] == 'L') {
                  if(onLine == FALSE){
                     onLine = TRUE;
                     cornerDirection = DIR_RIGHT;
                  } else if(onLine == TRUE){
                     if(cornerDirection == DIR_LEFT){
                        cutCount++;
                     }
                     onLine = FALSE;
                  }
               } else if(lines[k][j] == 'J' || lines[k][j] == '7') {
                  if(onLine == FALSE){
                     onLine = TRUE;
                     cornerDirection = DIR_LEFT;
                  } else if(onLine == TRUE){
                     if(cornerDirection == DIR_RIGHT){
                        cutCount++;
                     }
                     onLine = FALSE;
                  }
               } else if(onLine == FALSE){
                   cutCount++;
               }
            }
         }
         if(cutCount % 2 == 1) insideCount++;
      }
   }

   for(int i = 0; i < lineCount; i++){
      for(int j = 0; j < lineLength; j++){
         if(pathLocations[i][j] == FALSE) printf("%c", lines[i][j]);
         else printf("\x1b[1;32m%c\x1b[0m", lines[i][j]);
      }
      printf("\n");
   }

   printf("Solution: %d\n", insideCount);

   timerEnd;

   return 0;
}

int checkValidPipe(char pipe, int direction){
   if(pipe == '.') return -1;

   if(pipe == '-'){
      if(direction == DIR_LEFT || direction == DIR_RIGHT) return direction;
      return -1;
   }

   if(pipe == '|'){
      if(direction == DIR_UP || direction == DIR_DOWN) return direction;
      return -1;
   }

   if(pipe == '7'){
      if(direction == DIR_RIGHT){
         return DIR_DOWN;
      } else {
         if(direction == DIR_UP){
            return DIR_LEFT;
         }
      }
      return -1;
   }

   if(pipe == 'F'){
      if(direction == DIR_UP){
         return DIR_RIGHT;
      }
      if(direction == DIR_LEFT){
         return DIR_DOWN;
      }
      return -1;
   }

   if(pipe == 'J'){
      if(direction == DIR_DOWN){
         return DIR_LEFT;
      }
      if(direction == DIR_RIGHT){
         return DIR_UP;
      }
      return -1;
   }

   if(pipe == 'L'){
      if(direction == DIR_LEFT){
         return DIR_UP;
      }
      if(direction == DIR_DOWN){
         return DIR_RIGHT;
      }
      return -1;
   }

   return -1;
}

char getNextChar(int currentX, int currentY, int direction){
   switch(direction){
      case DIR_UP: if(currentY <= 0) {return -1;} return lines[currentY-1][currentX];
      case DIR_RIGHT: if(currentX >= lineLength -1) {return -1;} return lines[currentY][currentX+1]; 
      case DIR_DOWN: if(currentY >= lineCount -1) {return -1;} return lines[currentY+1][currentX];
      case DIR_LEFT: if(currentX <= 0) {return -1;} return lines[currentY][currentX-1];
   }
}

void setCurrentPos(int* currentX, int* currentY, int direction){
   switch (direction){
      case DIR_UP: *currentY -= 1; break;
      case DIR_RIGHT: *currentX += 1; break;
      case DIR_DOWN: *currentY += 1; break;
      case DIR_LEFT: *currentX -= 1; break;
   }
}