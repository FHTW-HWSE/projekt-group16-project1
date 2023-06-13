#include <stdio.h>
#include <string.h>
#include "seatAssignment.h"


void createTable(int totalStudents) {
    // Check if there are more than 24 students
    if (totalStudents > 24) {
        printf("Alert: Only 24 students can participate in this exam.\n");
        totalStudents = 24;  // Set the total number of students to 24
    }

    // Calculate the number of "X" cells per row
    int xCellsPerRow = MAX_COLS / 2;

    // Calculate the number of rows needed to accommodate all students
    int requiredRows = (totalStudents + xCellsPerRow - 1) / xCellsPerRow;

    // Adjust the number of rows to fit within MAX_ROWS
    int rows = (requiredRows <= MAX_ROWS) ? requiredRows : MAX_ROWS;

    // Print the top line of the table
    for (int j = 0; j < MAX_COLS; j++) {
        printf("+-----");
    }
    printf("+\n");

    // Display the table rows
    for (int i = 0; i < rows; i++) {
        // Print the cells of the row
        for (int j = 0; j < MAX_COLS; j++) {
            // Check if the current cell should be marked with "X"
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) {
                // Check if there are more students to mark
                if (totalStudents > 0) {
                    printf("|  X  ");
                    totalStudents--;
                } else {
                    printf("|     ");
                }
            } else {
                printf("|     ");
            }
        }
        printf("|\n");

        // Print the separator line between rows
        for (int j = 0; j < MAX_COLS; j++) {
            printf("+-----");
        }
        printf("+\n");
    }

    // Open the CSV file for reading
    FILE *file = fopen("../database/username.csv", "r");
    if (file == NULL) {
        printf("Error: Unable to open file\n");
        return;
    }

    // Open a temporary file for writing the updated CSV data
    FILE *tempFile = fopen("../database/temp.csv", "w");
    if (tempFile == NULL) {
        printf("Error: Unable to open temporary file\n");
        fclose(file);
        return;
    }

    // Read and update the CSV data
    char student[100];
    int currentRow = 1;
    int currentCol = 1;
    int xCount = 0;

    while (fgets(student, sizeof(student), file) != NULL) {
        // Remove the newline character from the student string
        //int len = strlen(student);
        if (student[strlen(student)-1] == '\n') {
            student[strlen(student)-1] = '\0';
        }
       
    
        // Write the student data to the temporary file with row and column placement
        fprintf(tempFile, "%s,%d,%d\n", student, currentRow, currentCol);

        // Increment the xCount and adjust the row and column placement
        xCount++;
        currentCol += 2;

        if (xCount % xCellsPerRow == 0) {
            currentRow++;
            currentCol = (currentRow % 2 == 1) ? 1 : 2;
        }

        // Reset the row and column placement if they exceed the maximum values
        if (currentRow > rows) {
            currentRow = 1;
            currentCol = 1;
        }
    }

    // Close the files
    fclose(file);
    fclose(tempFile);

    // Replace the original CSV file with the temporary file
    remove("../database/users.csv");
    rename("../database/temp.csv", "../database/users.csv");
}

int countStudents() {
    FILE *file = fopen("../database/username.csv", "r");
    if (file == NULL) {
        printf("Error: Unable to open file\n");
        return -1;
    }

    // Check if the file is empty
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fclose(file);
        return 0;
    }

    // If the file is not empty, count the students
    fseek(file, 0, SEEK_SET);
    int count = 0;
    char line[100];

    // Skip the header line
    if (fgets(line, sizeof(line), file) == NULL) {
        // File is empty (excluding the header line)
        fclose(file);
        return 0;
    }

    // Count the remaining lines (students)
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }

    fclose(file);
    return count;
}

int checkUsername(const char* username) {
    // Open the CSV file for reading
    FILE* file = fopen("../database/username.csv", "r");
    if (file == NULL) {
        printf("Error: Unable to open file\n");
        return 0;
    }

    // Read and compare each line in the CSV file
    char line[MAX_USERNAME_LENGTH];
    //while (fgets(line, MAX_USERNAME_LENGTH, file) != NULL) {
        // Remove the newline character from the line
        /*int len = strlen(line);
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }*/

        // Extract the username from the line
        fscanf(file, "%[^\n]", line);
        
        // Compare the extracted username with the input username
        if (strncmp(username, line, 8) == 0) {
            fclose(file);
            return 1;  // Username exists
        }
    //}

    fclose(file);
    return 0;  // Username not found
}




void personalSeat(const char *username) {
    FILE* file = fopen("../database/users.csv", "r");
    if (file == NULL) {
        printf("Error: Unable to open file\n");
        return;
    }

    char line[MAX_USERNAME_LENGTH + 10];
    int row, col;
    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove the newline character from the line
        /*int len = strlen(line);
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }*/

        // Extract username, row, and column from the line
        char csvUsername[MAX_USERNAME_LENGTH];
        sscanf(line, "%[^,],%d,%d", csvUsername, &row, &col);

        // Compare the extracted username with the provided username
        if (strncmp(username, csvUsername,8) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("User '%s' is seated at row %d, column %d\n", username, row, col);

        // Print the table with the user's seat marked
        for (int i = 1; i <= MAX_ROWS; i++) {
            for (int j = 1; j <= MAX_COLS; j++) {
                if (i == row && j == col) {
                    printf("|  X  ");
                } else {
                    printf("|     ");
                }
            }
            printf("|\n");

            // Print the separator line between rows
            for (int j = 0; j < MAX_COLS; j++) {
                printf("+-----");
            }
            printf("+\n");
        }
    } else {
        printf("User '%s' not found\n", username);
    }
}

bool isUsernameExisting(const char* username) {
    // Open the username.csv file for reading
    FILE* usernameFile = fopen("../database/username.csv", "r");
    if (usernameFile == NULL) {
        printf("Error: Unable to open username.csv file\n");
        return false;
    }

    // Check if the username already exists
    char existingUsername[100];
    while (fscanf(usernameFile, "%s\n", existingUsername) == 1) {
        if (strncmp(existingUsername, username,8) == 0) {
            fclose(usernameFile);
            return true;
        }
    }

    fclose(usernameFile);
    return false;
}

void addUser(const char* username) {
    //Check if username already exists
    if (isUsernameExisting(username)) {
        printf("Username '%s' already exists\n", username);
        return;
    }
    
    // Open the users.csv file for reading
    FILE* usersFile = fopen("../database/users.csv", "r");
    if (usersFile == NULL) {
        printf("Error: Unable to open users.csv file\n");
        return;
    }

    // Open the username.csv file for appending
    FILE* usernameFile = fopen("../database/username.csv", "a");
    if (usernameFile == NULL) {
        printf("Error: Unable to open username.csv file\n");
        fclose(usersFile);
        return;
    }

    // Read the existing user data and find the last seat position
    char csvUsername[100];
    int row, col;
    int lastRow = 0;
    int lastCol = 0;

    while (fscanf(usersFile, "%[^,], %d, %d\n", csvUsername, &row, &col) == 3) {
        lastRow = row;
        lastCol = col;
    }

    fclose(usersFile);

    // Calculate the new seat position based on the last seat position
    int newRow = lastRow;
    int newCol = lastCol + 2;

    if (newCol > MAX_COLS) {
        newRow++;
        newCol = (newRow % 2 == 1) ? 1 : 2;
    }

    // Write the new user data to the users.csv file
    FILE* appendFile = fopen("../database/users.csv", "a");
    if (appendFile == NULL) {
        printf("Error: Unable to open users.csv file\n");
        fclose(usernameFile);
        return;
    }
    fprintf(appendFile, "%s, %d, %d\n", username, newRow, newCol);
    fclose(appendFile);

    // Write the new username to the username.csv file
    fprintf(usernameFile, "%s\n", username);
    printf("New user added successfully!\n");
    fclose(usernameFile);
    
}

void isNeighbor(const char* username) {
    FILE* file = fopen("../database/users.csv", "r");
    if (file == NULL) {
        printf("Error: Unable to open file\n");
        return;
    }

    char csvUsername[MAX_USERNAME_LENGTH];
    int row, col;
    int found = 0;

    while (fscanf(file, "%[^,],%d,%d\n", csvUsername, &row, &col) == 3) {
        if (strncmp(username, csvUsername,8) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("The direct neighbors are the following:\n");

        if (row - 1 >= 1 && col - 1 >= 1) {
            printf("Direct neighbor at row %d, column %d: ", row - 1, col - 1);
            printUserID(row - 1, col - 1);
            printf("\n");
        }
        if (row - 1 >= 1 && col + 1 <= 8) {
            printf("Direct neighbor at row %d, column %d: ", row - 1, col + 1);
            printUserID(row - 1, col + 1);
            printf("\n");
        }
        if (row + 1 <= 6 && col - 1 >= 1) {
            printf("Direct neighbor at row %d, column %d: ", row + 1, col - 1);
            printUserID(row + 1, col - 1);
            printf("\n");
        }
        if (row + 1 <= 6 && col + 1 <= 8) {
            printf("Direct neighbor at row %d, column %d: ", row + 1, col + 1);
            printUserID(row + 1, col + 1);
            printf("\n");
        }

        printf("The indirect neighbors are the following:\n");
        if (col - 2 >= 1) {
            printf("Indirect neighbor at row %d, column %d: ", row, col - 2);
            printUserID(row, col - 2);
            printf("\n");
        }
        if (col + 2 <= 8) {
            printf("Indirect neighbor at row %d, column %d: ", row, col + 2);
            printUserID(row, col + 2);
            printf("\n");
        }
    } else {
        printf("User '%s' not found\n", username);
    }
}

void printUserID(int row, int col) {
    FILE* file = fopen("../database/users.csv", "r");
    if (file == NULL) {
        printf("Error: Unable to open file\n");
        return;
    }

    char csvUsername[MAX_USERNAME_LENGTH];
    int csvRow, csvCol;

    while (fscanf(file, "%[^,], %d, %d\n", csvUsername, &csvRow, &csvCol) == 3) {
        if (csvRow == row && csvCol == col) {
            printf("%s", csvUsername);
            break;
        }
    }

    fclose(file);
}
