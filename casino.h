#ifndef CASINO_H
#define CASINO_H

typedef struct {
    char name[50];
    int pin, balance, bj_wins, color_wins, roulette_wins, guess_wins, total_wins;
} User;

// prototypes
void signUp();
int verify(User *user);
void saveUser(User *user);
void playBlackjack(User *user);
void playGuess(User *user);
void showLeaderboard();

#endif