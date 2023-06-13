cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER "gcc")

find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)

set(TESTING TRUE)

if(NOT TESTING)
add_executable(seats10 main.cpp seatAssignment.cpp)

endif()

if(TESTING)
set(SOURCE_FILES tests.cpp seatAssignment.cpp)
    
    # Create an executable and link the Catch2 library
    add_executable(testseats10 ${SOURCE_FILES})
    target_link_libraries(testseats10 Catch2::Catch2)

endif(TESTING)