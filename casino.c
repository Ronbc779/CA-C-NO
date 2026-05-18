#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "casino.h"


int main(){
    srand(time(NULL));

    User user;
    int choice, game;

    while(1)
    {
        printf("\n=====%sCA-C-NO 2.0%s=====\n", BYEL, RESET);
        printf("1. Enter\n");
        printf("2. %sExit%s\n", RED, RESET);
        printf(">> ");
        scanf("%d",&choice);

        if(choice == 2)
            break;

        printf("\n1. Register\n2. Already a member\n3. %sExit%s\n>> ", RED, RESET);
        scanf("%d", &choice);

        if (choice == 1) {
            signUp();
        }
        else if (choice == 2) {
            //gets the values of user from  file and if it is there
            if (verify(&user)) {
                do{
                    printf("\n=======%sChoose Game%s======="
                           "\n1. Color Game"
                           "\n2. Blackjack"
                           "\n3. Hangman"
                           "\n4. Cloud Nine"
                           "\n5. High Low"
                           "\n6. Guess Game"
                           "\n7. Roulette"
                           "\n8. Show Leaderboard"
                           "\n9. %sLeave the gambling area%s\n>> ",BYEL, RESET, RED, RESET);
                    scanf("%d",&game);

                    switch(game)
                    {
                        //plays games in separate files
                        case 1: 
                           playColorGame(&user);
                            break;
                        case 2:
							playBlackjack(&user);
                            break;
                        case 3: 
                            playWordGuess(&user);
                            break;
                        case 4: 
                            playCloudNine(&user);
                            break;
                        case 5:
                            playHighLow(&user);
                            break;
                        case 6:
                            playGuess(&user);
                            break;
                        case 7:
                            playRoulette(&user);
                            break;
                        case 8: 
                        //show the leaderboard
                            showLeaderboard();
                            break;
                        case 9:
                            printf("\nExiting the gambling den...\n");
                            break;
                        default: 
                            printf("\nPlease choose a valid option!\n");
                            continue;
                    }
                } while (game != 9);

            } 
        }
        else{
            break;
        }
        
        
    }
    return 0;
}



