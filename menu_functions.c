#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int pin, balance, bj, sm, roul, guess, total;
} User;

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
    int balance, bj_wins, sm_wins, roulette_wins, guess_wins, total_wins;

    while (fscanf(fp, "%s %d %d %d %d %d %d %d",
                  temp_name, &existing_pin,
                  &balance, &bj_wins, &sm_wins, &roulette_wins, &guess_wins, &total_wins) != EOF) {

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

int verify(char name[], int *pin, int *balance, int *bj_wins, int *sm_wins, int *roulette_wins, int *guess_wins, int *total_wins) {
    FILE *fp = fopen("gamblers.txt", "r");

    char temp_name[50];
    int temp_pin, temp_balance, temp_bj, temp_sm, temp_roulette, temp_guess,  temp_total;

    printf("\n=== VERIFICATION ===\n");
    printf("Enter name: ");
    scanf("%s", name);

    printf("Enter PIN: ");
    scanf("%d", pin);

    while (fscanf(fp, "%s %d %d %d %d %d %d %d",
                  temp_name, &temp_pin,
                  &temp_balance, &temp_bj, &temp_sm, &temp_roulette, &temp_guess, &temp_total) != EOF) {

        //checks if same name with the current line in file
        if (strcmp(name, temp_name) == 0 && *pin == temp_pin) {
            
            *balance = temp_balance;
            *bj_wins = temp_bj;
            *sm_wins = temp_sm;
            *roulette_wins = temp_roulette;
            *guess_wins = temp_guess;
            *total_wins = temp_total;

            fclose(fp);
            printf("Verify successful!\n");
            return 1;
        }
    }

    fclose(fp);
    printf("Invalid credentials.\n");
    return 0;
}

void saveUser(char name[], int pin, int balance, int bj_wins, int sm_wins, int roulette_wins, int *guess_wins, int total_wins) {
    FILE *fp = fopen("gamblers.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    char temp_name[50];
    int temp_pin, temp_balance, temp_bj, temp_sm, temp_roulette, temp_guess,  temp_total;

    //goes through file line by line
    while (fscanf(fp, "%s %d %d %d %d %d %d %d",
                temp_name, &temp_pin,
                &temp_balance, &temp_bj,
                &temp_sm, &temp_roulette, &temp_guess, 
                &temp_total) != EOF) 
    {

        if (strcmp(name, temp_name) == 0 && pin == temp_pin) {
            //checks if name and pin matches then writes the updated values
            fprintf(temp, "%s %d %d %d %d %d %d %d\n",
                    name, pin, balance, bj_wins, sm_wins, roulette_wins, temp_guess, total_wins);
        } else {
            //not the right one so copies the same values
            fprintf(temp, "%s %d %d %d %d %d %d %d\n",
                    temp_name, temp_pin, temp_balance, temp_bj, temp_sm, temp_roulette, temp_guess, temp_total);
        }
    }

    fclose(fp);
    fclose(temp);

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
           &users[count].bj, &users[count].sm, &users[count].roul, &users[count].guess, &users[count].total) != EOF) {
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
                case 1: val1 = users[j].bj; val2 = users[j+1].bj; break;
                case 2: val1 = users[j].sm; val2 = users[j+1].sm; break;
                case 3: val1 = users[j].roul; val2 = users[j+1].roul; break;
                case 4: val1 = users[j].guess; val2 = users[j+1].guess; break;
                case 5: val1 = users[j].total; val2 = users[j+1].total; break;
                case 6: val1 = users[j].balance; val2 = users[j+1].balance; break;
                default: val1 = users[j].total; val2 = users[j+1].total; break;
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
            int display = (choice == 1) ? users[i].bj :
                        (choice == 2) ? users[i].sm :
                        (choice == 3) ? users[i].roul : 
                        (choice == 4) ? users[i].guess : users[i].total;
                            
            printf("%-15s | %-10d\n", users[i].name, display);
        }
    }
    
}