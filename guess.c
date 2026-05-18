#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "casino.h"

extern void saveUser(User *user);

int getBallPosition(int difficulty);
void drawCups(int count);

void playGuess(User *user){
    int choice, bet;
    printf("\n=====%sGuess Game%s=====\n", CYN, RESET);
    printf("Rules:\n1. Choose the difficulty you like.\n2. The harder the difficulty, the more options to choose from, the higher the payout.\n3. A ball will be placed in a random spot, all you have to do is guess where it is.\n4. There will be 3 rounds each starting with 3 balls and decreasing to 1.\n5. Payout rates:\n");
    printf("%sEasy%s = %sx1%s\n", GRN, RESET, RED, RESET);
    printf("%sMedium%s = %sx2%s\n", YEL, RESET, RED, RESET);
    printf("%sHard%s = %sx3%s\n=============\nWould you like to play?\n1. Yes\n2. No\n>> ", BRED, RESET, RED, RESET);
    scanf("%d", &choice);

    if(choice == 2) return;

    do{
        int diff, user_guess, won_round = 1;
        printf("\n=====%sGuess Game%s=====\n", BCYN, RESET);
        printf("Balance: %s%d%s\n", YEL, user->balance, RESET);
        printf("Enter bet: ");
        scanf("%d", &bet);

        if (bet <= 0 || bet > user->balance) {
            printf("%sInvalid bet!%s\n", RED, RESET);
            break;
        }

        printf("\n=====%sGuess Game%s=====\n", BCYN, RESET);
        printf("Choose difficulty:\n1. %sEasy: 4 choices%s\n2. %sMedium: 6 choices%s\n3. %sHard: 8 choices%s\n>> ", GRN, RESET, YEL, RESET, BRED, RESET);
        scanf("%d", &diff);

        int max_choices = (diff == 1) ? 4 : (diff == 2) ? 6 : 8;

        for (int round = 3; round >= 1; round--) {
            printf("\n--- ROUND %s%d%s: Find one of %s%d%s balls ---\n", RED, (4 - round), RESET, RED, round, RESET);

            drawCups(max_choices);
            
            // Generate ball positions for this round
            int ball_pos[3]; // Max 3 balls
            for (int i = 0; i < round; i++) {
                int unique;
                int new_pos;
                
                do {
                    unique = 1; // Assume it's unique at the start
                    new_pos = getBallPosition(diff);
                    
                    // Check if this new_pos was already used in this round
                    for (int j = 0; j < i; j++) {
                        if (new_pos == ball_pos[j]) {
                            unique = 0; // It's a duplicate, set unique to false
                            break;
                        }
                    }
                } while (!unique); // Keep trying if it wasn't unique

                ball_pos[i] = new_pos;
            }

            printf("Choose a cup (0 to %d): ", max_choices - 1);
            scanf("%d", &user_guess);

            int found = 0;
            for (int i = 0; i < round; i++) {
                if (user_guess == ball_pos[i]) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                //shuffle
                printf("%sCorrect! You found a ball.%s\nShuffling the remaining balls...\n", GRN, RESET);
            } else {
                printf("\n%sEmpty! The ball/s were at:%s ", RED, RESET);
                for(int i = 0; i < round; i++) printf("%d ", ball_pos[i]);
                printf("\n");
                won_round = 0;
                break; // Game over if you miss a round
            }
        }

        if (won_round) {
            int payout = bet * diff; 
            printf("\nCONGRATULATIONS! You passed all rounds. Won: %d\n", payout);
            user->balance += payout;
            (user->guess_wins)++;
            (user->total_wins)++;
        } else {
            printf("\nBetter luck next time. %sLost: %d%s\n", RED, bet, RESET);
            user->balance -= bet;
        }

        saveUser(user);

        printf("\n1. Play Again\n2. %sQuit%s\n>> ", RED, RESET);
        scanf("%d", &choice);
        if (choice == 2) break;
        

    }while(1);
}

int getBallPosition(int difficulty){
    if (difficulty == 1) return rand() % 4;
    if (difficulty == 2) return rand() % 6;
    return rand() % 8;
}

void drawCups(int count) {
    for(int i = 0; i < count; i++) printf("  ___   "); 
    printf("\n");
    for(int i = 0; i < count; i++) printf(" /   \\  ");
    printf("\n");
    for(int i = 0; i < count; i++) printf("|  %d  | ", i);
    printf("\n\n");
}
