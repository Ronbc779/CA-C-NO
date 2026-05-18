#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
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

// ===== ANIMATION FUNCTIONS =====
void typeText(const char *text, int delay){
    while(*text){
        printf("%c", *text);
        fflush(stdout);
        usleep(delay);
        text++;
    }
}

void loadingAnimation(){
    printf(BYEL "\nShuffling cards");
    fflush(stdout);

    for(int i = 0; i < 5; i++){
        printf(".");
        fflush(stdout);
        usleep(250000);
    }

    printf(RESET "\n");
}

// ===== MAIN GAME =====
void playCloudNine(User *user){

    char ranks[13][3] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    char suits[4][2] = {"H","D","C","S"};

    char playAgain = 'Y';
    char enter = ' ';

    srand(time(0));

    display(enter);

    do{

        CLRSCR();

        int playerCard1, playerCard2;
        int playerSuit1, playerSuit2;

        int dealerCard1, dealerCard2;
        int dealerSuit1, dealerSuit2;

        loadingAnimation();

        drawCards(&playerCard1, &playerCard2, &playerSuit1, &playerSuit2);
        drawCards(&dealerCard1, &dealerCard2, &dealerSuit1, &dealerSuit2);

        printf(BGRN "\n++++++ P L A Y E R ++++++\n" RESET);
        displayCards(ranks, suits, playerCard1, playerCard2, playerSuit1, playerSuit2);

        printf(BRED "\n++++++ D E A L E R ++++++\n" RESET);
        displayCards(ranks, suits, dealerCard1, dealerCard2, dealerSuit1, dealerSuit2);

        int playerValue1 = cardValue(playerCard1);
        int playerValue2 = cardValue(playerCard2);

        int dealerValue1 = cardValue(dealerCard1);
        int dealerValue2 = cardValue(dealerCard2);

        int playerScore = getScore(playerValue1, playerValue2);
        int dealerScore = getScore(dealerValue1, dealerValue2);

        printf(BYEL "\nPLAYER SCORE: %d\n" RESET, playerScore);
        printf(BLU "DEALER SCORE: %d\n" RESET, dealerScore);

        printf(MAG "\nCalculating result");
        fflush(stdout);

        for(int i = 0; i < 3; i++){
            printf(".");
            fflush(stdout);
            usleep(300000);
        }

        printf("\n");

        determineWinner(playerScore, dealerScore);

        printf(BYEL "\nPlay again? (Y/N): " RESET);
        scanf(" %c", &playAgain);

    }while(playAgain == 'Y' || playAgain == 'y');
}

// =====DISPLAY=====
void display(char enter){

    CLRSCR();

    printf(BRED BOLD);
    printf("=====================================\n");
    printf("        $$$  L U C K Y  9  $$$       \n");
    printf("=====================================\n");
    printf(RESET);

    printf(BYEL);
    printf("        +++  CASINO TABLE  +++\n");
    printf("          PLAYER  vs  DEALER\n");
    printf("=====================================\n");
    printf("           BET - DRAW - WIN\n");
    printf("=====================================\n");
    printf(RESET);

    printf(BGRN "Press ENTER to play: " RESET);
    scanf("%c", &enter);

    if(enter == '\n'){

        CLRSCR();

        printf(BCYN "RULES:\n\n" RESET);

        typeText("Each player gets 2 cards!\n", 20000);
        typeText("Try to get closest to 9!\n", 20000);
        typeText("A=1, 2-9 face value, 10/J/Q/K=0\n", 20000);
        typeText("Closest wins!\n\n", 20000);

        printf(BMAG "Good luck gambler...\n\n" RESET);
        usleep(800000);
    }
}

// ===== CARD DRAW =====
void drawCards(int *card1, int *card2, int *suit1, int *suit2){

    do{
        *card1 = rand() % 13;
        *card2 = rand() % 13;
        *suit1 = rand() % 4;
        *suit2 = rand() % 4;

    }while((*card1 == *card2) && (*suit1 == *suit2));
}

// ===== CARD DISPLAY WITH ANIMATION =====
void displayCards(char ranks[][3], char suits[][2],
                  int card1, int card2,
                  int suit1, int suit2){

    printf(BYEL "\nDrawing card");
    fflush(stdout);

    for(int i = 0; i < 3; i++){
        printf(".");
        fflush(stdout);
        usleep(200000);
    }

    printf("\n");

    printf(BRED "%s%s\n" RESET, ranks[card1], suits[suit1]);
    usleep(300000);

    printf(BLU "%s%s\n" RESET, ranks[card2], suits[suit2]);

    printf("\n");
}

// ===== GAME LOGIC =====
int cardValue(int card){
    return (card == 0) ? 1 : (card >= 9 ? 0 : card + 1);
}

int getScore(int value1, int value2){
    return abs(9 - ((value1 + value2) % 10));
}

// ===== WINNER =====
void determineWinner(int playerScore, int dealerScore){

    usleep(500000);

    if(playerScore < dealerScore){
        printf(BGRN "\nPLAYER WINS!\nYOU HIT LUCKY 9\n" RESET);
    }
    else if(dealerScore < playerScore){
        printf(BRED "\nDEALER WINS!\nHOUSE TAKES IT!\n" RESET);
    }
    else{
        printf(BYEL "\nDRAW!\nBETTER LUCK NEXT TIME\n" RESET);
    }
}