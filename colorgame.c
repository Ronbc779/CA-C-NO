#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "casino.h"

#define COLOR_CHOICES 6
#define COLOR_CODE_WIDTH 9
#define CUBE_HEIGHT 10
#define CUBE_COUNT 3

// Bet multipliers relative to correct guesses
#define MULTIPLIER_1 1
#define MULTIPLIER_2 2
#define MULTIPLIER_3 3

void printCube(char colors[COLOR_CHOICES][COLOR_CODE_WIDTH], int cube_size, int chosen_color);
void askGameplayLoop(int *play_switch, char message[]);
void askBetAmount(int *bet, int *balance);
void askColorGuess(int *color_choice);
void chooseRandomColor(int random_colors[CUBE_COUNT], char colors[COLOR_CHOICES][COLOR_CODE_WIDTH], 
	int user_choice, int *correct_guesses);
void updatePlayerStatistics(int *balance, int *wins, int *bet, int correct_guesses);

void playColorGame(User *user){
	// Fetches ANSI color codes for cube faces.
	char colors[COLOR_CHOICES][COLOR_CODE_WIDTH] = {
		RED, GRN, YEL, 
		BLU, MAG, CYN
	};
	
	int *balance = &user->balance;
	int *wins = &user->color_wins;
	int prompt_play; 

	// Prints rules and odds
	printf("%s\n========COLOR GAME========%s" 
			"\n1. Pick one color from the list"
			"\n2. Wait for the roll to happen and see if you're lucky! For hits:"
			"\n\ta. One (1) color: x%d"
			"\n\tb. Two (2) colors: x%d"	
			"\n\tc. Three (3) colors: x%d", BCYN, RESET, MULTIPLIER_1, MULTIPLIER_2, MULTIPLIER_3	
	);
	
	askGameplayLoop(&prompt_play, "Would you like to play?"); // First gameplay loop

	while(prompt_play == 1){
		printf("\n\nName: %s%s%s | Balance: %s%d%s | Wins: %s%d%s", 
			YEL, user->name, RESET, YEL, *balance, RESET, YEL, *wins, RESET); 
		
		int random_colors[CUBE_COUNT]; 	// Storage of random colors for comparison
		// Default initialization for each gameplay loop
		int bet = 0; int user_color = 0; int correct_guesses = 0; 
		
		askBetAmount(&bet, balance);
		askColorGuess(&user_color);
		chooseRandomColor(random_colors, colors, user_color, &correct_guesses);
		updatePlayerStatistics(balance, wins, &bet, correct_guesses);
		askGameplayLoop(&prompt_play, "Would you like to play again?");
	} 
	saveUser(user);
	CLRSCR(); 
	printf("\nLeaving 'Color Game', going back to main screen...\n");
	
}

void printCube(char colors[COLOR_CHOICES][COLOR_CODE_WIDTH], int cube_size, int chosen_color){
	// Sets cube to assigned color
	printf("%s", colors[chosen_color]);
	for(int i = 0; i < cube_size; i++){ // Cube height
		// Cube width printing
		for(int j = 0; j < cube_size*2; j++){
			printf("X");
		}
		printf("\n");
	} printf("%s", RESET);
}

void askGameplayLoop(int *play_switch, char message[]){
	while(true){ // First run for gameplay loop
		printf("\n\n============="); 
		printf("\n%s\n1. %sYes%s\n2. %sNo%s\n>> ", message, GRN, RESET, RED, RESET);
		scanf("%d", play_switch);
		if(*play_switch == 1 || *play_switch == 2){ // 1 - Yes; 2 - No
			break;
		} else{
			printf("\n%sError:%s Please choose between 'Yes' (1) or 'No' (2).", BRED, RESET);
		}
	}
}

void askBetAmount(int *bet, int *balance){
	while(true)
	{
		printf("\nPlace your bet!\n>>> ");
		scanf("%d", bet);
		// Stop case: Bet is within balance
		if(*bet <= *balance && *bet > 0){ 
			break;
		// Error: Bet larger than balance
		} else if (*bet > *balance && *bet > 0){
			printf("\nError: Insufficient! (Bet: %d | Balance: %d)", *bet, *balance);
		} else{
			printf("\nError: Invalid input Bet must be greater than 0! (Bet: %d)", *bet);
		}
	}
}

void askColorGuess(int *color_choice){
	while(true){
		printf("\n\nPick one color to bet on:"
				"\n1. Red\n2. Green\n3. Yellow\n4. Blue\n5. Magenta\n6. Cyan\n>>> "
		);
		scanf("%d", color_choice);
		// Stop case: Valid option within color choice
		if(*color_choice > 0 && *color_choice <= COLOR_CHOICES){
			(*color_choice)--; break; // Decrement for index syntax and random color comparison
		} else{
			printf("Error: Invalid input! (Must be between 1 and %d)", COLOR_CHOICES);
		}
	}
}

void chooseRandomColor(int random_colors[CUBE_COUNT], char colors[COLOR_CHOICES][COLOR_CODE_WIDTH], 
	int user_choice, int *correct_guesses){
	for(int i = 0; i<CUBE_COUNT; i++){
		// Chooses random color for the ith cube
		random_colors[i] = rand()%COLOR_CHOICES;
		if(random_colors[i] == user_choice){
			(*correct_guesses)++; //Increment if user guess the same as random color 
		}
		printf("\nCube %d | Color: %d\n", i+1, random_colors[i]); // Debug
		printCube(colors, CUBE_HEIGHT, random_colors[i]);
		SLEEP(1500);
	}
}

void updatePlayerStatistics(int *balance, int *wins, int *bet, int correct_guesses){
	// Shows guesses for playthrough
	printf("\n\nCorrect Guesses: %d", correct_guesses);
	switch(correct_guesses){
		case 1:  
			*bet *= MULTIPLIER_1;
			break;
		case 2:
			*bet *= MULTIPLIER_2;
			break; 
		case 3:
			*bet *= MULTIPLIER_3;
			break;
		default: 
			*bet *= -1;
			break;
	} 
	
	*balance += *bet; // Updates balance 

	if(correct_guesses > 0){
		(*wins)++; // Increments color game wins
		printf("\n\nCongratulations! You got %d correct and won %d!", correct_guesses, *bet);
	} else{
		printf("\n\nYou lost! You are now %d poorer!", *bet*-1);
	}
}