#include "../../utils.h"

typedef struct Game {
    int id;
    int valid;
} Game;

#define maxRed 12
#define maxGreen 13
#define maxBlue 14

void handleGame(char* gameString);
int handleDraw(char* drawString);

int IDsum;

int main(int argc, char *argv[]) {

    getFileName("input.txt");
    openFile;

    timerStart;

    size_t size = 1024;

    char *gameString = malloc(size);
    IDsum = 0;

    /* For each line (game) */
    while(getline(&gameString, &size, fd) != -1){
        handleGame(gameString);
    }

    free(gameString);

    printf("Solution: %d\n", IDsum);

    timerEnd;

    return 0;
}

void handleGame(char* gameString){
    int gameStringLength = strlen(gameString);

    Game* game = malloc(sizeof(Game));
    game->valid = 1;

    int gameStringIndex = 0;
    sscanf(gameString, "Game %d:", &game->id);

    int headerSize = strlen("Game :") + sizeOfNumber(game->id);

    gameStringIndex += headerSize;

    char* drawString = malloc(256);

    /* for each draw in game */
    while(gameStringIndex < gameStringLength){
        sscanf(gameString + gameStringIndex, "%[^;]", drawString);
        gameStringIndex += strlen(drawString) + 1;
        game->valid = handleDraw(drawString);
        if(game->valid == 0) break;
    }

    // printf("%s -> valid: %d\n", gameString, game->valid);

    free(drawString);

    if(game->valid == 1) IDsum += game->id;

}

int handleDraw(char* drawString){
    int drawLineSize = strlen(drawString);
    int drawLineIndex = 0;

    int number;
    char* color = malloc(16);

    /* for each color in draw */
    while(drawLineIndex < drawLineSize){
        sscanf(drawString + drawLineIndex, " %d %[^,\n]", &number, color);
        drawLineIndex += sizeOfNumber(number) + strlen(color) + 3; /* 3 is here because of space in front, space between values and comma */

        if(stringEqual(color, "red") == 1) {if(number > maxRed) return 0;}
        if(stringEqual(color, "green") == 1) {if(number > maxGreen) return 0;}
        if(stringEqual(color, "blue") == 1) {if(number > maxBlue) return 0;}
    }

    return 1;
}