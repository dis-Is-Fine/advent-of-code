#include "../../utils.h"

typedef struct Game {
    int id;
    int red;
    int green;
    int blue;
} Game;

#define maxRed 12
#define maxGreen 13
#define maxBlue 14

void handleGame(char* gameString);
void handleDraw(char* drawString, Game* game);

int sum;

int main(int argc, char *argv[]) {

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

    size_t size = 1024;

    char *gameString = malloc(size);
    sum = 0;

    /* For each line (game) */
    while(getline(&gameString, &size, fd) != -1){
        handleGame(gameString);
    }

    free(gameString);

    printf("Solution: %d\n", sum);

    timerEnd;

    return 0;
}

void handleGame(char* gameString){
    int gameStringLength = strlen(gameString);

    Game* game = malloc(sizeof(Game));
    game->red = 0; game->green = 0; game->blue = 0;

    int gameStringIndex = 0;
    sscanf(gameString, "Game %d:", &game->id);

    int headerSize = strlen("Game :") + sizeOfNumber(game->id);

    gameStringIndex += headerSize;

    char* drawString = malloc(256);

    /* for each draw in game */
    while(gameStringIndex < gameStringLength){
        sscanf(gameString + gameStringIndex, "%[^;]", drawString);
        gameStringIndex += strlen(drawString) + 1;
        handleDraw(drawString, game);
    }

    // printf("%s -> red: %d, green: %d, blue: %d\n", gameString, game->red, game->green, game->blue);

    free(drawString);

    sum += game->red * game->green * game->blue;

}

void handleDraw(char* drawString, Game* game){
    int drawLineSize = strlen(drawString);
    int drawLineIndex = 0;

    int number;
    char* color = malloc(16);

    /* for each color in draw */
    while(drawLineIndex < drawLineSize){
        sscanf(drawString + drawLineIndex, " %d %[^,\n]", &number, color);
        drawLineIndex += sizeOfNumber(number) + strlen(color) + 3; /* 3 is here because of space in front, space between values and comma */

        if(stringEqual(color, "red") == 1) {if(number > game->red) game->red = number;}
        if(stringEqual(color, "green") == 1) {if(number > game->green) game->green = number;}
        if(stringEqual(color, "blue") == 1) {if(number > game->blue) game->blue = number;}
    }
}