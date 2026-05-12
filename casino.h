#ifndef CASINO_H
#define CASINO_H

//normal colors
#define BLK "\x1B[0;30m"
#define RED "\x1B[0;31m"
#define GRN "\x1B[0;32m"
#define YEL "\x1B[0;33m"
#define BLU "\x1B[0;34m"
#define MAG "\x1B[0;35m"
#define CYN "\x1B[0;36m"
#define RESET "\x1B[0m"
#define BOLD  "\x1B[1m"

//bold colors
#define BBLK "\x1B[1;30m"
#define BRED "\x1B[1;31m"
#define BGRN "\x1B[1;32m"
#define BYEL "\x1B[1;33m"
#define BBLU "\x1B[1;34m"
#define BMAG "\x1B[1;35m"
#define BCYN "\x1B[1;36m"
#define BWHT "\x1B[1;37m"

// clear screen
#define CLRSCR() puts("\033[2J")

typedef struct {
    char name[50];
    int pin, balance, bj_wins, color_wins, roulette_wins, guess_wins, highlow_wins, total_wins;
} User;

// prototypes
void signUp();
int verify(User *user);
void saveUser(User *user);
void playBlackjack(User *user);
void playGuess(User *user);
void playColorGame(User *user);
void playRoulette(User *user);
void playCloudNine(User *user);
void showLeaderboard();

#endif