#pragma once

#include <stdio.h>
#include "sudoku.h"

// Glossary of Sudoku Terms:
// https://en.wikipedia.org/wiki/Glossary_of_Sudoku

void print(int grid[]) // print the current state of the grid, for testing
{
    for(int i=0, j=0; i<81; ++i, ++j)
    {
        if(j == 9) // print a new line every row (9 values)
        {
            printf("\n");
            j = 0;
        }

        printf("%i ", grid[i]);        
    }
    printf("\n");
}

bool isValid(int grid[]) // checks that the grid does not violate Sudoku constraints, but does not check for solvability
{
    // we will check each group (row, column or box) and verify no number appears more than once
    int countOnes, countTwos, countThrees, countFours, countFives, countSixes, countSevens, countEights, countNines;

    /* --- CHECK ROWS ARE VALID --- */
    for(int i=0; i<73; i+=9)
    {
        countOnes = 0;
        countTwos = 0;
        countThrees = 0;
        countFours = 0;
        countFives = 0;
        countSixes = 0;
        countSevens = 0;
        countEights = 0;
        countNines = 0;

        for(int j=0; j<9; ++j)
        {
            switch (grid[i+j])
            {
            case 1:
                ++countOnes;
                break;
            case 2:
                ++countTwos;
                break;
            case 3:
                ++countThrees;
                break;
            case 4:
                ++countFours;
                break;
            case 5:
                ++countFives;
                break;
            case 6:
                ++countSixes;
                break;
            case 7:
                ++countSevens;
                break;
            case 8:
                ++countEights;
                break;
            case 9:
                ++countNines;
                break;            
            default: // 0 or junk value
                break;
            }
        }

        if(countOnes > 1 || countTwos > 1 || countThrees > 1
            || countFours > 1 || countFives > 1 || countSixes > 1
            || countSevens > 1 || countEights > 1 || countNines > 1) return false;
    }

    /* --- CHECK COLUMNS ARE VALID --- */
    for(int i=0; i<9; ++i)
    {
        countOnes = 0;
        countTwos = 0;
        countThrees = 0;
        countFours = 0;
        countFives = 0;
        countSixes = 0;
        countSevens = 0;
        countEights = 0;
        countNines = 0;

        for(int j=0; j<73; j+=9)
        {
            switch (grid[i+j])
            {
            case 1:
                ++countOnes;
                break;
            case 2:
                ++countTwos;
                break;
            case 3:
                ++countThrees;
                break;
            case 4:
                ++countFours;
                break;
            case 5:
                ++countFives;
                break;
            case 6:
                ++countSixes;
                break;
            case 7:
                ++countSevens;
                break;
            case 8:
                ++countEights;
                break;
            case 9:
                ++countNines;
                break;            
            default: // 0 or junk value
                break;
            }
        }

        if(countOnes > 1 || countTwos > 1 || countThrees > 1
            || countFours > 1 || countFives > 1 || countSixes > 1
            || countSevens > 1 || countEights > 1 || countNines > 1) return false;
    }

    /* --- CHECK BOXES ARE VALID --- */
    for(int i=0; i<55; i+=27) // the boxes on the left stack of the grid start at indices 0, 27 and 54
    {
        for(int j=0; j<7; j+=3) // e.g. if i=0 the three boxes in that band start at indices 0, 3 and 6
        {
            countOnes = 0;
            countTwos = 0;
            countThrees = 0;
            countFours = 0;
            countFives = 0;
            countSixes = 0;
            countSevens = 0;
            countEights = 0;
            countNines = 0;

            // navigate the indices within the box
            /* the below is a hack to yield k =  0,  1,  2, 
                                                 9, 10, 11, 
                                                18, 19, 20 */
                    
            for(int k=0; k<21; ++k)
            {
                // skip to next row of the box if necessary
                if(k==3) k = 9;
                if(k==12) k = 18;                

                switch (grid[i+j+k])
                {
                case 1:
                    ++countOnes;
                    break;
                case 2:
                    ++countTwos;
                    break;
                case 3:
                    ++countThrees;
                    break;
                case 4:
                    ++countFours;
                    break;
                case 5:
                    ++countFives;
                    break;
                case 6:
                    ++countSixes;
                    break;
                case 7:
                    ++countSevens;
                    break;
                case 8:
                    ++countEights;
                    break;
                case 9:
                    ++countNines;
                    break;            
                default: // 0 or junk value
                    break;
                }        
            }
            
            if(countOnes > 1 || countTwos > 1 || countThrees > 1
                || countFours > 1 || countFives > 1 || countSixes > 1
                || countSevens > 1 || countEights > 1 || countNines > 1) return false;
        }
    }    

    return true; // grid is valid if we made it here
}

bool bruteForceSolve(int grid[], int index = 0) // recursively try every value from 1 to 9 at the specified index and every empty cell onwards
// note: assumes the grid is a proper Sudoku, i.e. there is only one solution
{  
    while(index <= 81 && grid[index] != 0) ++index; //find the next empty cell

    if(index > 81) return true; // if we've filled all cells then this solution is correct!

    for(int i=1; i<=9; ++i)
    {
        grid[index] = i;

        if(!isValid(grid)) continue; // if this value is not valid, continue to the next one

        if(bruteForceSolve(grid, index + 1)) return true; // if all other empty cells can be filled, this value for grid[index] is correct!
    }

    // if no value from 1-9 is valid in this cell then the solution up to now is wrong
    grid[index] = 0; // remove the incorrect value, we'll try setting it again in another recursion
    return false; 
}

int fillGridFromFile(char *file, int grid[]) // writes the values from the file into the grid array and returns the count of empty cells
{
    int countUnsolved = 0;

    FILE *input;
    fopen_s(&input, file, "r");

    for(int i=0; i<81; ++i)
    {
        fscanf_s(input, "%d", &grid[i]);

        if(grid[i] == 0) ++countUnsolved;
    }

    fclose(input);

    return countUnsolved;
}

void writeGridToFile(char *file, int grid[]) // writes the values from the grid array to the file
{
    FILE *output;
    fopen_s(&output, file, "w+");

    for(int i=0, j=0; i<81; ++i, ++j)
        {
            if(j == 9) // print a new line every row (9 values)
            {
                fprintf(output, "\n");
                j = 0;
            }

            fprintf(output, "%d ", grid[i]);
        }

    fclose(output);
}

void solve(char *fileIn, char *fileOut) // attempts to solve the grid from the input file by brute force, and writes the result to the output file
{
    int grid[81];
    int countUnsolved = fillGridFromFile(fileIn, grid);

    if(countUnsolved == 0) // already solved?!
    {
        writeGridToFile(fileOut, grid); // write "result" to output file
    }

    if(!isValid(grid)) // cannot solve grid as it already violates the constraints of Sudoku
    {
        FILE *output;
        fopen_s(&output, fileOut, "w+");
        fprintf(output, 
        "Could not solve the specified grid as it violates the constraints of Sudoku - found the same number more than once in a row, column or box.");
        fclose(output);
        return;
    }

    bool solved = bruteForceSolve(grid);

    if(!solved) 
    {
        FILE *output;
        fopen_s(&output, fileOut, "w+");
        fprintf(output, 
        "Could not solve the specified grid as no solution exists.");
        fclose(output);
    }

    else writeGridToFile(fileOut, grid); // write result to output file    
}

void solveNextNumber(char *fileIn, char *fileOut) // solves a single cell in the grid
{
    int grid[81];
    int countUnsolved = fillGridFromFile(fileIn, grid);

    if(countUnsolved == 0) // already solved?!
    {
        writeGridToFile(fileOut, grid); // write "result" to output file
    }

    if(!isValid(grid)) // cannot solve grid as it already violates the constraints of Sudoku
    {
        FILE *output;
        fopen_s(&output, fileOut, "w+");
        fprintf(output, 
        "Could not solve the specified grid as it violates the constraints of Sudoku - found the same number more than once in a row, column or box.");
        fclose(output);
        return;
    }

    // find the co-ordinates of all regions (a region is a row, column or box)
    // e.g. the first row has co-ordinates 0 1 2 3 4 5 6 7 8
    // the first column has co-ordinates 0 9 18 27 36 45 54 63 72
    // the first box has co-ordinates 0 1 2 9 10 11 18 19 20
    int regions[27][9]; 

    for(int i=0; i<9; ++i)
    {
        for(int j=0; j<9; ++j)
        {
            regions[i][j] = 9*i + j; // co-ordinates for rows
            regions[9+i][j] = i + 9*j; //co-ordinates for columns

            // mutate such that i = 0 1 2 9 10 11 18 19 20
            int k = i;
            if(i >= 6) k += 12;
            else if(i >= 3) k += 6;

            // mutate such that j = 0 1 2 9 10 11 18 19 20
            int l = j;
            if(j >= 6) l += 12;
            else if(j >= 3) l += 6;

            regions[18+i][j] = 3*k + l; //co-ordinates for boxes
        }
    }
}