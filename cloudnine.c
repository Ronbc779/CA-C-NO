#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "casino.h"

int playCloudNine(User *user){
    char ranks[13][3] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    char suits[4][2] = {"H", "D", "C", "S"};
    int bet = 0;
    char playAgain = 'Y';
    char enter = ' ';
    srand(time(0));

    printf("=====================================\n");
    printf("        $$$  L U C K Y   9  $$$      \n");
    printf("=====================================\n");
    printf("        +++ CASINO TABLE  +++\n");
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

        do{
            //player card
            int playerCard1 = (rand() % 13);
            int playerCard2 = (rand() % 13);
            int playerSuit1 = (rand() % 4);
            int playerSuit2 = (rand() % 4);

            //dealer card
            int dealerCard1 = (rand() % 13);
            int dealerCard2 = (rand() % 13);
            int dealerSuit1 = (rand() % 4);
            int dealerSuit2 = (rand() % 4);

            //displaying cards
            printf("=======PLAYER CARDS========\n");
            printf("%s%s\n", ranks[playerCard1], suits[playerSuit1]);
            printf("%s%s\n", ranks[playerCard2], suits[playerSuit2]);

            printf("=======DEALER CARDS========\n");
            printf("%s%s\n", ranks[dealerCard1], suits[dealerSuit1]);
            printf("%s%s\n", ranks[dealerCard2], suits[dealerSuit2]);

            //converting the index to its value
            int playerValue1 = (playerCard1 == 0) ? 1 : (playerCard1 >= 9 ? 0 : playerCard1 + 1);
            int playerValue2 = (playerCard2 == 0) ? 1 : (playerCard2 >= 9 ? 0 : playerCard2 + 1);
            int dealerValue1 = (dealerCard1 == 0) ? 1 : (dealerCard1 >= 9 ? 0 : dealerCard1 + 1);
            int dealerValue2 = (dealerCard2 == 0) ? 1 : (dealerCard2 >= 9 ? 0 : dealerCard2 + 1);

            int playerScore = abs(9 - ((playerValue1 + playerValue2) % 10));
            int dealerScore = abs(9 - ((dealerValue1 + dealerValue2) % 10));

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
                printf("          DRAW \n");
                printf(" BETTER LUCK NEXT TIME \n");
                printf("====================\n");
            }

            printf("Do you want to play again?");
            scanf(" %c", &playAgain);
        }while(playAgain == 'Y' || playAgain == 'y');
    }
}