#include "../../utils.h"

#define numberBufSize 50

typedef struct Card {
    int id;
    int winning[numberBufSize];
    int winningCount;
    int numbers[numberBufSize];
    int numberCount;
    int matches;
    int instances;
} Card;

void handleGame(char* gameString, Card* card);
void handleCard(char* winningString, char* numbersString, Card* card);
int checkMatching(Card* card, int number);

int numberOfCards = 0;
int sum = 0;
Card** cardArray;

int main(int argc, char *argv[]) {

    getFileName("input.txt");
    openFile;

    timerStart;

    size_t size = 1024;

    char *cardString = malloc(size);

    numberOfCards = getLineCount(fd);

    cardArray = malloc(sizeof(Card)*numberOfCards);
    for(int i = 0; i < numberOfCards; i++){
        cardArray[i] = malloc(sizeof(Card));
        cardArray[i]->instances = 1;
    }

    int cardNumber = 0;
    /* For each line (card) */
    while(getline(&cardString, &size, fd) != -1){ 
        handleGame(cardString, cardArray[cardNumber++]);
    }

    for(int i = 0; i < numberOfCards; i++){
        free(cardArray[i]);
    }

    printf("Solution: %d\n", sum);

    free(cardString);
    free(cardArray);

    timerEnd;

    return 0;
}

void handleGame(char* gameString, Card* card){
    card->winningCount = 0;
    card->numberCount = 0;

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

    for(int i = 0; i < card->matches; i++){
        cardArray[card->id + i]->instances += card->instances;
    }

    // printf("Card %d | Matches: %d | Instances: %d\n", card->id, card->matches, card->instances);
    sum += card->instances;

    free(winningString);
    free(numbersString);
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
}

int checkMatching(Card* card, int number){
    for(int i = 0; i < card->winningCount; i++){
        if(card->winning[i] == number) return 1;
    }
    return 0;
}