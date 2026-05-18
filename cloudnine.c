#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "casino.h"

void display();
void drawCards(int *card1, int *card2, int *suit1, int *suit2);
void displayCards(char ranks[][3], char suits[][2],
                  int card1, int card2,
                  int suit1, int suit2);
int cardValue(int card);
int getScore(int value1, int value2);
void determineWinner(User *user, int bet, int playerScore, int dealerScore);

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

    for(int i = 0; i < 6; i++){
        printf(".");
        fflush(stdout);
        usleep(500000);
    }

    printf(RESET "\n");
    usleep(500000);
}


void playCloudNine(User *user){

    char ranks[13][3] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    char suits[4][2] = {"H","D","C","S"};
    char playAgain = 'Y';

    srand(time(0));

    display();

    do{

        CLRSCR();
        int bet;
        printf("Balance: %d\n", user->balance);
        printf("Enter bet: ");
        scanf("%d", &bet);

        if (bet <= 0 || bet > user->balance) {
            printf("Invalid bet!\n");
            usleep(800000);
            continue;
        }

        int playerCard1, playerCard2;
        int playerSuit1, playerSuit2;

        int dealerCard1, dealerCard2;
        int dealerSuit1, dealerSuit2;

        loadingAnimation();

        drawCards(&playerCard1, &playerCard2, &playerSuit1, &playerSuit2);
        drawCards(&dealerCard1, &dealerCard2, &dealerSuit1, &dealerSuit2);

        printf(BGRN "\n++++++ PLAYER ++++++\n" RESET);
        displayCards(ranks, suits, playerCard1, playerCard2, playerSuit1, playerSuit2);

        printf(BRED "\n++++++ DEALER ++++++\n" RESET);
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

        for(int i = 0; i < 4; i++){
            printf(".");
            fflush(stdout);
            usleep(600000);
        }

        printf("\n");
        usleep(500000);

        determineWinner(user, bet, playerScore, dealerScore);

        printf(BYEL "\nPlay again? (Y/N): " RESET);
        scanf(" %c", &playAgain);

    }while(playAgain == 'Y' || playAgain == 'y');
    
    saveUser(user);
}



void display(){

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

    printf(BGRN "\nPress ENTER to play..." RESET);

    getchar();   // clears leftover input
    getchar();   // waits for real ENTER

    CLRSCR();

    printf(BCYN "RULES:\n\n" RESET);

    typeText("Each player gets 2 cards!\n", 50000);
    usleep(400000);

    typeText("Try to get closest to 9!\n", 50000);
    usleep(400000);

    typeText("A=1, 2-9 face value, 10/J/Q/K=0\n", 50000);
    usleep(400000);

    typeText("Closest wins!\n\n", 50000);

    printf(BMAG "Good luck gambler...\n\n" RESET);
    usleep(1000000);
}

void drawCards(int *card1, int *card2, int *suit1, int *suit2){

    do{
        *card1 = rand() % 13;
        *card2 = rand() % 13;
        *suit1 = rand() % 4;
        *suit2 = rand() % 4;

    }while((*card1 == *card2) && (*suit1 == *suit2));
}


void displayCards(char ranks[][3], char suits[][2],
                  int card1, int card2,
                  int suit1, int suit2){

    printf(BYEL "\nDrawing card");
    fflush(stdout);

    for(int i = 0; i < 4; i++){
        printf(".");
        fflush(stdout);
        usleep(300000);
    }

    printf("\n");
    usleep(500000);

    printf(BRED "%s%s\n" RESET, ranks[card1], suits[suit1]);
    usleep(800000);

    printf(BLU "%s%s\n" RESET, ranks[card2], suits[suit2]);
    usleep(600000);

    printf("\n");
}

int cardValue(int card){
    if(card == 0) return 1;        // A
    if(card >= 10) return 0;       // J Q K
    if(card == 9) return 0;        // 10
    return card + 1;               // 2–9
}

int getScore(int value1, int value2){
    return (value1 + value2) % 10;
}

// ================= WINNER =================
void determineWinner(User *user, int bet, int playerScore, int dealerScore){
    if (playerScore > dealerScore) {
        printf(BGRN "\nPLAYER WINS!\nYOU HIT LUCKY 9\n" RESET);

        user->balance += bet;
        user->total_wins++;
    }
    else if (dealerScore > playerScore) {
        printf(BRED "\nDEALER WINS!\nHOUSE TAKES IT!\n" RESET);

        user->balance -= bet;
    }
    else {
        printf(BYEL "\nDRAW!\nBET RETURNED\n" RESET);
    }
}