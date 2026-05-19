# CA-C-NO
CA-C-NO is a terminal-based gambling simulator. Users have the ability to place bets using a virtual currency to play gambling games of different complexities, stakes, and payouts. It also features a player leaderboard for competition between game-specific wins and total acquired currency.

---------------
## Key Features
1. Account and Persistence
    - A save function that manages user accounts, tracking balances, and win/loss records across multiple gaming sessions.
2. Dynamic Leaderboard
    - A ranking system that shows the top players in descending order based on user-selected categories.
3. Cultural Assimilation
    - Includes Filipino carnival games and classic casino games.
4. Currency & Stake Management
    - A system that provides initial capital and enforces consequences, such as program lock-out, if a user reaches a zero balance.
5. Game Variety
    - A modular design that supports different mini-games in a single terminal interface.

## Program Structure
### Main Programs
* <ins>Main Controller (casino.c)</ins>
  - Serves as the central hub of the program. It manages the primary execution loop, handling transitions among the authentication sequence, the     main game menu, and the cleanup/exit process.
* <ins>Menu and Data Management (menu_functions.c)</ins> 
  - Responsible for functionality of user prompts, storage, and validation of user input in the main menu (account details, authentication system, balance, leaderboard statistics).

### Games
* <ins>Color Game</ins>
  - Simulates the real-life counterpart. User bets on a color and after "dropping" three six-faced cubes, the amount of front faces with the chosen color multiplies the initial bet.
* <ins>Blackjack</ins>
  - Simulates the real-life counterpart. The house and the user draw cards until either hits (has a hand value of exactly 21) or busts (over 21). 
* <ins>Hangman</ins>
  - Guess the correct word one letter at a time, word bank is composed of Filipino cuisine and dishes.
* <ins>Cloud Nine</ins>
  - Inspired from the "Lucky Nine" real-life card game. The house and the user draw a two-card hand. The hand with the nearest value to nine (9) wins.
* <ins>High Low</ins>
  - A guessing game where the user must answer a set of dichotomous questions correctly about a random card drawn by the house.
* <ins>Guess Game</ins>
  - A ball is placed under a random cup among a set of other cups. After a "shuffling" period, the user must choose the cup where the ball is placed under.
* <ins>Roulette</ins>
  - Simulates the real-life counterpart. The user picks specific tiles on a colored roulette wheel to bet on. The wheel is spun and the payout depends if the wheel lands on the selected outcome. 

