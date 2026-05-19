#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "casino.h"

#define DECK_SIZE 52

//Card Struct
typedef struct {
    char suit[10];
    int value;
    char color[6];
} Card;

Card deck[DECK_SIZE];
int deckIndex = 0;

//Create Deck
void initializeDeck() {
    char *suits[] = {"Hearts","Diamonds","Clubs","Spades"};
    int index = 0;

    for(int s=0; s<4; s++) {
        for(int v=1; v<=13; v++) {

            //Copy suit name into card
            strcpy(deck[index].suit, suits[s]);
            deck[index].value = v;

            if(s==0 || s==1)
                strcpy(deck[index].color,"Red");
            else
                strcpy(deck[index].color,"Black");
            index++;
        }
    }
}

//Shuffling the Deck
void shuffleDeck() {
    for(int i=0;i<DECK_SIZE;i++){
        int r = rand()%DECK_SIZE; //Random Index
        //Swap Cards
        Card temp = deck[i];
        deck[i] = deck[r];
        deck[r] = temp;
    }
    deckIndex = 0;
}

//Drawing a card
Card drawHighLowCard() {
    return deck[deckIndex++];
}

//Converts card no. into readable name
char* valueName(int v){
    static char name[6];

    switch(v){
        case 1: return "Ace";
        case 11: return "Jack";
        case 12: return "Queen";
        case 13: return "King";
        default:
            sprintf(name,"%d",v);
            return name;
    }
}

//--------GAME ROUNDS---------//

//Guesses Color (Red/Black)
void redBlackRound(Card first, int *reward, int bet){
    char guess[10];

    printf("\n%sRed%s or %sBlack%s? ", BRED, RESET, BBLK, RESET);
    scanf("%s",guess);

    if(strcasecmp(guess,first.color)==0){
        *reward += bet;
        printf("%sNice Guess! You're Correct!%s\n", GRN, RESET);
    }
    else{
        *reward -= bet/2;
        printf("%sWrong! Nice try.%s\n", RED, RESET);
    }
}

//Guesses Tier (High/Low)
Card highLowRound(Card prev, int *reward, int bet){
    char guess[10];
    Card next = drawHighLowCard();

    printf("\n%sHigher%s or %sLower%s? ", BBLU, RESET, BYEL, RESET);
    scanf("%s",guess);

    if( (strcasecmp(guess,"Higher")==0 && next.value>prev.value) ||
        (strcasecmp(guess,"Lower")==0 && next.value<prev.value) )
    {
        *reward += bet;
        printf("%sNice! You're Correct!%s\n", GRN, RESET);
    }
    else{
        *reward -= bet/2;
        printf("%sWrong! Nice try.%s\n", RED, RESET);
    }
    printf("\n%sCard: %s of %s\n%s",
           MAG, valueName(next.value), next.suit, RESET);
    return next;
}

//Guesses Bound (In/Out)
Card insideOutsideRound(Card c1, Card c2, int *reward, int bet){
    char guess[15];
    Card third = drawHighLowCard();

    int min = c1.value<c2.value?c1.value:c2.value;
    int max = c1.value>c2.value?c1.value:c2.value;

    printf("\n%sInside%s or %sOutside?%s ", BBLU, RESET, BRED, RESET);
    scanf("%s",guess);

    int inside = (third.value>min && third.value<max);

    if( (strcasecmp(guess,"Inside")==0 && inside) ||
        (strcasecmp(guess,"Outside")==0 && !inside))
    {
        *reward += bet;
        printf("%sNice Guess! You're Correct!%s\n", GRN, RESET);
    }
    else{
        *reward -= bet/2;
        printf("%sWrong! Nice try.%s\n", RED, RESET);
    }
    printf("\n%sCard: %s of %s%s\n",
           MAG, valueName(third.value), third.suit, RESET);

    return third;
}

//Twist
void doubleOrNothingRound(int *reward){
    int choice;

    printf("\n%sDouble or Nothing?%s\n1. %sYes%s\n2. %sNo%s\n>> ", MAG, RESET, GRN, RESET, RED, RESET);
    scanf("%d",&choice);

    if(choice == 1){

        int guess;
        Card final = drawHighLowCard();

        printf("%sGuess number (1-13): %s", CYN, RESET);
        scanf("%d",&guess);

        if(guess==final.value){
            *reward *=2;
            printf("%sNice Guess! Your reward is%s %sDOUBLED!%s\n", YEL, RESET, BGRN, RESET);
        }
        else{
            *reward = 0;
            printf("%sBad luck! You Lost everything!%s\n", BRED, RESET);
        }
    }
    else if(choice == 2){
        *reward = 0;
    }
    else{
        printf("%sInvalid Input. Choose from the choices.%s\n", RED, RESET);
    }
}

void playHighLow(User *user){
    int bet;
    char again[10];

    do{
        initializeDeck();
        shuffleDeck();

        printf(BCYN BOLD);
        printf("\n=====================================\n");
        printf("      $$$  HIGHER or LOWER $$$       \n");
        printf("=====================================\n");
        printf(RESET);  
        printf("Balance: %s%d%s\n", YEL, user->balance, RESET);

        if (user->balance <= 0) {
        printf("\n%sYou are out of money! Go back to the main menu to deposit or reset.%s\n", RED, RESET);
        return; // Kicks playere
        }

        while(1) {
        printf("Enter bet: ");
        scanf("%d", &bet);

            if(bet <= 0 || bet > user->balance){
            printf("%sInvalid bet. Please enter a valid amount.%s\n\n", RED, RESET);
            } else {
            break;
            }
        }

        user->balance -= bet;
        int reward = bet;

        Card first = drawHighLowCard();
        printf("\n%sFirst Card: %s of %s\n%s",
               BLU, valueName(first.value),
               first.suit ,RESET);
        redBlackRound(first,&reward,bet);

        Card second = highLowRound(first,&reward,bet);
        insideOutsideRound(first,second, &reward,bet);

        doubleOrNothingRound(&reward);
        
        if(reward<0) reward=0; //Prevent negative reward
        user->balance += reward;

        if(reward>bet){
            user->highlow_wins++;
            user->total_wins++;
        }

        printf("\n%sReward:%s %d\n", BOLD, RESET, reward);
        printf("%sNew Balance:%s %d\n",BWHT, RESET, user->balance);

        saveUser(user);

        printf("\n%sPlay High-Low again?%s (yes/no): ", BGRN, RESET);
        scanf("%s",again);

    }while(strcasecmp(again,"yes")==0);
}