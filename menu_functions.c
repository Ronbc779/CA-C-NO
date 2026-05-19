#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "casino.h"

void signUp(){
    FILE *fp = fopen("gamblers.txt", "a+");

    char name[50];
    printf("\n===== %sSIGN UP%s =====\n", BGRN, RESET);
    printf("Enter name: ");
    scanf("%s", name);

    // Check duplicate PIN
    rewind(fp);
    char temp_name[50];
    int balance, bj_wins, color_wins, roulette_wins, guess_wins, highlow_wins, hangman_wins, cloudnine_wins, total_wins;

    while (fscanf(fp, "%s %d %d %d %d %d %d %d %d %d",
                  temp_name,
                  &balance, &bj_wins, &color_wins, &roulette_wins, &guess_wins, &highlow_wins, &hangman_wins, &cloudnine_wins, &total_wins) != EOF) {

        if (strcmp(temp_name, name) == 0) {
            printf("%sUser already exists! Try another.%s\n", BRED, RESET);
            fclose(fp);
            return;
        }
    }

    // Save new user
    fprintf(fp, "%s %d %d %d %d %d %d %d %d %d\n", name, 100, 0, 0, 0, 0, 0, 0, 0, 0);
    fclose(fp);

    printf("\n%s*****Account created successfully!*****%s\n", GRN, RESET);
}

int verify(User *user) {
    FILE *fp = fopen("gamblers.txt", "r");

    User temp;

    printf("\n===== %sVERIFICATION%s =====\n", BGRN, RESET);
    printf("Enter name: ");
    scanf("%s", user->name);


    while (fscanf(fp, "%s %d %d %d %d %d %d %d %d %d",
                  temp.name, &temp.balance,
                  &temp.bj_wins, &temp.color_wins, &temp.roulette_wins,
                  &temp.guess_wins, &temp.highlow_wins, &temp.hangman_wins, &temp.cloudnine_wins, &temp.total_wins) != EOF) {

        //checks if same name with the current line in file
        if (strcmp(user->name, temp.name) == 0) {
            
            *user = temp;

            fclose(fp);
            printf("%sVerify successful! Welcome, %s.%s\n", BGRN, user->name, RESET);
            return 1;
        }
    }

    fclose(fp);
    printf("User not found.\n");
    return 0;
}

void saveUser(User *user) {
    FILE *fp = fopen("gamblers.txt", "r");
    FILE *temp_fp = fopen("temp.txt", "w");

    User temp;

    //goes through file line by line
    while (fscanf(fp, "%s %d %d %d %d %d %d %d %d %d",
                temp.name, &temp.balance,
                  &temp.bj_wins, &temp.color_wins, &temp.roulette_wins,
                  &temp.guess_wins, &temp.highlow_wins, &temp.hangman_wins, &temp.cloudnine_wins, &temp.total_wins) != EOF) 
    {

        if (strcmp(user->name, temp.name) == 0) {
            //checks if name and pin matches then writes the updated values
            fprintf(temp_fp, "%s %d %d %d %d %d %d %d %d %d\n",
                    user->name, user->balance,
                    user->bj_wins, user->color_wins, user->roulette_wins,
                    user->guess_wins, user->highlow_wins, user->hangman_wins, user->cloudnine_wins, user->total_wins);
        } else {
            //not the right one so copies the same values
            fprintf(temp_fp, "%s %d %d %d %d %d %d %d %d %d\n",
                    temp.name, temp.balance,
                    temp.bj_wins, temp.color_wins, temp.roulette_wins,
                    temp.guess_wins, temp.highlow_wins, temp.hangman_wins, temp.cloudnine_wins, temp.total_wins);
        }
    }

    fclose(fp);
    fclose(temp_fp);

    //remove old and rename new file
    remove("gamblers.txt");
    rename("temp.txt", "gamblers.txt");
}

void showLeaderboard() {
    FILE *fp = fopen("gamblers.txt", "r");
    if (!fp) {
        printf("No data found.\n");
        return;
    }

    User users[100];
    int count = 0;

    // Read all users into an array and count them
    while (fscanf(fp, "%s %d %d %d %d %d %d %d %d %d", 
           users[count].name, &users[count].balance,
           &users[count].bj_wins, &users[count].color_wins, &users[count].roulette_wins,
           &users[count].guess_wins, &users[count].highlow_wins, &users[count].hangman_wins, &users[count].cloudnine_wins, &users[count].total_wins) != EOF) {
        count++;
    }
    fclose(fp);

    int choice;
    //user chooses sorting filter
    printf("\n=== %sLEADERBOARD SELECTION %s===\n", BCYN, RESET);
    printf("1. Blackjack Wins\n2. Color Game Wins\n3. Roulette Wins\n4. Guess Game\n5. High Low Wins \n6. Hangman Wins\n7. Cloudnine wins\n8. Total Wins\n9. Total Earnings (Balance)\n>> ");
    scanf("%d", &choice);
    
    //change later  if we add more games/choices
    if(choice < 0 || choice > 9){
        printf("%sPlease input among the choices.%s\n", RED, RESET);
        return;
    }

    // Bubble Sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int val1, val2;
            //get the values needed by user's choice
            switch(choice) {
                case 1: val1 = users[j].bj_wins; val2 = users[j+1].bj_wins;
                    break;
                case 2: val1 = users[j].color_wins; val2 = users[j+1].color_wins;
                    break;
                case 3: val1 = users[j].roulette_wins; val2 = users[j+1].roulette_wins;  
                    break;
                case 4: val1 = users[j].guess_wins; val2 = users[j+1].guess_wins;     
                    break;
                case 5: val1 = users[j].highlow_wins; val2 = users[j+1].highlow_wins;
                    break;
                case 6: val1 = users[j].hangman_wins; val2 = users[j+1].hangman_wins;     
                    break;
                case 7: val1 = users[j].cloudnine_wins; val2 = users[j+1].cloudnine_wins;
                    break;
                case 8: val1 = users[j].total_wins; val2 = users[j+1].total_wins;
                    break;
                case 9: val1 = users[j].balance; val2 = users[j+1].balance;
                    break;
                default: val1 = users[j].total_wins; val2 = users[j+1].total_wins;
                    break;
            }
            
            //switch values if first is smaller
            if (val1 < val2) {
                User temp = users[j];
                users[j] = users[j+1];
                users[j+1] = temp;
            }
        }
    }
    if(choice == 9){
        printf("\n%s %-15s | %-10s %s\n", BWHT, "NAME", "BALANCE", RESET);
        printf("---------------------------\n");
        for (int i = 0; i < count; i++) {
            //gets user's wanted variable and assigns to display
            int display = users[i].balance;
                            
            printf("%-15s | %s%-10d%s\n", users[i].name, YEL, display, RESET);
        }
    }
    else{
        printf("\n%s%-15s | %-10s%s\n", BWHT, "NAME", "WINS", RESET);
        printf("----------------------------\n");
        for (int i = 0; i < count; i++) {
            //gets user's wanted variable and assigns to display
            int display = (choice == 1) ? users[i].bj_wins :
                        (choice == 2) ? users[i].color_wins :
                        (choice == 3) ? users[i].roulette_wins : 
                        (choice == 4) ? users[i].guess_wins : 
                        (choice == 5) ? users[i].highlow_wins : 
                        (choice == 6) ? users[i].hangman_wins : 
                        (choice == 7) ? users[i].cloudnine_wins : users[i].total_wins;
                            
            printf("%-15s | %s%-10d%s\n", users[i].name, GRN, display, RESET);
        }
    }
    
}