//
//  Purpose: Solves sudoku boards of desired size chosen by the user
//
//  Backround info on algorithm: This program uses backtracking to solve the sudoku puzzle by checking multiple times if numbers are in valid positions and placing them and also removing them if they do not meet the sudoku requiments. This is done by checking the row, column, and box requirments (no repeated numbers in any of these) multiple times as numbers are added by the program.
//
//
//  Programer: Nikhil Sinclair
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int rowCheck(int** chart, int size);
int colCheck(int** chart, int size);
int boxCheck(int** chart, int size);
int boardCheck(int** chart, int size);
bool solver(int** chart, int size);
int empty_locator(int** chart, int size);
void insertNumber(int** chart, int position, int val, int size);
int successfulChoice(int** chart, int spot, int val, int size);


/*
 Purpose: Checks rows of sudoku board to see if a number can be used depending on if it had already been used
 */

int rowCheck(int** chart, int size) {
    
    for(int row = 0; row < size; row++) {
        
        int arr[size]; // stores all values of a given row on the sudoku board
        
        // creates an array that is a copy of a row in the sudoku chart
        for(int col = 0; col < size; col++) {
            arr[col] = chart[row][col];
        }
        
        sort(arr, arr+size); // sorts array from smallest values to largest
        
        //checks to see if there are any duplicate numbers in row
        for(int col = 1; col < size; col++) {
            
            // contiues if there is an empty slot (recall 0 is empty spot)
            if(arr[col] == 0) {
                continue;
            }
            
            // returns false if there is a number repeated in the row
            if(arr[col] == arr[col - 1]) {
                return false;
            }
        }
        
    }
    
    return true; // if no repeated integers are in the row
    
}


/*
 Purpose: Checks columns of sudoku board to see if a number can be used depending on if it had already been used
 */

int colCheck(int** chart, int size) {
    
    for(int col = 0; col < size; col++) {
        
        int arr[size]; // stores integers of a column in the sudoku board
        
        // creates an array that is a copy of a column in the sudoku chart
        for(int row = 0; row < size; row++) {
            
            arr[row] = chart[row][col]; // assigns values from column to array
            
        }
            
        sort(arr, arr+size); // sorts array from smallest values to largest
            
        // checks to see if there are any duplicate numbers in column
        for(int row = 1; row < size; row++) {
            
            // contiues if empty slot (recall empty slot is 0)
            if(arr[row] == 0) {
                continue;
            }
            
            // returns false if there are duplicate integers in a column
            if(arr[row] == arr[row - 1]) {
                return false;
            }
        }
            
    }
        
    return true; // if no duplicate integers in column
        
}

/*
 Purpose: Checks boc of sudoku board to see if a number can be used depending on if it had already been used
 */

int boxCheck(int** chart, int size) {
    
    int boxSize = sqrt(size); // calculates size of boxes on sudoku board
    
    for (int row = 0; row < size; row += boxSize) {
        
        for (int col = 0; col < size; col += boxSize) {
            
            int arr[size]; // creates array for all elements within a box
            int num = 0; // used to assign values of box to array
            
            // assigns values of box to array
            for (int i = 0; i < boxSize; i++) {
                for (int j = 0; j < boxSize; j++) {
                    arr[num++] = chart[row + i][col + j];
                }
            }
            
            sort(arr, arr + size); // sorts array from smallest values to largest
            
            
            for (int col = 1; col < size; col++) {
                
                //conitues to excecute loop if an empty slot is found
                if (arr[col] == 0) {
                    continue;
                }
                
                // checks if a number has be used twice in a box and returns false if repeated
                if (arr[col] == arr[col - 1]) {
                    return false;
                }
            }
        }
    }
    return true; // if no repeated inetgers in box
}


/*
 Purpose: Checks if board is completed
 */

int boardCheck(int** chart, int size) {
    return rowCheck(chart, size) && colCheck(chart, size) && boxCheck(chart, size); // will be true if all checks are satisfied
}

int empty_locator(int** chart, int size) {
    
    int val = 0; // varibale which stores a value that provides the coordinates of empty space
    
    // finds empty spots on entire sudoku board
    while(val < size * size) {
    
        //checks spaces to find empty slot on board
        if(chart[val/size][val%size] == 0) {
            return val;
        }
        
        val++;
    }
    
    return -1; // returns -1 if board has no empty spots (board is full or completed)
    
}

/*
 Purpose: Inserts integer to a position on the sudoku board
 */

void insertNumber(int** chart, int position, int val, int size) {
    
    chart[position/size][position%size] = val; // inserts a valid number to a position on the board
    
}

/*
 Purpose: Checks if a position for a number is correct and works with the other elements of the board
 */

int successfulChoice(int** chart, int spot, int val, int size) {
    
    insertNumber(chart, spot, val, size);
    
    // checks if position of number is valid for the sudoku board
    if(boardCheck(chart, size)) {
        return true; // since number is placed in a valid spot
    }
    
    
    // checks if the chosen position does not work
    else {
        insertNumber(chart, spot, 0, size); // if value does not work in position, the spot will still have a 0 in it
        return false; // since number is not supposed to be placed in this position
    }
    
}


bool solver(int** chart, int size) {
    
    int emptySpace = empty_locator(chart, size); // locates empty space using a single variable which related to both the x and y coordinates of the chart

    // if there are no empty spaces board is complete, so board is solved (return true)
    if(emptySpace == -1) {
        return true; // if board in completed return true
    }

    // Below variable n is used as the inputed number to the board. Different values of n are tried until the right value is found to suit the board
    for(int n = 1; n <= size; n++) {
        
        if (successfulChoice(chart, emptySpace, n, size)) {
            
            // statement below allows for backtracking
            if (solver(chart, size)) {
                return true;
                }
            
            // creates empty slot if mistake was made for placment of integer
            else {
                insertNumber(chart, emptySpace, 0, size);
                }
            }
        }

    return false; // board was not solved
}


int main() {
    
    int size; // stores side length of board
    
    std::cout << "What is the side lengths of your sudoku board?\n" << std::endl;
    std::cin >> size;
    
    double sqrtVal = sqrt(size);
    
    int integerSqrt = static_cast<int>(sqrtVal); // used to see if size is valid, since the size should be able to be squarooted
    
    // condiiton to see if board is valid size
    if(integerSqrt * integerSqrt == size && size != 0) {
    
        // creates sudoku board
        int** chart = new int*[size];
        for (int i = 0; i < size; i++) {
                chart[i] = new int[size];
            }

        
        // Allows user to input their specfic sudoku board into program
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                std::cout << "Enter value for row " << row + 1 << ", column " << col + 1 << " (enter 0 if it is blank): ";
                std::cin >> chart[row][col];
            }
        }
        
        
        
        if(solver(chart, size)) {
            
            // Print the completed sudoku board
            for (int row = 0; row < size; row++) {
                for (int col = 0; col < size; col++) {
                    std::cout << chart[row][col] << "\t";
                }
                std::cout << std::endl;
            }
            
        }
        
        
        else {
            std::cout << "Error, the board you have entered is insolvable" << std::endl;
        }
        
        //Deleting chart entries to save memory
        for (int row = 0; row < size; row++) {
            delete[] chart[row];
        }
        
        delete[] chart;
        
    }
    
    // if board is not a valid size
    else{
        std::cout << "Error the enetered size is not valid for a sudoku board" << std::endl;
    }
    
    
    
    return 0;
}
