#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

extern void saveUser(char name[], int pin, int balance, int bj_wins, int sm_wins, int roulette_wins, int guess_wins, int total_wins);

int getBallPosition(int difficulty);
void drawCups(int count);

void playGuess(char name[], int pin, int *balance, int bj_wins, int *total_wins, int sm_wins, int roulette_wins, int *guess_wins){
    int choice, bet;
    printf("\n????????Guess Game????????\n");
    printf("Rules:\n1. Choose the difficulty you like.\n2. The harder the difficulty, the more options to choose from, the higher the payout.\n3. A ball will be placed in a random spot, all you have to do is guess where it is.\n4. There will be 3 rounds each starting with 3 balls and decreasing to 1.\n5. Payout rates:\nEasy = x1\nMedium = x2\nHard = x3\n=============\nWould you like to play?\n1. Yes\n2. No\n>> ");
    scanf("%d", &choice);

    if(choice == 2) return;

    do{
        int diff, user_guess, won_round = 1;
        printf("\n????????Guess Game????????\n");
        printf("Balance: %d\n", *balance);
        printf("Enter bet: ");
        scanf("%d", &bet);

        if (bet <= 0 || bet > *balance) {
            printf("Invalid bet!\n");
            break;
        }

        printf("\n????????Guess Game????????\n");
        printf("Choose difficulty:\n1. Easy: 4 choices\n2. Medium: 6 choices\n3. Hard: 8 choices\n>> ");
        scanf("%d", &diff);

        int max_choices = (diff == 1) ? 4 : (diff == 2) ? 6 : 8;

        for (int round = 3; round >= 1; round--) {
            printf("\n--- ROUND %d: Find one of %d balls ---\n", (4 - round), round);

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
                printf("Correct! You found a ball.\nShuffling the remaining balls...\n");
            } else {
                printf("\nEmpty! The ball/s were at: ");
                for(int i = 0; i < round; i++) printf("%d ", ball_pos[i]);
                printf("\n");
                won_round = 0;
                break; // Game over if you miss a round
            }
        }

        if (won_round) {
            int payout = bet * diff; 
            printf("\nCONGRATULATIONS! You passed all rounds. Won: %d\n", payout);
            *balance += payout;
            (*guess_wins)++;
            (*total_wins)++;
        } else {
            printf("\nBetter luck next time. Lost: %d\n", bet);
            *balance -= bet;
        }

        saveUser(name, pin, *balance, bj_wins, sm_wins, roulette_wins, *guess_wins, *total_wins);
        printf("\n1. Play Again\n2. Quit\n>> ");
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
