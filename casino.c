#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

//function prototypes
void signUp();
int verify(char name[], int *pin, int *balance, int *bj_wins, int *sm_wins, int *roulette_wins, int *guess_wins, int *total_wins);
void saveUser(char name[], int pin, int balance, int bj_wins, int sm_wins, int roulette_wins, int *guess_wins, int total_wins);
void playBlackjack(char name[], int pin, int *balance, int *bj_wins, int *total_wins, int sm_wins, int roulette_wins, int guess_wins);
void playGuess(char name[], int pin, int *balance, int bj_wins, int *total_wins, int sm_wins, int roulette_wins, int *guess_wins);
void showLeaderboard();

typedef struct {
    char name[50];
    int pin, balance, bj, sm, roul, guess, total;
} User;

int main(){
    srand(time(NULL));

    char name[50];
    int pin = 0, balance = 0, bj_wins = 0, sm_wins = 0, roulette_wins = 0, guess_wins = 0, total_wins = 0;
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

        printf("\n1. Create Membership\n2. Already a member\n3. Exit\n>> ");
        scanf("%d", &choice);

        if (choice == 1) {
            signUp();
        }
        else if (choice == 2) {
            //gets the values of user from  file and if it is there
            if (verify(name, &pin, &balance, &bj_wins, &sm_wins, &roulette_wins, &guess_wins, &total_wins)) {
                do{
                    printf("\n=======Choose Game=======\n1. Blackjack\n2. Slot Machine\n3. Roulette\n4. Guess Game\n5. Show Leaderboard\n6. Leave the gambling area\n>> ");
                    scanf("%d",&game);

                    switch(game)
                    {
                        case 1: 
                        //play blackjack in seperate file
                            playBlackjack(name, pin, &balance, &bj_wins, &total_wins, sm_wins, roulette_wins, guess_wins);
                            break;
                        case 2: break;
                        case 3: break;
                        case 4: 
                            playGuess(name, pin, &balance, bj_wins, &total_wins, sm_wins, roulette_wins, &guess_wins);
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



