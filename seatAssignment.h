#include <stdbool.h>
#ifndef GRUPPE16_1_2_SEATASSIGNMENT_H
#define GRUPPE16_1_2_SEATASSIGNMENT_H

#define MAX_ROWS 6
#define MAX_COLS 8
#define MAX_USERNAME_LENGTH 100

// Function to count the number of students
int countStudents();


void createTable(int totalStudents);
// Function to check if a username exists in the users.csv file
int checkUsername(const char* username);

// Function to assign a personal seat to a student
void personalSeat(const char* username);

// Function to add a new user to the users.csv file
void addUser(const char* username);

//Function to check if username laready exists in file
bool isUsernameExisting(const char* username);

// Function to check if two students are neighbors
void isNeighbor(const char* username);

void printUserID(int row, int col);


#endif //GRUPPE16_1_2_SEATASSIGNMENT_H
