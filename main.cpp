#include <stdio.h>
#include <string.h>
#include "seatAssignment.h"
#include <stdlib.h>



int main() {
    int totalStudents = countStudents();
    printf("Total Students: %d\n", totalStudents);

    createTable(totalStudents);

    char username[MAX_USERNAME_LENGTH];
    char csvFilePath[MAX_USERNAME_LENGTH] ="../database/username.csv";

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
/*
    if (username[strlen(username) - 1] == '\n') {
            username[strlen(username) - 1] = '\0';}
            */
    //username[strcspn(username, "\n")] = '\0';  // Remove the newline character
    
    if (checkUsername(username)) {
        printf("Login successful!\n");
        //printf("Show the whole class:\n");
        //createTable(totalStudents);
        printf("Where is the user seated?\n");
        username[strcspn(username, "\n")] = '\0';  // Remove the newline character

        personalSeat(username);

        char hadCorona;

        printf("Did you have corona? (y/n): ");
        scanf(" %c", &hadCorona);

        if (hadCorona == 'y' || hadCorona == 'Y') {
            printf("%s HAS CORONA.\n", username);
            isNeighbor(username);
        } else {
            printf("Good for you!\n");
        }


    } else {
        printf("Invalid username!\n");
    }
    char addNewUser;
    printf("Do you want to add a new user? (y/n): ");
    scanf(" %c", &addNewUser);

    if (addNewUser == 'y' || addNewUser == 'Y') {
        char newUsername[MAX_USERNAME_LENGTH];
        printf("Enter the new username: ");
        scanf(" %[^\n]", newUsername);

        addUser(newUsername);
    }
    return 0;
}

