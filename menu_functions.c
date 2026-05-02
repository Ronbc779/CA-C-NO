#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "casino.h"

void signUp(){
    FILE *fp = fopen("gamblers.txt", "a+");

    char name[50];
    int pin, existing_pin;

    printf("\n=== SIGN UP ===\n");
    printf("Enter name: ");
    scanf("%s", name);

    printf("Enter 4-digit PIN: ");
    scanf("%d", &pin);

    // Check duplicate PIN
    rewind(fp);
    char temp_name[50];
    int balance, bj_wins, color_wins, roulette_wins, guess_wins, total_wins;

    while (fscanf(fp, "%s %d %d %d %d %d %d %d",
                  temp_name, &existing_pin,
                  &balance, &bj_wins, &color_wins, &roulette_wins, &guess_wins, &total_wins) != EOF) {

        if (existing_pin == pin) {
            printf("PIN already exists! Try another.\n");
            fclose(fp);
            return;
        }
    }

    // Save new user
    fprintf(fp, "%s %d %d %d %d %d %d %d\n", name, pin, 100, 0, 0, 0, 0, 0);
    //nts: if name is yumeko, balance is 99999 and wins are 1000 frfr
    fclose(fp);

    printf("\n*****Account created successfully!*****\n");
}

int verify(User *user) {
    FILE *fp = fopen("gamblers.txt", "r");

    User temp;

    printf("\n=== VERIFICATION ===\n");
    printf("Enter name: ");
    scanf("%s", user->name);


    while (fscanf(fp, "%s %d %d %d %d %d %d %d",
                  temp.name, &temp.pin, &temp.balance,
                  &temp.bj_wins, &temp.color_wins, &temp.roulette_wins,
                  &temp.guess_wins, &temp.total_wins) != EOF) {

        //checks if same name with the current line in file
        if (strcmp(user->name, temp.name) == 0 && user->pin == temp.pin) {
            
            *user = temp;

            fclose(fp);
            printf("Verify successful!\n");
            return 1;
        }
    }

    fclose(fp);
    printf("Invalid credentials.\n");
    return 0;
}

void saveUser(User *user) {
    FILE *fp = fopen("gamblers.txt", "r");
    FILE *temp_fp = fopen("temp.txt", "w");

    User temp;

    //goes through file line by line
    while (fscanf(fp, "%s %d %d %d %d %d %d %d",
                temp.name, &temp.pin, &temp.balance,
                  &temp.bj_wins, &temp.color_wins, &temp.roulette_wins,
                  &temp.guess_wins, &temp.total_wins) != EOF) 
    {

        if (strcmp(user->name, temp.name) == 0 && user->pin == temp.pin) {
            //checks if name and pin matches then writes the updated values
            fprintf(temp_fp, "%s %d %d %d %d %d %d %d\n",
                    user->name, user->pin, user->balance,
                    user->bj_wins, user->color_wins, user->roulette_wins,
                    user->guess_wins, user->total_wins);
        } else {
            //not the right one so copies the same values
            fprintf(temp_fp, "%s %d %d %d %d %d %d %d\n",
                    temp.name, temp.pin, temp.balance,
                    temp.bj_wins, temp.color_wins, temp.roulette_wins,
                    temp.guess_wins, temp.total_wins);
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
    while (fscanf(fp, "%s %d %d %d %d %d %d %d", 
           users[count].name, &users[count].pin, &users[count].balance,
           &users[count].bj_wins, &users[count].color_wins, &users[count].roulette_wins,
           &users[count].guess_wins, &users[count].total_wins) != EOF) {
        count++;
    }
    fclose(fp);

    int choice;
    //user chooses sorting filter
    printf("\n--- LEADERBOARD SELECTION ---\n");
    printf("1. Blackjack Wins\n2. Slot Machine Wins\n3. Roulette Wins\n4. Guess Game\n5. Total Wins\n6. Total Earnings (Balance)\n>> ");
    scanf("%d", &choice);
    
    //change later  if we add more games/choices
    if(choice < 0 || choice > 6){
        printf("Please input among the choices.");
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
                case 5: val1 = users[j].total_wins; val2 = users[j+1].total_wins;     
                    break;
                case 6: val1 = users[j].balance; val2 = users[j+1].balance;
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
    if(choice == 6){
        printf("\n%-15s | %-10s\n", "NAME", "BALANCE");
        printf("---------------------------\n");
        for (int i = 0; i < count; i++) {
            //gets user's wanted variable and assigns to display
            int display = users[i].balance;
                            
            printf("%-15s | %-10d\n", users[i].name, display);
        }
    }
    else{
        printf("\n%-15s | %-10s\n", "NAME", "WINS");
        printf("----------------------------\n");
        for (int i = 0; i < count; i++) {
            //gets user's wanted variable and assigns to display
            int display = (choice == 1) ? users[i].bj_wins :
                        (choice == 2) ? users[i].color_wins :
                        (choice == 3) ? users[i].roulette_wins : 
                        (choice == 4) ? users[i].guess_wins : users[i].total_wins;
                            
            printf("%-15s | %-10d\n", users[i].name, display);
        }
    }
    
}