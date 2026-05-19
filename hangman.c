#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "casino.h"

// Defined a safe upper limit for string buffers to prevent structural overflows
#define MAX_WORD_LEN 32

typedef struct {
    char category[MAX_WORD_LEN];
    char word[MAX_WORD_LEN];
} WordBank;

void playWordGuess(User *user) {
    int choice, bet;

    // Word bank
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

    // Safe evaluation of initial choice
    if (scanf("%d", &choice) != 1) {
        while(getchar() != '\n'); // Clear buffer on invalid input
        return;
    }

    if (choice != 1) return;

    do {
        printf("\n%s%s=== HANGMAN ===%s\n", BCYN, BOLD, RESET);
        printf("Balance: %d\n", user->balance);
        printf("Enter bet: ");
      
        // Check if bet input is a valid integer
        if (scanf("%d", &bet) != 1) {
            printf("Invalid input type! Please enter numbers only.\n");
            while(getchar() != '\n'); // Clear standard input stream
            continue; 
        }

        if (bet <= 0 || bet > user->balance) {
            printf("Invalid bet amount! You cannot bet more than your balance.\n");
            break; 
        }

        // Setup random word target
        int idx = rand() % bankSize;
        char *target = bank[idx].word;
        int len = strlen(target);
       
        // Build hidden display string
        char hidden[MAX_WORD_LEN];
        for(int i = 0; i < len; i++) {
            // Automatically reveal hyphens (e.g., KWEK-KWEK) so players don't guess symbols
            if (target[i] == '-') {
                hidden[i] = '-';
            } else {
                hidden[i] = '_';
            }
        }

        hidden[len] = '\0';

        int lives = len;
        int initialLives = len;
      
        // Tracks alphabet choices (A to Z) to stop punishing duplicate guesses
        int guessedLetters[26] = {0}; 

        printf("\nCategory: %s%s%s", BYEL, bank[idx].category, RESET);

        // Primary core guessing loop
        while (lives > 0 && strcmp(target, hidden) != 0) {
            printf("\nWord: ");
            for(int i = 0; i < len; i++) printf("%c ", hidden[i]);
            printf("\nLives: %s%d%s | Guess a letter: ", BRED, lives, RESET);
          
            char guess;
            scanf(" %c", &guess);

            guess = toupper(guess);

            // Filter out non-alphabet characters
            if (guess < 'A' || guess > 'Z') {
                printf("Please enter a valid letter from A to Z.\n");
                continue;
            }

            // Flag system check for duplicate entries
            if (guessedLetters[guess - 'A']) {
                printf("You already guessed '%c'! Try another letter.\n", guess);
                continue;
            }

            guessedLetters[guess - 'A'] = 1; // Mark letter as attempted

            int found = 0;
            for (int i = 0; i < len; i++) {
                if (target[i] == guess) {
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
            // Multiplier payout setup based on performance
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

        // Bankrupt termination protection
        if (user->balance <= 0) {
            printf("You are out of money!\n");
            break;
        }

        printf("\nPlay another word?\n1. Yes\n2. No\n>> ");
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            break; // Exit game loop safely if unexpected character is passed here
        }

    } while (choice == 1);
}