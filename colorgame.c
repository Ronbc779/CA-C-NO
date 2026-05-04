#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "casino.h"

#define COLOR_CHOICES 6
#define COLOR_CODE_WIDTH 9
#define CUBE_HEIGHT 10
#define CUBE_COUNT 3

void print_cube(char colors[COLOR_CHOICES][COLOR_CODE_WIDTH], int cube_size, int chosen_color);

void playColorGame(User *user){
	// Fetches ANSI color codes for cube faces and reset escape code.
	char colors[COLOR_CHOICES][COLOR_CODE_WIDTH] = {
		RED, GRN, YEL, 
		BLU, MAG, CYN
	};
	
	int prompt_play = 1; // Game loop
	while(prompt_play == 1){
		int random_colors[CUBE_COUNT]; 	// Storage of random colors for comparison
		int bet; int user_color;
		printf("\n********COLOR GAME********"
				"\n1. Pick one color from the list"
				"\n2. Wait for the roll to happen and see if you're lucky! For hits:"
				"\n\ta. One (1) color: x1.5"
				"\n\tb. Two (1) colors: x2.0"	
				"\n\tc. Three (3) colors: x3.0"	
				"\n3. Minimum bet: 50 coins"
		);
		while(true){
			printf("\n=============");
			printf("\nWould you like to play?\n1. Yes\n2. No\n>> ");
			scanf("%d", &prompt_play);
			if(prompt_play == 1 || prompt_play == 2){
				break;
			} else{
				printf("\nError: Please choose between 'Yes' (1) or 'No' (2).");
			}
		}
		for(int i = 0; i<CUBE_COUNT; i++){
		// Chooses random color for the ith cube
		random_colors[i] = rand()%COLOR_CHOICES;
		printf("\nCube %d | Color: %d\n", i+1, random_colors[i]);
		print_cube(colors, CUBE_HEIGHT, random_colors[i]);
		}
	}
	
	
}

void print_cube(char colors[COLOR_CHOICES][COLOR_CODE_WIDTH], int cube_size, int chosen_color){
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
