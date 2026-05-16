#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "casino.h"

typedef struct {
    char category[20];
    char word[20];
} WordBank;

void playWordGuess(User *user) {
    int choice, bet;
    
    WordBank bank[] = {
        {"STREETFOOD", "FISHBALL"}, {"STREETFOOD", "KWEK-KWEK"}, {"STREETFOOD", "ISAW"},
        {"STREETFOOD", "KIKIAM"}, {"STREETFOOD", "BETAMAX"}, {"STREETFOOD", "CALAMARES"},
        {"STREETFOOD", "BALUT"}, {"STREETFOOD", "SIOMAI"}, {"STREETFOOD", "EMPANADA"},
        {"DESSERT", "TURON"}, {"DESSERT", "TAHO"}, {"DESSERT", "BIBINGKA"},
        {"DESSERT", "KUTSINTA"}, {"DESSERT", "SORBETES"}, {"DESSERT", "SCRAMBLE"},
        {"DESSERT", "PASTILLAS"}, {"DESSERT", "POLVORON"}, {"DESSERT", "GULAMAN"},
        {"ULAM", "ADOBO"}, {"ULAM", "SINIGANG"}, {"ULAM", "AFRITADA"},
        {"ULAM", "LECHON"}, {"ULAM", "KALDERETA"}, {"ULAM", "SISIG"},
        {"ULAM", "PARES"}, {"ULAM", "DINUGUAN"}, {"ULAM", "PINAKBET"}
    };
    int bankSize = sizeof(bank) / sizeof(bank[0]);

    printf("\n%s%s=== HANGMAN RULES ===%s\n", BCYN, BOLD, RESET);
    printf("1. Guess the hidden word letter by letter.\n");
    printf("2. Lives = Word Length. Lose a life for every wrong guess.\n");
    printf("3. %sMultiplier:%s Win more by keeping more lives!\n", YEL, RESET);
    printf("   (Max payout: 2x bet for 0 mistakes)\n");
    printf("==========================\nWould you like to play?\n1. Yes\n2. No\n>> ");
    scanf("%d", &choice);

    if (choice == 2) return;

    do {
        printf("\n%s%s=== HANGMAN ===%s\n", BCYN, BOLD, RESET);
        printf("Balance: %d\n", user->balance);
        printf("Enter bet: ");
        scanf("%d", &bet);

        if (bet <= 0 || bet > user->balance) {
            printf("Invalid bet!\n");
            break;
        }

        int idx = rand() % bankSize;
        char *target = bank[idx].word;
        int len = strlen(target);
        
        char hidden[21];
        for(int i = 0; i < len; i++) hidden[i] = '_';
        hidden[len] = '\0';

        int lives = len;
        int initialLives = len;

        printf("\nCategory: %s%s%s", BYEL, bank[idx].category, RESET);
        
        while (lives > 0 && strcmp(target, hidden) != 0) {
            printf("\nWord: ");
            for(int i=0; i<len; i++) printf("%c ", hidden[i]);
            printf("\nLives: %s%d%s | Guess a letter: ", BRED, lives, RESET);
            
            char guess;
            scanf(" %c", &guess);
            guess = toupper(guess);

            int found = 0;
            for (int i = 0; i < len; i++) {
                if (target[i] == guess && hidden[i] == '_') {
                    hidden[i] = guess;
                    found = 1;
                }
            }

            if (!found) {
                printf("%sWrong!%s\n", RED, RESET);
                lives--;
            } else {
                printf("%sCorrect!%s\n", GRN, RESET);
            }
        }

        if (strcmp(target, hidden) == 0) {
            // Multiplier = 1.0 + (remaining_lives / total_lives)
            // Example: 0 mistakes = 2.0x, Half lives left = 1.5x
            float multiplier = 1.0f + ((float)lives / initialLives);
            int winnings = (int)(bet * multiplier);
            int profit = winnings - bet;

            printf("\n%s%s★ YOU GUESSED IT! ★%s\n", MAG, BOLD, RESET);
            printf("The word was: %s\n", target);
            printf("Multiplier: %.2fx | Gained: %d\n", multiplier, profit);
            
            user->balance += profit;
            user->total_wins++;
        } else {
            printf("\n%sOUT OF LIVES!%s\n", RED, RESET);
            printf("The word was: %s\n", target);
            printf("You lost %d.\n", bet);
            
            user->balance -= bet;
        }

        saveUser(user);

        if (user->balance <= 0) {
            printf("You are out of money!\n");
            break;
        }

        printf("\nPlay another word?\n1. Yes\n2. No\n>> ");
        scanf("%d", &choice);
        if (choice == 2) break;

    } while(1);
}