#ifndef CASINO_H
#define CASINO_H

#define RED   "\033[31m"
#define BLK   "\033[30m"
#define RESET "\033[0m"
#define YLW "\033[0;33m"
#define BOLD  "\033[1m"

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