#include "../../utils.h"

#define TYPE_HIGH 0
#define TYPE_ONE_PAIR 1
#define TYPE_TWO_PAIR 2
#define TYPE_THREE_OF_KIND 3
#define TYPE_FULL_HOUSE 4
#define TYPE_FOUR_OF_KIND 5
#define TYPE_FIVE_OF_KIND 6

#define CARD_T 10
#define CARD_J 11
#define CARD_Q 12
#define CARD_K 13
#define CARD_A 14

typedef struct Card {
    char chars[5];
    int numbers[5];
    int bet;
    int rank;
    int type;
} Card;

void assignNumbers(Card* card);
void assignType(Card* card);
void assignRanks(Card** cards, int size);
int charToNumber(char ch);

int main(int argc, char* argv[]){
    
    // if(argc != 2) {
    //     printf("Usage: %s <input_file>\n", argv[0]);
    //     return -1;
    // }

    FILE* fd = fopen("example.txt", "r");

    if (fd == NULL) {
        printf("File not found\n");
        return -1;
    }

    timerStart;

    size_t size = 32;
    char* lineBuf = malloc(size);

    Card** cards = malloc(sizeof(Card*)*getLineCount(fd));

    int i = 0;
    while(getline(&lineBuf, &size, fd) != -1){
        cards[i] = malloc(sizeof(Card));
        sscanf(lineBuf, "%5c %d", (char *)&cards[i]->chars, &cards[i]->bet);
        assignNumbers(cards[i]);
        assignType(cards[i]);
        i++;
    }

    assignRanks(cards, i);

    for(int i = 0; i < sizeof(cards)/sizeof(Card); i++){
        free(cards[i]);
    }

    free(cards);
    
    timerEnd;

    return 0;
}

void assignNumbers(Card* card){
    for(int i = 0; i < 5; i++){
        if(isDigit(card->chars[i])){
            card->numbers[i] = card->chars[i]-'0';
        } else {
            card->numbers[i] = charToNumber(card->chars[i]);
        }
    }
}

void assignType(Card* card){
    int instances[2][5] = {0};
    int numberCount = 0;
    for(int i = 0; i < 5; i++){
        int index = intBelongsToArray(card->numbers[i], instances[0], numberCount);
        if(index == -1){
            instances[0][numberCount] = card->numbers[i];
            instances[1][numberCount++] = 1;
            continue;
        }
        instances[1][index]++;
    }

    int largest = largestInIntArray(instances[1], numberCount);
    /* There is only one number repeated 5 times */
    if(instances[1][0] == 5){card->type = TYPE_FIVE_OF_KIND; return;}

    /* There are two numbers one of which is repeated 4 times */
    if(largest == 4){card->type = TYPE_FOUR_OF_KIND; return;}

    /* There are two numbers, one of which is repeated three times so the other one must be repeated 2 times */
    if(largest == 3 && numberCount == 2){card->type = TYPE_FULL_HOUSE; return;}

    /* There are three numbers, one of which is repeated three times */
    if(largest == 3 && numberCount == 3){card->type = TYPE_THREE_OF_KIND; return;}

    /* There are three numbers, one of which is repeated 2 times
       so one of other numbers must also be repeated 2 times and other one appears once */
    if(largest == 2 && numberCount == 3){card->type = TYPE_TWO_PAIR; return;}

    /* There are four numbers, one of which is repeated 2 times so other numbers appear once */
    if(largest == 2 && numberCount == 4){card->type = TYPE_ONE_PAIR; return;}

    /* Else all numbers are different */
    card->type = TYPE_HIGH; return;
}

void assignRanks(Card** cards, int size){
    Card** cardsByRank[7];
    for(int i = 0; i < 7; i++){
        cardsByRank[i] = malloc(sizeof(Card*)*128);
        cardsByRank[i][0] = calloc(1, sizeof(Card));
    }

    int sizeOfArray[7] = {0};

    for(int rank = 0; rank < 7; rank++){
        /* First put every card in respective rank array */
        for(int i = 0; i < size; i++){
            if(cards[i]->type != rank) continue;
            cardsByRank[rank][sizeOfArray[rank]] = cards[i];
            sizeOfArray[rank]++;
        }

        for(int i = 0; i < )
    }
}

int charToNumber(char ch){
    switch(ch){
        case 'T': return CARD_T;
        case 'J': return CARD_J;
        case 'Q': return CARD_Q;
        case 'K': return CARD_K;
        case 'A': return CARD_A;
        default: return 0;
    }
}