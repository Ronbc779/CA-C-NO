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

	// Storage of random colors for comparison
	while(true){
		int random_colors[CUBE_COUNT];
		printf("\n====== COLOR GAME ======="
				"\n1. Pick one color from the list"
				"\n2. Wait for the roll to happen, for hits:"
				"\n\ta. One (1) color: x1.5"
				"\n\tb. Two (1) colors: x2.0"	
				"\n\tc. Three (3) colors: x3.0"	
				"\n3. Minimum bet: 50 coins"
		);
		for(int i = 0; i<CUBE_COUNT; i++){
		// Chooses random color for the ith cube
		random_colors[i] = rand()%COLOR_CHOICES;
		printf("\nCube %d | Color: %d\n", i+1, random_colors[i]);
		print_cube(colors, CUBE_HEIGHT, random_colors[i]);
		}
		break;

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
