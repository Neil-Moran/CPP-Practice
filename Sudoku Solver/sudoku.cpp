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
                // skip to next row of the square if necessary
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

void solve(char *fileIn, char *fileOut)
{
    FILE *input;
    fopen_s(&input, fileIn, "r");

    int grid[81];

    for(int i=0; i<81; ++i)
    {
        fscanf_s(input, "%d", &grid[i]);
    }

    print(grid);

    if(!isValid(grid)) // cannot solve grid as it already violates the constraints of Sudoku
        {
            FILE *output;
            fopen_s(&output, fileOut, "w+");
            fprintf(output, 
            "Could not solve the specified grid as it violates the constraints of Sudoku - found the same number more than once in a row, column or square.");
            fclose(output);
            return;
        }

    bool completed = false; // completed either means the Sudoku is solved or our algorithm cannot solve it any further

    while(!completed)
    {
        completed = true;        
        
    }

    fclose(input);

    // write result to output file
    FILE *output;
    fopen_s(&output, fileOut, "w+");

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