#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "casino.h"

#define MAX_HAND 10


typedef struct {
    char rank;
    char suit;
    int value;
} Card;

char suits[] = {'H','S','D','C'};
char ranks[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};

Card drawCard();
void printHand(const char* owner, Card hand[], int size);
int getCardValue(char r);
int calculateScore(Card hand[], int size);

void playBlackjack(User *user) {
    int choice, bet;
    printf("\n********BLACKJACK********\n");
    printf("Rules:\n1. The goal is to be higher than your opponent without going over 21.\n2. Going over 21 automatically results in a loss.\n3. The dealer will keep hitting unless it has 17 or more.\n4. You automatically win when the dealer busts.\n=============\nWould you like to play?\n1. Yes\n2. No\n>> ");
    scanf("%d", &choice);

    if (choice == 2) return;

    do {
        printf("\n********BLACKJACK********\n");
        printf("Balance: %d\n", user->balance);
        printf("Enter bet: ");
        scanf("%d", &bet);

        if (bet <= 0 || bet > user->balance) {
            printf("Invalid bet!\n");
            break;
        }

        Card pHand[MAX_HAND], dHand[MAX_HAND];
        int pSize = 0, dSize = 0;

        // Initial deal
        pHand[pSize++] = drawCard();
        pHand[pSize++] = drawCard();
        dHand[dSize++] = drawCard();
        dHand[dSize++] = drawCard();

        while (1) {
            printHand("Player", pHand, pSize);
            printf("Dealer shows: [%c%c]\n", dHand[0].rank, dHand[0].suit);

            int pScore = calculateScore(pHand, pSize);
            if (pScore > 21) break;

            printf("\n1. Hit (Draw Card)\n2. Stand (Stay)\n>> ");
            scanf("%d", &choice);

            if (choice == 1) {
                pHand[pSize++] = drawCard();
            } else {
                break;
            }
        }

        int playerFinal = calculateScore(pHand, pSize);

        // Dealer's turn (only if player didn't bust)
        int dealerFinal = calculateScore(dHand, dSize);
        if (playerFinal <= 21) {
            printf("\nDealer reveals: [%c%c] [%c%c]\n", dHand[0].rank, dHand[0].suit, dHand[1].rank, dHand[1].suit);

            while (calculateScore(dHand, dSize) < 17) {
                printf("Dealer hits...\n");
                dHand[dSize++] = drawCard();
                printHand("Dealer", dHand, dSize);
            }
            dealerFinal = calculateScore(dHand, dSize);
        }

        // Determine winner
        printf("\n--- FINAL RESULTS ---\nPLAYER SCORE: %d\nDEALER SCORE: %d\n", playerFinal, dealerFinal);

        if (playerFinal > 21) {
            printf("BUST! You lost %d.\n", bet);
            user->balance -= bet;
        } else if (dealerFinal > 21 || playerFinal > dealerFinal) {
            printf("%sYOU WIN! You gained %d%s.\n", GRN, bet, RESET);
            user->balance += bet;
            user->bj_wins++;
            user->total_wins++;
        } else if (playerFinal < dealerFinal) {
            printf("%sDEALER WINS! You lost %d%s.\n",RED, bet, RESET);
            user->balance -= bet;
        } else {
            printf("PUSH (Tie)! Your bet was returned.\n");
        }

        saveUser(user);

        printf("Want to play again?\n1. Yes\n2. No\n>> ");
        scanf("%d", &choice);
        if (choice == 2) return;
    } while (1);
}

Card drawCard() {
    Card c;
    c.rank = ranks[rand() % 13];
    c.suit = suits[rand() % 4];
    c.value = getCardValue(c.rank);
    return c;
}

void printHand(const char* owner, Card hand[], int size) {
    printf("%s's hand: ", owner);
    for (int i = 0; i < size; i++) {
        if (hand[i].suit == 'H' || hand[i].suit == 'D') {
            // Rank and Suit will both be Red
            printf("[%s%s%c%c%s] ", RED, BOLD, hand[i].rank, hand[i].suit, RESET);
        } else {
            printf("[%c%c] ", hand[i].rank, hand[i].suit);
        }
    }
    printf("(Value: %d)\n", calculateScore(hand, size));
}

int getCardValue(char r) {
    if (r == 'A') return 11;
    if (r == 'T' || r == 'J' || r == 'Q' || r == 'K') return 10;
    return r - '0';
}

int calculateScore(Card hand[], int size) {
    int total = 0, aces = 0;
    for (int i = 0; i < size; i++) {
        total += hand[i].value;
        if (hand[i].rank == 'A') aces++;
    }
    while (total > 21 && aces > 0) {
        total -= 10;
        aces--;
    }
    return total;
}