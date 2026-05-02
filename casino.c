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
        printf("\n=====CA-C-NO 2.0=====\n");
        printf("1. Enter\n");
        printf("2. Exit\n");
        printf(">> ");
        scanf("%d",&choice);

        if(choice == 2)
            break;

        printf("\n1. Register\n2. Already a member\n3. Exit\n>> ");
        scanf("%d", &choice);

        if (choice == 1) {
            signUp();
        }
        else if (choice == 2) {
            //gets the values of user from  file and if it is there
            if (verify(&user)) {
                do{
                    printf("\n=======Choose Game=======\n1. Blackjack\n2. Color Game\n3. Roulette\n4. Guess Game\n5. Show Leaderboard\n6. Leave the gambling area\n>> ");
                    scanf("%d",&game);

                    switch(game)
                    {
                        case 1: 
                        //play blackjack in seperate file
                            playBlackjack(&user);
                            break;
                        case 2: break;
                        case 3: break;
                        case 4: 
                            playGuess(&user);
                            break;
                        case 5: 
                        //show the leaderboard
                            showLeaderboard();
                            break;
                        default: continue;
                    }
                } while (game != 6);

            } 
        }
        else{
            break;
        }
        
        
    }
    return 0;
}



