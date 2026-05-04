#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "casino.h"

#define COLOR_CHOICES 6
#define COLOR_CODE_WIDTH 9
#define CUBE_HEIGHT 10
#define CUBE_COUNT 3
#define MINIMUM_BET 50

void printCube(char colors[COLOR_CHOICES][COLOR_CODE_WIDTH], int cube_size, int chosen_color);

void playColorGame(User *user){
	// Fetches ANSI color codes for cube faces and reset escape code.
	char colors[COLOR_CHOICES][COLOR_CODE_WIDTH] = {
		RED, GRN, YEL, 
		BLU, MAG, CYN
	};
	
	int prompt_play; 

	// Prints rules and odds
	printf("\n********COLOR GAME********"
			"\n1. Pick one color from the list"
			"\n2. Wait for the roll to happen and see if you're lucky! For hits:"
			"\n\ta. One (1) color: x1.5"
			"\n\tb. Two (2) colors: x2.0"	
			"\n\tc. Three (3) colors: x3.0"	
			"\n3. Minimum bet: %d coins", MINIMUM_BET
	);
	
	while(true){ // First run for gameplay loop
		printf("\n============="); 
		printf("\nWould you like to play?\n1. Yes\n2. No\n>> ");
		scanf("%d", &prompt_play);
		if(prompt_play == 1 || prompt_play == 2){ // 1 - Yes; 2 - No
			break;
		} else{
			printf("\nError: Please choose between 'Yes' (1) or 'No' (2).");
		}
	}

	while(prompt_play == 1){
		printf("Username: %s | Balance: %d", user->name, user->balance); // Debug
		
		int random_colors[CUBE_COUNT]; 	// Storage of random colors for comparison
		int bet; int user_color; int *balance = &user->balance;
		
		while(true){
			printf("\nPlace your bet! (Minimum: %d)\n>>> ", MINIMUM_BET);
			scanf("%d", &bet);
			// Stop case: Valid bet and within balance
			if(bet >= MINIMUM_BET && bet <= *balance){ 
				break;
			// Error 1: User bet is less than minimum bet
			} else if(bet < MINIMUM_BET && bet<= *balance){ // 
				printf("\nError: Please enter a higher bet! (%d is less than %d)", bet, MINIMUM_BET);
			// Error 2: Insufficient balance
			} else{
				printf("\nError: Insufficient balance! (Bet: %d | Balance: %d)", bet, *balance);
			}
		}

		for(int i = 0; i<CUBE_COUNT; i++){
			// Chooses random color for the ith cube
			random_colors[i] = rand()%COLOR_CHOICES;
			printf("\nCube %d | Color: %d\n", i+1, random_colors[i]); // Debug
			printCube(colors, CUBE_HEIGHT, random_colors[i]);
		}

		while(true){ // Reprompt gameplay loop, same functionality
			printf("\n=============");
			printf("\nWould you like to play again?\n1. Yes\n2. No\n>> "); 
			scanf("%d", &prompt_play);
			if(prompt_play == 1 || prompt_play == 2){
				break;
			} else{
				printf("\nError: Please choose between 'Yes' (1) or 'No' (2).");
			}
		}
	} 
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
