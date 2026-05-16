#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "casino.h"

//function prototypes
void display(char enter);
void drawCards(int *card1, int *card2, int *suit1, int *suit2);
void displayCards(char ranks[][3], char suits[][2], 
                  int card1, int card2, 
                  int suit1, int suit2);
int cardValue(int card);
int getScore(int value1, int value2);
void determineWinner(int playerScore, int dealerScore);


void playCloudNine(User *user){
    char ranks[13][3] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    char suits[4][2] = {"H", "D", "C", "S"};
    int bet = 0;
    char playAgain = 'Y';
    char enter = ' ';

    srand(time(0));

    display(enter);

    do{
        //player card
        int playerCard1, playerCard2;
        int playerSuit1, playerSuit2;

        //dealer card
        int dealerCard1, dealerCard2;
        int dealerSuit1, dealerSuit2;
        
        //drawing cards
        drawCards(&playerCard1, &playerCard2, &playerSuit1, &playerSuit2);
        drawCards(&dealerCard1, &dealerCard2, &dealerSuit1, &dealerSuit2);

        //displaying cards of the player
        printf("++++++ P L A Y E R ++++++\n");
        displayCards(ranks, suits, playerCard1, playerCard2, playerSuit1, playerSuit2);
        printf("++++++ D E A L E R ++++++\n");
        displayCards(ranks, suits, dealerCard1, dealerCard2, dealerSuit1, dealerSuit2);

        //converting the index to its value
        //for player
        int playerValue1 = cardValue(playerCard1);
        int playerValue2 = cardValue(playerCard2);

        //for dealer
        int dealerValue1 = cardValue(dealerCard1);
        int dealerValue2 = cardValue(dealerCard2);

        //get the distance
        int playerScore = getScore(playerValue1, playerValue2);
        int dealerScore = getScore(dealerValue1, dealerValue2);

        determineWinner(playerScore, dealerScore);

        printf("Do you want to play again?");
        scanf(" %c", &playAgain);
    }while(playAgain == 'Y' || playAgain == 'y');
    
}

void display(char enter){
    printf("=====================================\n");
    printf("        $$$  L U C K Y   9  $$$      \n");
    printf("=====================================\n");
    printf("        +++  CASINO TABLE  +++\n");
    printf("          PLAYER  vs  DEALER\n");
    printf("=====================================\n");
    printf("           BET - DRAW - WIN\n");
    printf("=====================================\n");

    printf("Press ENTER to play: ");
    scanf("%c", &enter);

    if(enter == '\n'){
        printf("RULES OF THE TABLE:\n");
        printf("\tEach player receives 2 mystery cards!\n");
        printf("\tAim for the closest score to 9!\n");
        printf("\tCard values: A = 1, 2-9 = face value; 10, J, Q, K = 0 (wild zeros!)\n");
        printf("\tHighest score takes the crown! Ties? The house calls it a DRAW!\n");
    }
}

void drawCards(int *card1, int *card2, int *suit1, int *suit2){
    do{
        *card1 = rand() % 13;
        *card2 = rand() % 13;
        *suit1 = rand() % 4;
        *suit2 = rand() % 4;
    }while((*card1 == *card2) && (*suit1 == *suit2));
}

void displayCards(char ranks[][3], char suits[][2], int card1, int card2, int suit1, int suit2){
    printf("%s%s\n", ranks[card1], suits[suit1]);
    printf("%s%s\n", ranks[card2], suits[suit2]);
}

int cardValue(int card){
    return (card == 0) ? 1 : (card >= 9 ? 0 : card + 1);
}

int getScore(int value1, int value2){
    return abs(9 - ((value1 + value2) % 10));
}

void determineWinner(int playerScore, int dealerScore){
    if(playerScore < dealerScore){
            printf("\n====================\n");
            printf("   PLAYER WINS! \n");
            printf("   YOU HIT LUCKY 9\n");
            printf("====================\n");
    }
    else if(dealerScore < playerScore){
        printf("\n====================\n");
        printf("    DEALER WINS \n");
        printf("   HOUSE TAKES IT!\n");
        printf("====================\n");
    }
    else{
        printf("\n====================\n");
        printf("       DRAW \n");
        printf(" BETTER LUCK NEXT TIME \n");
        printf("====================\n");
    }
}