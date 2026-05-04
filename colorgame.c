#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "casino.h"

#define COLOR_CHOICES 6
#define COLOR_CODE_WIDTH 9
#define CUBE_HEIGHT 10
#define CUBE_COUNT 3

void printCube(char colors[COLOR_CHOICES][COLOR_CODE_WIDTH], int cube_size, int chosen_color);

void playColorGame(User *user){
	// Fetches ANSI color codes for cube faces.
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
	);
	
	while(true){ // First run for gameplay loop
		printf("\n\n============="); 
		printf("\nWould you like to play?\n1. Yes\n2. No\n>> ");
		scanf("%d", &prompt_play);
		if(prompt_play == 1 || prompt_play == 2){ // 1 - Yes; 2 - No
			break;
		} else{
			printf("\nError: Please choose between 'Yes' (1) or 'No' (2).");
		}
	}

	while(prompt_play == 1){
		printf("\n\nName: %s | Balance: %d", user->name, user->balance); 
		
		int random_colors[CUBE_COUNT]; 	// Storage of random colors for comparison
		int bet; int user_color; int *balance = &user->balance; int correct_guesses; 
		
		while(true){
			printf("\nPlace your bet!\n>>> ");
			scanf("%d", &bet);
			// Stop case: Bet is within balance
			if(bet <= *balance && bet > 0){ 
				break;
			// Error: Bet larger than balance
			} else if (bet > *balance && bet > 0){
				printf("\nError: Insufficient! (Bet: %d | Balance: %d)", bet, *balance);
			} else{
				printf("\nError: Invalid input Bet must be greater than 0! (Bet: %d)", bet);
			}
		}

		while(true){
			printf("\n\nPick one color to bet on:"
				   "\n1. Red\n2. Green\n3. Yellow\n4. Blue\n 5. Magenta\n 6. Cyan"
			);
			scanf("%d", &user_color);
			if(user_color > 0 && user_color <= COLOR_CHOICES){
				break;
			} else{
				printf("Error: Invalid input! (Must be between 1 and %d)", COLOR_CHOICES);
			}
			break;
		}

		for(int i = 0; i<CUBE_COUNT; i++){
			// Chooses random color for the ith cube
			random_colors[i] = rand()%COLOR_CHOICES;
			if(random_colors[i] == user_color){
				correct_guesses++
			}
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
