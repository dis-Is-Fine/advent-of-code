#include "../../utils.h"

char** lines;
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
   getFileName("example.txt");
   openFile;

   timerStart;

   lineCount = getLineCount(fd);
   
   size_t size = 512;
   lines = malloc(sizeof(char*)*lineCount);

   for(int i = 0; i < lineCount; i++){
      lines[i] = malloc(size);
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
   int direction;
   /* Check for initial direction */
   for(int i = 0; i < 4; i++){
      char nextChar = getNextChar(startX, startY, i);
      if(nextChar == -1) continue;
      direction = checkValidPipe(nextChar, i);
      if(direction == -1) continue;
      setCurrentPos(&currentX, &currentY, i);
      break;
   }

   int pathLength = 1;
   int maxPathLength = lineCount * lineLength;
   int previousDirection = direction;
   while(pathLength < maxPathLength){
      char nextChar = getNextChar(currentX, currentY, direction);
      if(nextChar == -1) {printf("Bad input data\n"); exit(-1);}
      if(nextChar == 'S') {pathLength++; break;}
      direction = checkValidPipe(nextChar, direction);
      if(direction == -1) {printf("Something's sad"); exit(-1);}
      setCurrentPos(&currentX, &currentY, previousDirection);
      previousDirection = direction;
      pathLength++;
   }

   printf("Solution: %d\n", pathLength/2);


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