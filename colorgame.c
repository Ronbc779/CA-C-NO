#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "casino.h"

void print_cube(char colors[][9], int cube_size, int color_choices, int chosen_color);

void playColorGame(User *user){
	int color_choices = 7;
	// Fetches ANSI color codes for cube faces and reset escape code.
	char colors[7][9] = {
		RED, GRN, YEL, 
		BLU, MAG, CYN, RESET
	};
	
	int cube_size = 10; int cubes = 3; 
	int random_colors[cubes];
	
	for(int i = 0; i<cubes; i++){
		int colors_only = color_choices-1;
		random_colors[i] = rand()%colors_only;
		printf("\nCube %d | Color: %d\n", i+1, random_colors[i]);
		print_cube(colors, cube_size, color_choices, random_colors[i]);
	}
}

void print_cube(char colors[][9], int cube_size, int color_choices, int chosen_color){
	printf("%s", colors[chosen_color]);
	for(int i = 0; i < cube_size; i++){
		for(int j = 0; j < cube_size*2; j++){
			printf("X");
		}
		printf("\n");
	}

	printf("%s", colors[color_choices-1]);
}
