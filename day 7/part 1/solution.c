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
void sortByValue(Card* cardsByType[], int size);
void swap(Card* a, Card* b);
int charToNumber(char ch);

int main(int argc, char* argv[]){
    
    getFileName("input.txt");
    openFile;

    timerStart;

    size_t size = 32;
    char* lineBuf = malloc(size);

    Card** cards = malloc(sizeof(Card*)*getLineCount(fd));

    int sz = 0;
    while(getline(&lineBuf, &size, fd) != -1){
        cards[sz] = malloc(sizeof(Card));
        sscanf(lineBuf, "%5c %d", (char *)&cards[sz]->chars, &cards[sz]->bet);
        assignNumbers(cards[sz]);
        assignType(cards[sz]);
        sz++;
    }

    assignRanks(cards, sz);

    int solution = 0;

    for(int i = 0; i < sz; i++){
        for(int j = 0; j < 5; j++){
            printf("%c", cards[i]->chars[j]);
        }
        printf(" %d\n", cards[i]->bet);
        solution += cards[i]->bet*cards[i]->rank;
    }

    printf("Solution: %d\n", solution);

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
    Card** cardsByType[7];

    for(int i = 0; i < 7; i++){
        cardsByType[i] = malloc(sizeof(Card*)*size);
    }

    int sizeOfArray[7] = {0};

    /* First put every card in respective type array */
    for(int type = 0; type < 7; type++){
        for(int i = 0; i < size; i++){
            cardsByType[type][i] = malloc(sizeof(Card));
            if(cards[i]->type != type) continue;
            cardsByType[type][sizeOfArray[type]] = cards[i];
            sizeOfArray[type]++;
        }
        sortByValue(cardsByType[type], sizeOfArray[type]);
    }

    int offset = 0;
    for(int type = 0; type < 7; type++){
        for(int j = 0; j < sizeOfArray[type]; j++){
            cards[offset+j] = cardsByType[type][j];
        }
        offset += sizeOfArray[type];
    }
    
    for(int i = 0; i < size; i++){
        cards[i]->rank = i+1;
    }

}

int valcmp(int a[], int b[], int size){
    for(int i = 0; i < size; i++){
        if(a[i] == b[i]) continue;
        if(a[i] > b[i]) return 1;
        return -1;
    }
    return 0;
}

void sortByValue(Card* cards[], int size){
    int s = sizeof(Card**)*size;

    for (int i=0; i<size; i++) {
        for (int j=0; j<size-1; j++) {
            if (valcmp(cards[j]->numbers, cards[j+1]->numbers, 5) > 0) {
                swap(cards[j], cards[j+1]);
            }
        }
    }
    
}

void swap(Card* a, Card* b){
    Card* temp = malloc(sizeof(Card));
    memcpy(temp, a, sizeof(Card));
    memcpy(a, b, sizeof(Card));
    memcpy(b, temp, sizeof(Card));
    free(temp);
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