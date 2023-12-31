#include "../../utils.h"
#include <math.h>

#define numberBufSize 50

typedef struct Card {
    int id;
    int winning[numberBufSize];
    int winningCount;
    int numbers[numberBufSize];
    int numberCount;
    int matches;
    int points;
} Card;

int handleGame(char* gameString);
void handleCard(char* winningString, char* numbersString, Card* card);
int checkMatching(Card* card, int number);

int main(int argc, char *argv[]) {

    getFileName("input.txt");
    openFile;

    timerStart;

    int sum = 0;

    size_t size = 1024;

    char *cardString = malloc(size);

    /* For each line (card) */
    while(getline(&cardString, &size, fd) != -1){
        sum += handleGame(cardString);
    }

    printf("Solution: %d\n", sum);

    free(cardString);

    timerEnd;

    return 0;
}

int handleGame(char* gameString){
    Card* card = malloc(sizeof(Card));
    card->winningCount = 0;
    card->numberCount = 0;
    card->points = 0;

    int gameStringIndex = 0;
    sscanf(gameString, "Card %d:", &card->id);

    int headerSize = strlen("Card :") + sizeOfNumber(card->id);

    gameStringIndex += headerSize;

    char* winningString = malloc(256);
    char* numbersString = malloc(256);

    sscanf(gameString + gameStringIndex, "%[^|]", winningString);
    gameStringIndex += strlen(winningString) + 1;
    sscanf(gameString + gameStringIndex, "%[^\n]", numbersString);
    handleCard(winningString+1, numbersString+1, card);

    // printf("Winning: '%s' | Numbers: '%s' | Matches: %d | Points: %d\n", winningString, numbersString, card->matches, card->points);

    free(winningString);
    free(numbersString);

    return card->points;
}

void handleCard(char* winningString, char* numbersString, Card* card){

    int winningStringLength = strlen(winningString);
    int numbersStringLength = strlen(numbersString);

    int stringIndex = 0;
    while(stringIndex < winningStringLength) {
        while(winningString[stringIndex] == ' ') stringIndex++;
        sscanf(winningString + stringIndex, "%d", &card->winning[card->winningCount]);
        stringIndex += sizeOfNumber(card->winning[card->winningCount++]) + 1;
    }

    stringIndex = 0;
    while(stringIndex < numbersStringLength) {
        while(numbersString[stringIndex] == ' ') stringIndex++;
        sscanf(numbersString + stringIndex, "%d", &card->numbers[card->numberCount]);
        stringIndex += sizeOfNumber(card->numbers[card->numberCount++]) + 1;
    }

    card->matches = 0;
    for(int i = 0; i < card->numberCount; i++){
        if(checkMatching(card, card->numbers[i]) == 1) card->matches++;
    }
    
    if(card->matches != 0){
        card->points = (int) pow((double) 2, (double) card->matches - 1);
    } else {
        card->points = 0;
    }
}

int checkMatching(Card* card, int number){
    for(int i = 0; i < card->winningCount; i++){
        if(card->winning[i] == number) return 1;
    }
    return 0;
}