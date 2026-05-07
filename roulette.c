#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "casino.h"
#include <unistd.h>

#define SLEEP(ms) usleep(ms * 1000)

//for bets
typedef struct {
    int type;  
    int amount;
} RouletteBet;

// Roulette wheel sequence
int wheel[] = {0, 28, 9, 26, 30, 11, 7, 20, 32, 17, 5, 22, 34, 15, 3, 24, 36, 13, 1, 00, 27, 10, 25, 29, 12, 8, 19, 31, 18, 6, 21, 33, 16, 4, 23, 35, 14, 2};

// Helper to check if a number is red (based on standard table)
int isRed(int num) {
    int reds[] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
    for (int i = 0; i < 18; i++) if (reds[i] == num) return 1;
    return 0;
}

void displayTable() {
    printf("\n%s%s========== ROULETTE TABLE ==========%s\n", BCYN, BOLD, RESET);
    printf(" [00] %s[ 0]%s\n", GRN, RESET);
    
    // Display numbers 1-36 in 3 rows
    for (int row = 0; row < 3; row++) {
        for (int i = 1; i <= 36; i++) {
            if (i % 3 == (row == 0 ? 0 : row == 1 ? 2 : 1)) {
                if (isRed(i)) printf("%s[%2d]%s ", RED, i, RESET);
                else printf("%s[%2d]%s ", BLU, i, RESET);
            }
        }
        printf("\n");
    }
    
    printf("\n%s--- OUTSIDE BETS ---%s\n", YEL, RESET);
    printf("37. 1st 12 (1-12)   38. 2nd 12 (13-24)  39. 3rd 12 (25-36)\n");
    printf("40. 1-18 (Low)      41. EVEN            42. %sRED%s\n", RED, RESET);
    printf("43. %sBLACK%s           44. ODD             45. 19-36 (High)\n", BLU, RESET);
    printf("==============================================\n");
}

void spinAnimation(int finalResult) {
    int animationCycles = 35;
    int delay = 30;

    printf("\n%sSpinning the wheel...%s\n", BOLD, RESET);
    
    for (int i = 0; i < animationCycles; i++) {
        int tempIdx = rand() % 38;
        int num = wheel[tempIdx];
        
        const char* color = (num == 0 || num == 00) ? GRN : (isRed(num) ? RED : BLU);
        
        printf("\r    %s>>%s  %s[%02d]%s  %s<<%s    ", CYN, RESET, color, num, RESET, CYN, RESET);
        fflush(stdout);
        
        SLEEP(delay);
        if (i > 20) delay += 50; // Slowing down
    }

    const char* finalColor = (finalResult == 0 || finalResult == 00) ? GRN : (isRed(finalResult) ? RED : BLU);
    printf("\r    ===> WINNING NUMBER: %s[%02d]%s <===    \n", finalColor, finalResult, RESET);
}

void playRoulette(User *user) {
    int isPlaying = 1;

    // 1. EXPLAIN RULES AND REWARDS
    printf("\n%s%s=== ROULETTE RULES & REWARDS ===%s\n", BCYN, BOLD, RESET);
    printf("1. You can place multiple bets before the wheel spins.\n");
    printf("2. %sStraight Up (0-36): Pays %s35 to 1%s.\n", YEL, RED, RESET);
    printf("3. %sDozens (1st, 2nd, 3rd 12): Pays %s2 to 1.%s\n", YEL, RED, RESET);
    printf("4. %sEven/Odd, Red/Black, Low/High: Pays %s1 to 1.%s\n", YEL, RED, RESET);
    printf("5. If the ball lands on %s0%s or %s00%s, all outside bets lose.\n", GRN, RESET, GRN, RESET);

    printf("\nDo you want to step up to the table?\n1. Yes\n2. No\n>> ");
    int choice;
    scanf("%d", &choice);
    if (choice != 1) return;
    
    while (isPlaying) {
        RouletteBet bets[50]; // Store up to 50 bets per spin
        int betCount = 0;
        int totalSessionBet = 0;

        displayTable();

        // Add up multiple bets
        int addingBets = 1;
        while (addingBets) {
            printf("\n%s[ Current Bets: %d | Total Wager: %d | Balance: %d ]%s\n", 
                   BOLD, betCount, totalSessionBet, user->balance, RESET);
            
            int currentType, currentAmount;
            printf("Enter Number/Type (0-45) to bet on: ");
            scanf("%d", &currentType);

            if (currentType < 0 || currentType > 45) {
                printf("%sInvalid bet type!%s\n", RED, RESET);
                continue;
            }

            printf("Enter amount for this bet: ");
            scanf("%d", &currentAmount);

            if (currentAmount <= 0 || (totalSessionBet + currentAmount) > user->balance) {
                printf("%sInsufficient funds or invalid amount!%s\n", RED, RESET);
            } else {
                bets[betCount].type = currentType;
                bets[betCount].amount = currentAmount;
                totalSessionBet += currentAmount;
                betCount++;
            }

            //all in
            if (totalSessionBet >= user->balance) {
                printf("You've bet your entire balance!\n");
                addingBets = 0;
            } else {
                printf("\n1. Add another bet\n2. Spin the wheel\n>> ");
                int next;
                scanf("%d", &next);
                if (next == 2) addingBets = 0;
            }
        }

        //spin the wheel
        int resultIdx = rand() % 38;
        int winningNum = wheel[resultIdx];
        spinAnimation(winningNum);

        // return rewards
        int totalWon = 0;
        for (int i = 0; i < betCount; i++) {
            int winAmount = 0;
            int type = bets[i].type;
            int amt = bets[i].amount;

            if (type <= 36) { // Straight Up
                if (type == winningNum) winAmount = amt * 35;
            } else { // Outside Bets
                switch(type) {
                    case 37: if (winningNum >= 1 && winningNum <= 12) winAmount = amt * 2; break;
                    case 38: if (winningNum >= 13 && winningNum <= 24) winAmount = amt * 2; break;
                    case 39: if (winningNum >= 25 && winningNum <= 36) winAmount = amt * 2; break;
                    case 40: if (winningNum >= 1 && winningNum <= 18) winAmount = amt; break;
                    case 41: if (winningNum != 0 && winningNum != 00 && winningNum % 2 == 0) winAmount = amt; break;
                    case 42: if (isRed(winningNum)) winAmount = amt; break;
                    case 43: if (!isRed(winningNum) && winningNum != 0 && winningNum != 00) winAmount = amt; break;
                    case 44: if (winningNum % 2 != 0) winAmount = amt; break;
                    case 45: if (winningNum >= 19 && winningNum <= 36) winAmount = amt; break;
                }
            }

            if (winAmount > 0) {
                totalWon += (winAmount + amt); // Return original bet + profit
            }
        }

        // Final accounting for the spin
        int netResult = totalWon - totalSessionBet;
        user->balance += netResult;

        if (netResult > 0) {
            printf("\n%s SPIN TOTAL: YOU WON %d! %s\n", GRN, netResult, RESET);
            user->roulette_wins++;
            user->total_wins++;
        } else if (netResult < 0) {
            printf("\n%sSPIN TOTAL: YOU LOST %d.%s\n", RED, abs(netResult), RESET);
        } else {
            printf("\n%sEVEN: You broke even on this spin.%s\n", YEL, RESET);
        }

        saveUser(user);

        // 5. KEEP PLAYING?
        if (user->balance <= 0) {
            printf("%sYou are out of money! Returning to menu.%s\n", RED, RESET);
            isPlaying = 0;
        } else {
            printf("\nKeep playing Roulette?\n1. Yes\n2. No\n>> ");
            int keepGoing;
            scanf("%d", &keepGoing);
            if (keepGoing != 1) isPlaying = 0;
        }
    }

    
}