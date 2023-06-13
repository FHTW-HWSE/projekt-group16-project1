#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "seatAssignment.h"


TEST_CASE("Create table") {
    // Test case 1: When there are 10 students
    createTable(10);
    // Verify the generated table visually or by checking specific cell values

    // Test case 2: When there are 20 students
    createTable(20);
    // Verify the generated table visually or by checking specific cell values

    // Test case 3: When there are 30 students
    createTable(30);
    // Verify the alert and generated table visually or by checking specific cell values
}

TEST_CASE("Check username") {
    // Test case 1: When the username exists
    REQUIRE(checkUsername("ic22b090") == 1);

    // Test case 2: When the username does not exist
    REQUIRE(checkUsername("ic22b015") == 0);
}

TEST_CASE("Personal seat") {
    // Test case 1: When the username exists
    personalSeat("ic22b090");

    // Test case 2: When the username does not exist
    personalSeat("ic22b022");
}

TEST_CASE("Add user") {
    // Test case 1: Adding a new user
    addUser("ic22b015");
    // Verify if the user is added to the users.csv and username.csv files

    // Test case 2: Adding a user with an existing username
    addUser("ic22b090");
    // Verify if the user already exists and is not added to the users.csv and username.csv files   
}
TEST_CASE("Check neighbors") {
    // Test case 1: Existing user with neighbors
    // The user "ic22b090" is located at row 1, column 1
    // Direct neighbors: (row 2, column 2, ic22b094)
    // Indirect neighbors: (row 3, column 3, ic22b091) 
    std::cout << "Test case 1:\n";
    isNeighbor("ic22b090");

    // Test case 2: Existing user without neighbors
    // The user "ic22b015" is located at row 6 column 2
    //Direct neighbors: (row 5, column 3, ic22b107) and (row 5, column 5, ic22b108)
    //Indirect neighbors: (row 6, column 2, ic22b88)
    std::cout << "Test case 2:\n";
    isNeighbor("ic22b015");

    // Test case 3: Non-existing user
    // The user "ic22b999" does not exist in the database
    //Expecting: User ic22b999 not found
    std::cout << "Test case 3:\n";
    isNeighbor("ic22b999");
}



