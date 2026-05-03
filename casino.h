#ifndef CASINO_H
#define CASINO_H

//normal colors
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define RESET "\e[0m"
#define BOLD  "\e[1m"

//bold colors
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

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