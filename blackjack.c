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

//prototypes
Card drawCard();
void printHand(const char* owner, Card hand[], int size);
int getCardValue(char r);
int calculateScore(Card hand[], int size);

void playBlackjack(User *user) {
    int choice, bet;
    //explains the rules to user
    printf("\n=== %sBLACKJACK RULES & REWARDS %s===\n", BCYN, RESET);
    printf("Rules:\n1. The goal is to be higher than your opponent without going over 21.\n2. Going over 21 automatically results in a loss.\n3. The dealer will keep hitting unless it has 17 or more.\n4. You automatically win when the dealer busts.\nPays %s1 to 1%s\n=============\nWould you like to play?\n1. Yes\n2. No\n>> ", YEL, RESET);
    scanf("%d", &choice);

    if (choice == 2) return;

    //gameplay loop
    do {
        printf("\n%s%s=== BLACKJACK ===%s\n", BCYN, BOLD, RESET);
        printf("Balance: %d\n", user->balance);
        printf("Enter bet: ");
        scanf("%d", &bet);

        if (bet <= 0 || bet > user->balance) {
            printf("Invalid bet!\n");
            break;
        }

        //initialize player and dealer as array structures
        Card player_hand[MAX_HAND], dealer_hand[MAX_HAND];
        int player_size = 0, dealer_size = 0;

        // Initial deal
        player_hand[player_size++] = drawCard();
        player_hand[player_size++] = drawCard();
        dealer_hand[dealer_size++] = drawCard();
        dealer_hand[dealer_size++] = drawCard();

        while (1) {
            printHand("Player", player_hand, player_size);
            printf("Dealer shows: ");
            if (dealer_hand[0].suit == 'H' || dealer_hand[0].suit == 'D') {
                printf("[%s%c%c%s] %s[??]%s\n", RED, dealer_hand[0].rank, dealer_hand[0].suit, RESET, CYN, RESET);
            } else {
                printf("[%c%c] %s[??]%s\n", dealer_hand[0].rank, dealer_hand[0].suit, CYN, RESET);
            }

            //calculate score
            int player_score = calculateScore(player_hand, player_size);
            //check if immediate blackjack
            if (player_score == 21) {
                printHand("Player", player_hand, player_size);
                printf("%s%sNATURAL BLACKJACK!%s\n", MAG, BOLD, RESET);
            }
            if (player_score > 21) break;

            printf("\n1. Hit (Draw Card)\n2. Stand (Stay)\n>> ");
            scanf("%d", &choice);

            if (choice == 1) {
                player_hand[player_size++] = drawCard();
            } else {
                break;
            }
        }

        //calculate player's final score
        int p_final_score = calculateScore(player_hand, player_size);

        // Dealer's turn (only if player didn't bust)
        int d_final_score = calculateScore(dealer_hand, dealer_size);
        if (p_final_score <= 21) {
            printf("\nDealer reveals: [%c%c] [%c%c]\n", dealer_hand[0].rank, dealer_hand[0].suit, dealer_hand[1].rank, dealer_hand[1].suit);

            while (calculateScore(dealer_hand, dealer_size) < 17) {
                printf("Dealer hits...\n");
                dealer_hand[dealer_size++] = drawCard();
                printHand("Dealer", dealer_hand, dealer_size);
            }
            d_final_score = calculateScore(dealer_hand, dealer_size);
        }

        // Determine winner
        printf("\n--- FINAL RESULTS ---\nPLAYER SCORE: %d\nDEALER SCORE: %d\n", p_final_score, d_final_score);

        if (p_final_score > 21) {
            printf("BUST! You lost %d.\n", bet);
            user->balance -= bet;
        } else if (d_final_score > 21 || p_final_score > d_final_score) {
            printf("%sYOU WIN! You gained %d%s.\n", GRN, bet, RESET);
            user->balance += bet;
            user->bj_wins++;
            user->total_wins++;
        } else if (p_final_score < d_final_score) {
            printf("%sDEALER WINS! You lost %d%s.\n",RED, bet, RESET);
            user->balance -= bet;
        } else {
            printf("%sPUSH   (Tie)!%s Your bet was returned.\n", BWHT, RESET);
        }

        saveUser(user);

        printf("Want to play again?\n1. Yes\n2. No\n>> ");
        scanf("%d", &choice);
        if (choice == 2) return;
    } while (1);
}

Card drawCard() {
    //randomly get a rank and suit
    Card c;
    c.rank = ranks[rand() % 13];
    c.suit = suits[rand() % 4];
    c.value = getCardValue(c.rank);
    return c;
}

void printHand(const char* owner, Card hand[], int size) {
    printf("%s's hand: ", owner);
    for (int i = 0; i < size; i++) {
       const char* suit_color = RESET;
        
        // Assign colors based on suit
        switch(hand[i].suit) {
            case 'H': suit_color = BRED; break; // Hearts: Bold Red
            case 'D': suit_color = RED;   break; // Diamonds: Standard Red
            case 'S': suit_color = BLU; break; // Spades: Blue
            case 'C': suit_color = GRN;   break; // Clubs: Green
        }
        printf("[%s%c%c%s] ", suit_color, hand[i].rank, hand[i].suit, RESET);
    }
    printf("(Score: %s%d%s)\n", BYEL, calculateScore(hand, size), RESET);
}

int getCardValue(char r) {
    //convert letters to corresponding values
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