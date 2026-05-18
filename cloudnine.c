#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "casino.h"

//function prototypes
void display();
void drawCards(int *card1, int *card2, int *suit1, int *suit2);
void displayCards(char ranks[][3], char suits[][2],
                  int card1, int card2,
                  int suit1, int suit2);
int cardValue(int card);
int getScore(int value1, int value2);
void determineWinner(User *user, int bet, int playerScore, int dealerScore);

//simulates typewriter effect in in printing statements
void typeText(const char *text, int delay){
    while(*text){       //loop through each character
        printf("%c", *text);
        fflush(stdout);     //immediate output
        usleep(delay);      //pause for delay
        text++;
    }
}

//animation for shuffling cards
void loadingAnimation(){

    printf(BYEL "\nShuffling cards");   //yellow
    fflush(stdout);

    for(int i = 0; i < 6; i++){     //loop 6 times for animation dots
        printf(".");
        fflush(stdout);
        usleep(500000);     //wait 0.5 seconds before next dor
    }

    printf(RESET "\n");     //reset color 
    usleep(500000);     //small pause after animation ends
}

//main function
void playCloudNine(User *user){
    //card rank labels
    char ranks[13][3] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    //suit labels
    char suits[4][2] = {"H","D","C","S"};
    //variable to control replay loop
    char playAgain = 'Y';

    srand(time(0));     //seed ramdom generator for card drawing

    display();  //shows the game intro 

    do{

        CLRSCR();   //clear screen
        int bet;
        printf("Balance: %d\n", user->balance);     //show current player balance
        printf("Enter bet: ");
        scanf("%d", &bet);      //get bet from the user

        //validating for the bet (must be positive and not exceed balance)
        if (bet <= 0 || bet > user->balance) {
            printf("Invalid bet!\n");
            usleep(800000);     //delay
            continue;       //restart loop if invalid
        }

        //variables for players card, players suit
        int playerCard1, playerCard2;
        int playerSuit1, playerSuit2;

        //variables for dealers card, dealers suit
        int dealerCard1, dealerCard2;
        int dealerSuit1, dealerSuit2;

        //show shuffle animation
        loadingAnimation();

        //generate player cards
        drawCards(&playerCard1, &playerCard2, &playerSuit1, &playerSuit2);
        //generate dealer cards
        drawCards(&dealerCard1, &dealerCard2, &dealerSuit1, &dealerSuit2);

        //display cards
        printf(BGRN "\n++++++ PLAYER ++++++\n" RESET);
        displayCards(ranks, suits, playerCard1, playerCard2, playerSuit1, playerSuit2);
        printf(BRED "\n++++++ DEALER ++++++\n" RESET);
        displayCards(ranks, suits, dealerCard1, dealerCard2, dealerSuit1, dealerSuit2);

        //conversion of cards to a numerical value
        int playerValue1 = cardValue(playerCard1);
        int playerValue2 = cardValue(playerCard2);
        int dealerValue1 = cardValue(dealerCard1);
        int dealerValue2 = cardValue(dealerCard2);

        //compute the player and dealer score
        int playerScore = getScore(playerValue1, playerValue2);
        int dealerScore = getScore(dealerValue1, dealerValue2);

        printf(BYEL "\nPLAYER SCORE: %d\n" RESET, playerScore);
        printf(BLU "DEALER SCORE: %d\n" RESET, dealerScore);

        //printing results with animation
        printf(MAG "\nCalculating result");
        fflush(stdout);

        for(int i = 0; i < 4; i++){
            printf(".");
            fflush(stdout);
            usleep(600000);
        }

        printf("\n");
        usleep(500000);

        //show the winner and update the balance
        determineWinner(user, bet, playerScore, dealerScore);

        //ask if the player wants to play again
        printf(BYEL "\nPlay again? (Y/N): " RESET);
        scanf(" %c", &playAgain);

    }while(playAgain == 'Y' || playAgain == 'y');
    
    //save balance and updates it to the file
    saveUser(user);
}


void display(){

    CLRSCR();       //clear screen

    //printing of welcome text
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

    //prompt user to start
    printf(BGRN "\nPress ENTER to play..." RESET);

    getchar();   // clears leftover input
    getchar();   // waits for real ENTER

    CLRSCR();

    //printing of rules with animation and delay 
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

//drawing of cards
void drawCards(int *card1, int *card2, int *suit1, int *suit2){

    do{
        *card1 = rand() % 13;       // generate random card (0–12)
        *card2 = rand() % 13;
        *suit1 = rand() % 4;        // generate random suit (0–3)
        *suit2 = rand() % 4;

        //avoid exact duplicate card + suited pair
    }while((*card1 == *card2) && (*suit1 == *suit2));
}

//displaying of cards
void displayCards(char ranks[][3], char suits[][2],
                  int card1, int card2,
                  int suit1, int suit2){

    printf(BYEL "\nDrawing card");      //animation starts
    fflush(stdout);

    //animation for dots
    for(int i = 0; i < 4; i++){
        printf(".");
        fflush(stdout);
        usleep(300000);
    }

    printf("\n");
    usleep(500000);

    //show first card
    printf(BRED "%s%s\n" RESET, ranks[card1], suits[suit1]);
    usleep(800000);
    //show second card
    printf(BLU "%s%s\n" RESET, ranks[card2], suits[suit2]);
    usleep(600000);

    printf("\n");
}

int cardValue(int card){
    //assigning of values
    if(card == 0) return 1;        // A
    if(card >= 10) return 0;       // J Q K
    if(card == 9) return 0;        // 10
    return card + 1;               // 2–9
}

//converting the card into a numericall value
int getScore(int value1, int value2){
    return (value1 + value2) % 10;
}

//determine winner
void determineWinner(User *user, int bet, int playerScore, int dealerScore){
    if (playerScore > dealerScore) {
        printf(BGRN "\nPLAYER WINS!\nYOU HIT LUCKY 9\n" RESET);

        user->balance += bet;       //reward bet to balance
        user->total_wins++;     //increment win counter
    }
    else if (dealerScore > playerScore) {
        printf(BRED "\nDEALER WINS!\nHOUSE TAKES IT!\n" RESET);

        user->balance -= bet;       //deduct bet from balance
    }
    else {
        printf(BYEL "\nDRAW!\nBET RETURNED\n" RESET);
        //no balance change
    }
}