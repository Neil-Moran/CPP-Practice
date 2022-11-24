#pragma once

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <Windows.h>
#include "bitHacks.h"
#include "sudoku.h"

// Glossary of Sudoku Terms:
// https://en.wikipedia.org/wiki/Glossary_of_Sudoku

// hard code the co-ordinates of all regions (row, column or box)
static int regions[27][9] = {
    // 0-8: rows
    {0, 1, 2, 3, 4, 5, 6, 7, 8},
    {9, 10, 11, 12, 13, 14, 15, 16, 17},
    {18, 19, 20, 21, 22, 23, 24, 25, 26},
    {27, 28, 29, 30, 31, 32, 33, 34, 35},
    {36, 37, 38, 39, 40, 41, 42, 43, 44},
    {45, 46, 47, 48, 49, 50, 51, 52, 53},
    {54, 55, 56, 57, 58, 59, 60, 61, 62},
    {63, 64, 65, 66, 67, 68, 69, 70, 71},
    {72, 73, 74, 75, 76, 77, 78, 79, 80},
    // 9-17: columns
    {0, 9, 18, 27, 36, 45, 54, 63, 72},
    {1, 10, 19, 28, 37, 46, 55, 64, 73},
    {2, 11, 20, 29, 38, 47, 56, 65, 74},
    {3, 12, 21, 30, 39, 48, 57, 66, 75},
    {4, 13, 22, 31, 40, 49, 58, 67, 76},
    {5, 14, 23, 32, 41, 50, 59, 68, 77},
    {6, 15, 24, 33, 42, 51, 60, 69, 78},
    {7, 16, 25, 34, 43, 52, 61, 70, 79},
    {8, 17, 26, 35, 44, 53, 62, 71, 80},
    // 18-26: boxes
    {0, 1, 2, 9, 10, 11, 18, 19, 20},
    {3, 4, 5, 12, 13, 14, 21, 22, 23},
    {6, 7, 8, 15, 16, 17, 24, 25, 26},
    {27, 28, 29, 36, 37, 38, 45, 46, 47},
    {30, 31, 32, 39, 40, 41, 48, 49, 50},
    {33, 34, 35, 42, 43, 44, 51, 52, 53},
    {54, 55, 56, 63, 64, 65, 72, 73, 74},
    {57, 58, 59, 66, 67, 68, 75, 76, 77},
    {60, 61, 62, 69, 70, 71, 78, 79, 80}
    // derivation of regions:
    /*
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
    */
};

inline int getRow(int cell) // returns the row of the specified cell
{
    return cell/9;
}

inline int getColumn(int cell) // returns the column of the specified cell
{
    return 9 + (cell%9);
}

inline int getBox(int cell) // returns the box of the specified cell
{
    return 18 + (3*(cell/27)) + ((cell%9)/3);
}

inline bool isRow(int region) // returns true if the region index is for a box and not a row or column
{
    return region < 9;
}

inline bool isBox(int region) // returns true if the region index is for a box and not a row or column
{
    return region >= 18;
}

int fillGridFromFile(char *file, int grid[9][9]) // writes the values from the file into the grid array and returns the count of empty cells
{
    int countUnsolved = 0;

    FILE *input;
    fopen_s(&input, file, "r");

    for(int row=0; row<9; ++row)
    {
        for(int column=0; column<9; ++column)
        {
            fscanf_s(input, "%d", &grid[row][column]);

            if(grid[row][column] == 0) ++countUnsolved;
        }
    }

    fclose(input);

    return countUnsolved;
}

void writeGridToFile(char *file, int grid[9][9]) // writes the values from the grid array to the file
{
    FILE *output;
    fopen_s(&output, file, "w+");

    for(int row=0; row<9; ++row)
    {
        for(int column=0; column<9; ++column)
        {
            if(grid[row][column] == 0) fprintf(output, "_ ");
            else fprintf(output, "%d ", grid[row][column]);
        }
        fprintf(output, "\n"); // print a new line every row
    }

    fclose(output);
}

bool isValid(int grid[9][9]) // checks that the grid does not violate Sudoku constraints, but does not check for solvability
{
    // we will check each group (row, column or box) and verify no number appears more than once
    int countOnes, countTwos, countThrees, countFours, countFives, countSixes, countSevens, countEights, countNines;

    /* --- CHECK ROWS ARE VALID --- */
    for(int row=0; row<9; ++row)
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
        
        for(int column=0; column<9; ++column)
        {
            switch (grid[row][column])
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

        // all values should be 0 or 1, so OR-ing them should be 0 or 1 also
        if((countOnes | countTwos | countThrees
            | countFours | countFives | countSixes 
            | countSevens | countEights | countNines) > 1) return false;        
    }

    /* --- CHECK COLUMNS ARE VALID --- */
    for(int column=0; column<9; ++column)
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
        
        for(int row=0; row<9; ++row)
        {
            switch (grid[row][column])
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
        
        // all values should be 0 or 1, so OR-ing them should be 0 or 1 also
        if((countOnes | countTwos | countThrees
            | countFours | countFives | countSixes 
            | countSevens | countEights | countNines) > 1) return false;
    }

    /* --- CHECK BOXES ARE VALID --- */
    for(int colOffset=0; colOffset<=6; colOffset+=3)
    {
        for(int rowOffset=0; rowOffset<=6; rowOffset+=3)
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

            for(int column=0; column<3; ++column)
            {
                for(int row=0; row<3; ++row)
                {
                    switch (grid[row+rowOffset][column+colOffset])
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
            }

            // all values should be 0 or 1, so OR-ing them should be 0 or 1 also
            if((countOnes | countTwos | countThrees
                | countFours | countFives | countSixes 
                | countSevens | countEights | countNines) > 1) return false;            
        }
    }

    return true; // grid is valid if we made it here
}

bool isRegionValid(int grid[], int region[]) // checks that specified region of the grid does not violate Sudoku constraints, but does not check for solvability
{
    // the region variable is a list of 9 indices referring to a specific region (row, column or box) in the grid
    // we will verify no number appears more than once in the region
    int countOnes = 0, countTwos = 0, countThrees = 0, countFours = 0, countFives = 0, countSixes = 0, countSevens = 0, countEights = 0, countNines = 0;

    for(int i=0; i<9; ++i)
    {
        switch (grid[region[i]])
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

    // all values should be 0 or 1, so OR-ing them should be 0 or 1 also
    if((countOnes | countTwos | countThrees
        | countFours | countFives | countSixes 
        | countSevens | countEights | countNines) > 1) return false;

    else return true;
}

bool isRowValid(int grid[9][9], int row) // checks that the specified row does not violate Sudoku constraints
{
    int countOnes = 0, countTwos = 0, countThrees = 0, countFours = 0, countFives = 0, countSixes = 0, countSevens = 0, countEights = 0, countNines = 0;

    for(int column=0; column<9; ++column)
    {
        switch (grid[row][column])
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

    // all values should be 0 or 1, so OR-ing them should be 0 or 1 also
    if((countOnes | countTwos | countThrees
        | countFours | countFives | countSixes 
        | countSevens | countEights | countNines) > 1) return false;

    else return true;
}

bool isColumnValid(int grid[9][9], int column) // checks that the specified column does not violate Sudoku constraints
{
    int countOnes = 0, countTwos = 0, countThrees = 0, countFours = 0, countFives = 0, countSixes = 0, countSevens = 0, countEights = 0, countNines = 0;

    for(int row=0; row<9; ++row)
    {
        switch (grid[row][column])
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

    // all values should be 0 or 1, so OR-ing them should be 0 or 1 also
    if((countOnes | countTwos | countThrees
        | countFours | countFives | countSixes 
        | countSevens | countEights | countNines) > 1) return false;

    else return true;
}

bool isBoxValid(int grid[9][9], int row, int column) // checks that the box containing the specified cell does not violate Sudoku constraints
{
    int countOnes = 0, countTwos = 0, countThrees = 0, countFours = 0, countFives = 0, countSixes = 0, countSevens = 0, countEights = 0, countNines = 0;

    // round down the current row and column to the nearest factor of 3
    int rowOffset = 3*(row/3);
    int colOffset = 3*(column/3);

    for(int columnIt=0; columnIt<3; ++columnIt)
    {
        for(int rowIt=0; rowIt<3; ++rowIt)
        {
            switch (grid[rowIt+rowOffset][columnIt+colOffset])
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
    }

    // all values should be 0 or 1, so OR-ing them should be 0 or 1 also
    if((countOnes | countTwos | countThrees
        | countFours | countFives | countSixes 
        | countSevens | countEights | countNines) > 1) return false;

    else return true;
}

inline bool isCellValid(int grid[9][9], int row, int column) // checks that the regions of the grid containing the specified cell do not violate Sudoku constraints
{
    if(isRowValid(grid, row) && isColumnValid(grid, column) && isBoxValid(grid, row, column))
        return true; // all three regions are still valid
    else return false;
}

bool bruteForceSolve(int grid[9][9], int row = 0, int column = 0) // recursively try every value from 1 to 9 at the specified index and every empty cell onwards
{  
    // note: assumes the grid is a proper Sudoku, i.e. there is only one solution

    if(column == 9) // reached the end of the row, jump to the start of the next one
    {
        column = 0;
        ++row;
    }

    while(row < 9 && grid[row][column] != 0) // find the next empty cell
    {
        ++column;
        if(column == 9) // reached the end of the row, jump to the start of the next one
        {
            column = 0;
            ++row;
        }
    }

    if(row >= 9) return true; // if we've filled all cells then this solution is correct!
    
    for(int value=1; value<=9; ++value)
    {
        grid[row][column] = value;

        if(!isCellValid(grid, row, column)) continue; // if current value makes the grid invalid, continue to the next

        if(bruteForceSolve(grid, row, column+1)) return true; // if all other empty cells can be filled, this value is correct!
    }

    // if no value from 1-9 is valid in this cell then the solution up to now is wrong
    grid[row][column] = 0; // remove the incorrect value, we'll try setting it again in another recursion
    return false; 
}

void solve(char *fileIn, char *fileOut) // attempts to solve the grid from the input file by brute force, and writes the result to the output file
{
    int grid[9][9];
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

void solveNextNumber(char *fileIn, char *fileOut, int countToSolve, int sleepTimeMs) // solves next N cells in the grid
{
    int grid[9][9];
    {
        int countUnsolved = fillGridFromFile(fileIn, grid);

        if(countUnsolved == 0) // already solved?!
        {
            writeGridToFile(fileOut, grid); // write "result" to output file
            return;
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

        if(countToSolve > countUnsolved) countToSolve = countUnsolved; 
    }
    
    int countSolved = 0;
    int16_t possibleValues[9][9] = {0}; // stores the possible values for every empty cell, e.g. if 4th bit is set then 4 is still a possible value

    for(int row=0; row<9; ++row) // initialise possible values
    {
        for(int column=0; column<9; ++column)
        {
            if(grid[row][column] == 0) possibleValues[row][column] = 0b1111111110;
        }
    }
    
    for(int numLoops = 0; numLoops <= countToSolve; ++numLoops) // if we don't solve at least one number every iteration (after the first initialisation pass), the grid is unsolvable
    {
        // check possible values for every empty cell
        for(int currRow=0; currRow<9; ++currRow)
        {
            for(int currCol=0; currCol<9; ++currCol)
            {
                if(grid[currRow][currCol] != 0) continue; // ignore completed cells

                // try all values in the empty cell, if the grid is still valid then that value is possible
                for(int value=1; value<=9; ++value)
                {
                    if(!(possibleValues[currRow][currCol] & (1 << value))) continue; // skip if we already know value is not possible
                    grid[currRow][currCol] = value;

                    if(!isCellValid(grid, currRow, currCol)) // if grid is now invalid remove possible value for this cell
                        possibleValues[currRow][currCol] &= ~(1 << value); 
                }

                assert(possibleValues[currRow][currCol] != 0);

                if(isPowerOfTwo(possibleValues[currRow][currCol])) // if possible value is a power of 2 there is only one possible value
                {
                    // find the correct value
                    int value = getPowerOfTwo(possibleValues[currRow][currCol]);

                    grid[currRow][currCol] = value;
                    possibleValues[currRow][currCol] = 0;

                    assert(isCellValid(grid, currRow, currCol));

                    writeGridToFile(fileOut, grid);

                    ++countSolved;
                    if(countSolved == countToSolve) return; // stop if we've solved enough cells, continue otherwise

                    // we now know that value cannot go anywhere in the three regions containing the current cell; clear the appropriate bit for those cells
                    {
                        for(int i=0; i<9; ++i)
                        {
                            possibleValues[currRow][i] &= ~(1 << value); // row
                            possibleValues[i][currCol] &= ~(1 << value); // column
                        }

                        // round down the current row and column to the nearest factor of 3
                        int rowOffset = 3*(currRow/3);
                        int colOffset = 3*(currCol/3);

                        for(int columnIt=0; columnIt<3; ++columnIt)
                        {
                            for(int rowIt=0; rowIt<3; ++rowIt)
                            {
                                possibleValues[rowIt+rowOffset][columnIt+colOffset] &= ~(1 << value); // box
                            }
                        }
                    }
                    Sleep(sleepTimeMs);
                }

                else grid[currRow][currCol] = 0; // else reset cell to empty
            }
        } // cell loop

        // search every region to see if any values can only be in one cell
        /*for(int currRegion=0; currRegion<27; ++currRegion)
        {
            for(int value=1; value<=9; ++value) // see if we can solve any of the numbers 1-9 for this region
            {
                int countCandidates = 0; // number of candidate cells where value could go
                int candidateCells[3] = {-999, -999, -999}; // co-ordinates of first 3 candidate cells

                for(int currCell=0; currCell<9; ++currCell)
                {
                    if((possibleValues[regions[currRegion][currCell]] & (1 << value)) > 0) // value can go in currCell
                    {   
                        if(countCandidates < 3) // if less than 3 candidates so far, store the current cell and keep going                        
                            candidateCells[countCandidates++] = currCell;
                            
                        else // if there are more than 3 candidates then no possible info, continue to next value
                        {
                            ++countCandidates;
                            break;
                        }
                    }
                }

                switch(countCandidates)
                {
                    case 1: // found where value goes
                    {
                        int cell = regions[currRegion][candidateCells[0]];
                        grid[cell] = value;
                        possibleValues[cell] = 0;

                        assert(isCellValid(grid, cell));

                        writeGridToFile(fileOut, grid);                    

                        ++countSolved;
                        if(countSolved == countToSolve) return; // stop if we've solved enough cells, continue otherwise

                        // we now know value cannot go anywhere in the three regions containing the current cell; clear the value-th bit for those cells
                        // however we can ignore the current region - the reason we're here is because value couldn't go anywhere else there
                        int region1, region2;

                        if(isRow(currRegion)) // current region is row
                        {
                            region1 = getColumn(cell); // column
                            region2 = getBox(cell); // box
                        }
                        else if (!isBox(currRegion)) // current region is column
                        {
                            region1 = getRow(cell); // row
                            region2 = getBox(cell); // box
                        }
                        else // current region is box
                        {
                            region1 = getRow(cell); // row
                            region2 = getColumn(cell); // column
                        }

                        for(int i=0; i<9; ++i)
                        {
                            possibleValues[regions[region1][i]] &= ~(1 << value);
                            possibleValues[regions[region2][i]] &= ~(1 << value); 

                            assert((possibleValues[regions[region1][i]] || grid[regions[region1][i]]));
                            assert((possibleValues[regions[region2][i]] || grid[regions[region2][i]]));
                        }
                        Sleep(sleepTimeMs);
                    }
                        break;

                    // if value only has 2 or 3 candidates in the current region that are also all in another region, we can eliminate value from other cells in that region
                    // e.g. see Step 14 here: https://www.websudoku.com/images/example-steps.html
                    case 2: // pointing pairs: https://sudoku.com/sudoku-rules/pointing-pairs/
                    {
                        // transform cells from region space to grid space
                        int cell1 = regions[currRegion][candidateCells[0]];
                        int cell2 = regions[currRegion][candidateCells[1]];

                        if(isBox(currRegion)) // if current region is a box, check if candidates are in the same row or column
                        {
                            if(getRow(cell1) == getRow(cell2)) // same row
                            {
                                int row = getRow(cell1);

                                // clear value-th bit for all other cells in row
                                for(int i=0; i<9; ++i)
                                {
                                    if(regions[row][i] != cell1 
                                    && regions[row][i] != cell2)
                                        possibleValues[regions[row][i]] &= ~(1 << value);

                                    assert(possibleValues[regions[row][i]] || grid[regions[row][i]]); 
                                }
                            }

                            else if(getColumn(cell1) == getColumn(cell2)) // same column
                            {
                                int column = getColumn(cell1);

                                // clear value-th bit for all other cells in column
                                for(int i=0; i<9; ++i)
                                {
                                    if(regions[column][i] != cell1 
                                    && regions[column][i] != cell2)
                                        possibleValues[regions[column][i]] &= ~(1 << value);
                                
                                    assert(possibleValues[regions[column][i]] || grid[regions[column][i]]);
                                }
                            }
                        }
                        else // else current region is a row or column, check if candidates are in the same box
                        {
                            int box = getBox(cell1);

                            if(box == getBox(cell2)) // same box
                            {
                                // clear value-th bit for all other cells in box
                                for(int i=0; i<9; ++i)
                                {
                                    if(regions[box][i] != cell1 
                                    && regions[box][i] != cell2)
                                        possibleValues[regions[box][i]] &= ~(1 << value);

                                    assert(possibleValues[regions[box][i]] || grid[regions[box][i]]);
                                }
                            }
                        }
                    }
                        break;

                    case 3: // pointing triples: https://sudoku.com/sudoku-rules/pointing-triples/
                    {
                        // transform cells from region space to grid space
                        int cell1 = regions[currRegion][candidateCells[0]];
                        int cell2 = regions[currRegion][candidateCells[1]];
                        int cell3 = regions[currRegion][candidateCells[2]];

                        if(isBox(currRegion)) // if current region is a box, check if candidates are in the same row or column
                        {
                            if((getRow(cell1) == getRow(cell2))
                                && getRow(cell1) == getRow(cell3)) // same row
                            {
                                int row = getRow(cell1);

                                // clear value-th bit for all other cells in row
                                for(int i=0; i<9; ++i)
                                {
                                    if(regions[row][i] != cell1 
                                    && regions[row][i] != cell2
                                    && regions[row][i] != cell3)
                                        possibleValues[regions[row][i]] &= ~(1 << value);

                                    assert(possibleValues[regions[row][i]] || grid[regions[row][i]]); 
                                }
                            }

                            else if((getColumn(cell1) == getColumn(cell2))
                                && (getColumn(cell1) == getColumn(cell3))) // same column
                            {
                                int column = getColumn(cell1);

                                // clear value-th bit for all other cells in column
                                for(int i=0; i<9; ++i)
                                {
                                    if(regions[column][i] != cell1 
                                    && regions[column][i] != cell2
                                    && regions[column][i] != cell3)
                                        possibleValues[regions[column][i]] &= ~(1 << value);
                                
                                    assert(possibleValues[regions[column][i]] || grid[regions[column][i]]);
                                }
                            }
                        }
                        else // else current region is a row or column, check if candidates are in the same box
                        {
                            int box = getBox(cell1);

                            if(box == getBox(cell2) && box == getBox(cell3)) // same box
                            {
                                // clear value-th bit for all other cells in box
                                for(int i=0; i<9; ++i)
                                {
                                    if(regions[box][i] != cell1 
                                    && regions[box][i] != cell2
                                    && regions[box][i] != cell3)
                                        possibleValues[regions[box][i]] &= ~(1 << value);

                                    assert(possibleValues[regions[box][i]] || grid[regions[box][i]]);
                                }
                            }
                        }
                    }
                        break;
                    default: break; // too many candidates, no info
                }
            } // value loop

            for(int firstCell=0; firstCell<9; ++firstCell) // look for hidden pairs: https://sudoku.com/sudoku-rules/hidden-pairs/
            {
                if(grid[regions[currRegion][firstCell]] != 0) continue; // ignore completed cells

                for(int secondCell = firstCell+1; secondCell<9; ++secondCell)
                {
                    if(grid[regions[currRegion][secondCell]] != 0) continue; // ignore completed cells

                    // store the values that could possibly be in both cells
                    int16_t possibleValuesCommon = possibleValues[regions[currRegion][firstCell]] 
                                                & possibleValues[regions[currRegion][secondCell]];

                    // now store all the values that could possibly be in the other 7 cells
                    int16_t possibleValuesOther = 0;

                    for(int otherCell=0; otherCell<9; ++otherCell)
                    {
                        if(otherCell != firstCell && otherCell != secondCell)
                            possibleValuesOther |= possibleValues[regions[currRegion][otherCell]];
                    }

                    // find the bits that are set in common but not other, i.e. the values that can only go in firstCell and secondCell
                    possibleValuesCommon &= ~possibleValuesOther;

                    // if there are 2 bits set, i.e. 2 values that can only go in firstCell and secondCell,
                    // then they MUST go in those 2 cells. All other possibilities can be cleared
                    if(getCountBitsSet(possibleValuesCommon) == 2)
                    {
                        possibleValues[regions[currRegion][firstCell]] = possibleValuesCommon;
                        possibleValues[regions[currRegion][secondCell]] = possibleValuesCommon;
                        break; // continue to next value for firstCell
                    }
                }
            }
        } // region loop
    */
   }
}