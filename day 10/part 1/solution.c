#define DEV_MODE
#include "../../utils.h"

char** lines;
int lineCount;
int startX;
int startY;

#define DIR_UP 0
#define DIR_RIGHT 1
#define DIR_DOWN 2
#define DIR_LEFT 3

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

   int currentX = startX;
   int currentY = startY;
   int direction;
   /* Check for initial direction */


   timerEnd;

   return 0;
}

int checkValidPipe(char currentPipe, char nextPipe, int direction){
   
}
