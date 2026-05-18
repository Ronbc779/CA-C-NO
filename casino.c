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
                           "\n1. Blackjack"
                           "\n2. Color Game"
                           "\n3. Roulette"
                           "\n4. Guess Game"
                           "\n5. High Low"
                           "\n6. Cloud Nine"
                           "\n7. Hangman"
                           "\n8. Show Leaderboard"
                           "\n9. %sLeave the gambling area%s\n>> ",BYEL, RESET, RED, RESET);
                    scanf("%d",&game);

                    switch(game)
                    {
                        //plays games in separate files
                        case 1: 
                           playBlackjack(&user);
                            break;
                        case 2:
							playColorGame(&user);
                            break;
                        case 3: 
                            playRoulette(&user);
                            break;
                        case 4: 
                            playGuess(&user);
                            break;
                        case 5:
                            playHighLow(&user);
                            break;
                        case 6:
                            playCloudNine(&user);
                            break;
                        case 7:
                            playWordGuess(&user);
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



