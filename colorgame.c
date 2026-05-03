#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
	int random_colors[CUBE_COUNT];
	
	for(int i = 0; i<CUBE_COUNT; i++){
		// Chooses random color for the ith cube
		random_colors[i] = rand()%COLOR_CHOICES;
		printf("\nCube %d | Color: %d\n", i+1, random_colors[i]);
		print_cube(colors, CUBE_HEIGHT, random_colors[i]);
	}
}

void print_cube(char colors[][9], int cube_size, int chosen_color){
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
