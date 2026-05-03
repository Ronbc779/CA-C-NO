#ifndef CASINO_H
#define CASINO_H

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define RESET "\e[0m"
#define BOLD  "\e[1m"

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