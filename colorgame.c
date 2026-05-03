#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "casino.h"

void print_cube(char colors[][9], int cube_size, int chosen_color);

void playColorGame(User *user){
	int color_choices = 6;
	// Fetches ANSI color codes for cube faces and reset escape code.
	char colors[6][9] = {
		RED, GRN, YEL, 
		BLU, MAG, CYN
	};
	
	// Sets cube height, number of cubes
	int cube_size = 10; int cubes = 3; 
	// Stores random colors for comparison
	int random_colors[cubes];
	
	for(int i = 0; i<cubes; i++){
		// Chooses random color for the ith cube
		random_colors[i] = rand()%color_choices;
		printf("\nCube %d | Color: %d\n", i+1, random_colors[i]);
		print_cube(colors, cube_size, random_colors[i]);
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
