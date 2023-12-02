#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct Game {
    int id;
    int red;
    int green;
    int blue;
    int valid;
} Game;

#define maxRed 12
#define maxGreen 13
#define maxBlue 14

int stringEqual(char* str1, char* str2);
int sizeOfNumber(int number);

int main(int argc, char *argv[]) {

    // if(argc != 2) {
    //     printf("Usage: %s <input_file>\n", argv[0]);
    //     return -1;
    // }

    FILE* fd = fopen("input.txt", "r");

    if (fd == NULL) {
        printf("File not found\n");
        return -1;
    }

    size_t size = 512;

    char *gameString = malloc(size);
    int IDsum = 0;

    /* For each line (game) */
    while(getline(&gameString, &size, fd) != -1){
        int i = 0;
        int lineSize = strlen(gameString);
        Game* game = malloc(sizeof(game));
        game->red = 0;
        game->green = 0;
        game->blue = 0;
        game->valid = 1;
        /* make sure it has Game # in beggining and assign game id to game struct*/
        sscanf(gameString, "Game %d:", &game->id);
        i += strlen("Game :") + sizeOfNumber(game->id);

        /* For each draw in game */
        for(int j = 0; j<strlen(gameString); j++){
            char* lineString = malloc(lineSize);
            memset(lineString, 0, lineSize);
            sscanf(gameString + i + j, "%[^;]", lineString); /* reading game offset by 'Game #:' header*/
            lineString[strlen(lineString)] = ';';

            int k = 0;

            /* For each cube color */
            while(k < strlen(lineString)){
                int number;
                char* color = malloc(16);
                char* ending = malloc(2);
                sscanf(lineString+k, "%d %[^,;]%[,;]", &number, color, ending);
                if(stringEqual(color, "red")) game->red = number;
                if(stringEqual(color, "green")) game->green = number;
                if(stringEqual(color, "blue")) game->blue = number;

                k = k + sizeOfNumber(number) + strlen(color) + 1 + 2;

                if(ending[0] == ';') break;
            }

            if(game->red > maxRed) { game->valid = 0; continue; }
            if(game->green > maxGreen) { game->valid = 0; continue; }
            if(game->blue > maxBlue) { game->valid = 0; continue; }
            game->valid = 1;

            j =  + k;

        }

        // printf("game: %s, valid: %d\n", lineString, game->valid);
        if(game->valid = 1) IDsum += game->id;
        free(game);

    }

    free(gameString);

    printf("%d", IDsum);

    return 0;
}

int stringEqual(char* str1, char* str2){
    int size = strlen(str1);
    if(size != strlen(str2)) return 0;
    for(int i = 0; i < size; i++){
        if(str1[i] != str2[i]) return 0;
    }
    return 1;
}

int sizeOfNumber(int number) {
    int i = 1;
    while(number >= 10){
        number = number / 10;
        i++;
    }
    return i;
}