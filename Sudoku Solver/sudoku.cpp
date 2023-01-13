#pragma once

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <Windows.h>
#include "bitHacks.h"
#include "sudoku.h"

// Glossary of Sudoku Terms:
// https://en.wikipedia.org/wiki/Glossary_of_Sudoku

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

inline bool isRow(cell region[8]) // returns true if the region is a row
{
    return (region[0].row == region[8].row);
}

inline bool isColumn(cell region[8]) // returns true if the region is a column
{
    return (region[0].column == region[8].column);
}

inline bool isBox(cell region[8]) // returns true if the region is a box
{
    return ((region[0].row+2) == region[8].row);
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
    for(int rowOffset=0; rowOffset<=6; rowOffset+=3)
    {
        for(int colOffset=0; colOffset<=6; colOffset+=3)
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

            for(int row=rowOffset; row<3+rowOffset; ++row)
            {
                for(int column=colOffset; column<3+colOffset; ++column)
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

    for(int rowIt=rowOffset; rowIt<3+rowOffset; ++rowIt)
    {
        for(int columnIt=colOffset; columnIt<3+colOffset; ++columnIt)
        {
            switch (grid[rowIt][columnIt])
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

solver::solver(char *fileIn, char *fileOut, int countToSolve, int sleepTimeMs)
{
    file = fileOut;
    this->countToSolve = countToSolve;
    
    int countUnsolved = fillGridFromFile(fileIn, grid);

    if(countUnsolved == 0) // already solved?!
    {
        write(); // write "result" to output file
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

    if(countToSolve > countUnsolved) this->countToSolve = countUnsolved;         
    
    countSolved = 0;
    finished = false;
    this->sleepTimeMs = sleepTimeMs;

    for(int row=0; row<9; ++row) // initialise possible values
    {
        for(int column=0; column<9; ++column)
        {
            if(grid[row][column] == 0) possibleValuesMask[row][column] = 0b1111111110;

            else possibleValuesMask[row][column] = 0;
        }
    }
}

void solver::write()
{
    writeGridToFile(file, grid);
}

void solver::writeCell(cell cell, int value) // enter value into cell and write the result to file
{
    int row = cell.row;
    int column = cell.column;

    grid[row][column] = value;
    possibleValuesMask[row][column] = 0;

    assert(isCellValid(grid, row, column));

    write();

    ++countSolved;
    if(countSolved == countToSolve) // stop if we've solved enough cells, continue otherwise
    {
        finished = true;
        return;
    }

    // we now know that value cannot go anywhere in the three regions containing the current cell; clear the appropriate bit for those cells
    {
        for(int i=0; i<9; ++i)
        {
            possibleValuesMask[row][i] &= ~(1 << value); // row
            possibleValuesMask[i][column] &= ~(1 << value); // column

            assert(possibleValuesMask[row][i] || grid[row][i]);
            assert(possibleValuesMask[i][column] || grid[i][column]);
        }

        // round down the current row and column to the nearest factor of 3
        int rowOffset = 3*(row/3);
        int colOffset = 3*(column/3);

        for(int rowIt=rowOffset; rowIt<3+rowOffset; ++rowIt)
        {
            for(int columnIt=colOffset; columnIt<3+colOffset; ++columnIt)
            {
                possibleValuesMask[rowIt][columnIt] &= ~(1 << value); // box

                assert(possibleValuesMask[rowIt][columnIt] || grid[rowIt][columnIt]);
            }
        }
    }
    Sleep(sleepTimeMs); // sleep if desired, for an animated solve effect!
}

void solver::solveValueForRegion(int value, cell region[]) // checks where specified value could go in the specified region, and updates grid or possible values accordingly
{
    int countCandidates = 0; // number of candidate cells where value could go
    cell candidateCells[3]; // co-ordinates of first 3 candidate cells

    for(int currCell=0; currCell<9; ++currCell)
    {
        int currRow = region[currCell].row;
        int currCol = region[currCell].column;

        if(grid[currRow][currCol] == value) return; // value already solved for this region 

        if((possibleValuesMask[currRow][currCol] & (1 << value)) > 0) // value can go in current cell
        {   
            countCandidates++;

            if(countCandidates < 4) // if less than 4 candidates so far, store the current cell and keep going
            {             
                candidateCells[countCandidates-1] = cell(currRow, currCol);
            }                
            else // if there are 4+ candidates then no possible info, continue to next value
            {
                break;
            }
        }
    } // region loop

    switch(countCandidates)
    {
        case 1: // found where value goes
        {
            writeCell(candidateCells[0], value);            
        }
            break;

        // if value only has 2 or 3 candidates in the current region that are also all in another region, we can eliminate value from other cells in that region
        // e.g. see Step 14 here: https://www.websudoku.com/images/example-steps.html
        case 2: // pointing pairs: https://sudoku.com/sudoku-rules/pointing-pairs/
        {
            // if current region is a box, check if candidates are also in the same row or column
            if(isBox(region)) 
            {
                if(candidateCells[0].row == candidateCells[1].row) // candidates are in the same row
                {
                    int row = candidateCells[0].row;

                    for(int currCol=0; currCol<9; ++currCol)
                    {
                        // clear possible value for non-candidate cells
                        if((currCol != candidateCells[0].column) && (currCol != candidateCells[1].column))
                        {
                            possibleValuesMask[row][currCol] &= ~(1 << value);

                            assert(possibleValuesMask[row][currCol] || grid[row][currCol]);
                        }
                    }
                }
                else if(candidateCells[0].column == candidateCells[1].column) // candidates are in the same column
                {
                    int column = candidateCells[0].column;

                    for(int currRow=0; currRow<9; ++currRow)
                    {
                        // clear possible value for non-candidate cells
                        if((currRow != candidateCells[0].row) && (currRow != candidateCells[1].row))
                        {
                            possibleValuesMask[currRow][column] &= ~(1 << value);

                            assert(possibleValuesMask[currRow][column] || grid[currRow][column]);
                        }
                    }
                }
            }
            else // else current region is a row or column, check if candidates are also in the same box
            {
                int rowOffset = 3*(candidateCells[0].row/3);
                int colOffset = 3*(candidateCells[0].column/3);

                if( (isRow(region) && (colOffset == 3*(candidateCells[1].column/3)))
                    || (isColumn(region) && (rowOffset == 3*(candidateCells[1].row/3))))
                    {
                        for(int rowIt=rowOffset; rowIt<3+rowOffset; ++rowIt)
                        {
                            for(int columnIt=colOffset; columnIt<3+colOffset; ++columnIt)
                            {
                                // clear possible value for non-candidate cells
                                if(((rowIt != candidateCells[0].row) || (columnIt != candidateCells[0].column))
                                    && ((rowIt != candidateCells[1].row) || (columnIt != candidateCells[1].column)))
                                {
                                    possibleValuesMask[rowIt][columnIt] &= ~(1 << value);

                                    assert(possibleValuesMask[rowIt][columnIt] || grid[rowIt][columnIt]);
                                }
                            }
                        }
                    }
            }
        }
            break;

        case 3: // pointing triples: https://sudoku.com/sudoku-rules/pointing-triples/
        {
            // if((region[0].row == region[8].row)) // if current region is a row, check if candidates are also in the same box
            // {
            //     int rowOffset = 3*(candidateCells[0].row/3);
            //     int colOffset = 3*(candidateCells[0].column/3);

            //     if((colOffset == 3*(candidateCells[1].column/3)) 
            //         && (colOffset == 3*(candidateCells[2].column/3))) // candidates are in the same box
            //     {
            //         for(int rowIt=rowOffset; rowIt<3+rowOffset; ++rowIt)
            //         {
            //             for(int columnIt=colOffset; columnIt<3+colOffset; ++columnIt)
            //             {
            //                 // clear possible value for non-candidate cells
            //                 if(((rowIt) != candidateCells[0].row))
            //                 {
            //                     possibleValuesMask[rowIt][columnIt] &= ~(1 << value);

            //                     assert(possibleValuesMask[rowIt][columnIt] || grid[rowIt][columnIt]);
            //                 }
            //             }
            //         }
            //     }
            // }
            // else if((region[0].column == region[8].column)) // else if current region is a column, check if candidates are also in the same box
            // {
            //     int rowOffset = 3*(candidateCells[0].row/3);
            //     int colOffset = 3*(candidateCells[0].column/3);

            //     if((rowOffset == 3*(candidateCells[1].row/3))
            //         && (rowOffset == 3*(candidateCells[2].row/3))) // candidates are in the same box
            //     {
            //         for(int rowIt=rowOffset; rowIt<3+rowOffset; ++rowIt)
            //         {
            //             for(int columnIt=colOffset; columnIt<3+colOffset; ++columnIt)
            //             {
            //                 // clear possible value for non-candidate cells
            //                 if(((columnIt) != candidateCells[0].column))
            //                 {
            //                     possibleValuesMask[rowIt][columnIt] &= ~(1 << value);

            //                     assert(possibleValuesMask[rowIt][columnIt] || grid[rowIt][columnIt]);
            //                 }
            //             }
            //         }
            //     }
            // }
            // else // else current region is a box, check if candidates are also in the same row or column
            // {
            //     if((candidateCells[0].row == candidateCells[1].row)
            //         && (candidateCells[0].row == candidateCells[2].row)) // candidates are in the same row
            //     {
            //         int row = candidateCells[0].row;

            //         for(int currCol=0; currCol<9; ++currCol)
            //         {
            //             // clear possible value for non-candidate cells
            //             if((currCol != candidateCells[0].column) 
            //                 && (currCol != candidateCells[1].column)
            //                 && (currCol != candidateCells[2].column))
            //             {
            //                 possibleValuesMask[row][currCol] &= ~(1 << value);

            //                 assert(possibleValuesMask[row][currCol] || grid[row][currCol]);
            //             }
            //         }
            //     }
            //     else if((candidateCells[0].column == candidateCells[1].column)
            //             && (candidateCells[0].column == candidateCells[2].column)) // candidates are in the same column
            //     {
            //         int column = candidateCells[0].column;

            //         for(int currRow=0; currRow<9; ++currRow)
            //         {
            //             // clear possible value for non-candidate cells
            //             if((currRow != candidateCells[0].row) 
            //                 && (currRow != candidateCells[1].row)
            //                 && (currRow != candidateCells[2].row))
            //             {
            //                 possibleValuesMask[currRow][column] &= ~(1 << value);

            //                 assert(possibleValuesMask[currRow][column] || grid[currRow][column]);
            //             }
            //         }
            //     }
            // }
        }
            break;
        default: break; // too many candidates, no info
    }
}

void solver::solveNextNumber()
{
    cell regions[27][9] = 
    {
        //rows
        {cell(0,0), cell(0,1), cell(0,2), cell(0,3), cell(0,4), cell(0,5), cell(0,6), cell(0,7), cell(0,8)},
        {cell(1,0), cell(1,1), cell(1,2), cell(1,3), cell(1,4), cell(1,5), cell(1,6), cell(1,7), cell(1,8)},
        {cell(2,0), cell(2,1), cell(2,2), cell(2,3), cell(2,4), cell(2,5), cell(2,6), cell(2,7), cell(2,8)},
        {cell(3,0), cell(3,1), cell(3,2), cell(3,3), cell(3,4), cell(3,5), cell(3,6), cell(3,7), cell(3,8)},
        {cell(4,0), cell(4,1), cell(4,2), cell(4,3), cell(4,4), cell(4,5), cell(4,6), cell(4,7), cell(4,8)},
        {cell(5,0), cell(5,1), cell(5,2), cell(5,3), cell(5,4), cell(5,5), cell(5,6), cell(5,7), cell(5,8)},
        {cell(6,0), cell(6,1), cell(6,2), cell(6,3), cell(6,4), cell(6,5), cell(6,6), cell(6,7), cell(6,8)},
        {cell(7,0), cell(7,1), cell(7,2), cell(7,3), cell(7,4), cell(7,5), cell(7,6), cell(7,7), cell(7,8)},
        {cell(8,0), cell(8,1), cell(8,2), cell(8,3), cell(8,4), cell(8,5), cell(8,6), cell(8,7), cell(8,8)},
        //columns
        {cell(0,0), cell(1,0), cell(2,0), cell(3,0), cell(4,0), cell(5,0), cell(6,0), cell(7,0), cell(8,0)},
        {cell(0,1), cell(1,1), cell(2,1), cell(3,1), cell(4,1), cell(5,1), cell(6,1), cell(7,1), cell(8,1)},
        {cell(0,2), cell(1,2), cell(2,2), cell(3,2), cell(4,2), cell(5,2), cell(6,2), cell(7,2), cell(8,2)},
        {cell(0,3), cell(1,3), cell(2,3), cell(3,3), cell(4,3), cell(5,3), cell(6,3), cell(7,3), cell(8,3)},
        {cell(0,4), cell(1,4), cell(2,4), cell(3,4), cell(4,4), cell(5,4), cell(6,4), cell(7,4), cell(8,4)},
        {cell(0,5), cell(1,5), cell(2,5), cell(3,5), cell(4,5), cell(5,5), cell(6,5), cell(7,5), cell(8,5)},
        {cell(0,6), cell(1,6), cell(2,6), cell(3,6), cell(4,6), cell(5,6), cell(6,6), cell(7,6), cell(8,6)},
        {cell(0,7), cell(1,7), cell(2,7), cell(3,7), cell(4,7), cell(5,7), cell(6,7), cell(7,7), cell(8,7)},
        {cell(0,8), cell(1,8), cell(2,8), cell(3,8), cell(4,8), cell(5,8), cell(6,8), cell(7,8), cell(8,8)},
        //boxes
        {cell(0,0), cell(0,1), cell(0,2), cell(1,0), cell(1,1), cell(1,2), cell(2,0), cell(2,1), cell(2,2)},
        {cell(0,3), cell(0,4), cell(0,5), cell(1,3), cell(1,4), cell(1,5), cell(2,3), cell(2,4), cell(2,5)},
        {cell(0,6), cell(0,7), cell(0,8), cell(1,6), cell(1,7), cell(1,8), cell(2,6), cell(2,7), cell(2,8)},
        {cell(3,0), cell(3,1), cell(3,2), cell(4,0), cell(4,1), cell(4,2), cell(5,0), cell(5,1), cell(5,2)},
        {cell(3,3), cell(3,4), cell(3,5), cell(4,3), cell(4,4), cell(4,5), cell(5,3), cell(5,4), cell(5,5)},
        {cell(3,6), cell(3,7), cell(3,8), cell(4,6), cell(4,7), cell(4,8), cell(5,6), cell(5,7), cell(5,8)},
        {cell(6,0), cell(6,1), cell(6,2), cell(7,0), cell(7,1), cell(7,2), cell(8,0), cell(8,1), cell(8,2)},
        {cell(6,3), cell(6,4), cell(6,5), cell(7,3), cell(7,4), cell(7,5), cell(8,3), cell(8,4), cell(8,5)},
        {cell(6,6), cell(6,7), cell(6,8), cell(7,6), cell(7,7), cell(7,8), cell(8,6), cell(8,7), cell(8,8)}
    };

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
                    if(!(possibleValuesMask[currRow][currCol] & (1 << value))) continue; // skip if we already know value is not possible
                    grid[currRow][currCol] = value;

                    if(!isCellValid(grid, currRow, currCol)) // if grid is now invalid remove possible value for this cell
                        possibleValuesMask[currRow][currCol] &= ~(1 << value); 
                }

                assert(possibleValuesMask[currRow][currCol] != 0);

                if(isPowerOfTwo(possibleValuesMask[currRow][currCol])) // if possible value is a power of 2 there is only one possible value
                {
                    // find the correct value
                    int value = getPowerOfTwo(possibleValuesMask[currRow][currCol]);
                    writeCell(cell(currRow, currCol), value);

                    if(finished) return;
                }

                else grid[currRow][currCol] = 0; // else reset cell to empty
            }
        } // cell loop

        // search every region to see if any values can only be in one cell
        for(int currRegion=0; currRegion<27; ++currRegion) 
        {
            for(int value=1; value<=9; ++value) // see if we can solve any of the numbers 1-9 for this column
            {
                solveValueForRegion(value, regions[currRegion]);

                if(finished) return; // stop if we've solved enough cells, continue otherwise
            } // value loop

            /*for(int firstCell=0; firstCell<9; ++firstCell) // look for hidden pairs: https://sudoku.com/sudoku-rules/hidden-pairs/
            {
                if(grid[currRow][firstCell] != 0) continue; // ignore completed cells

                for(int secondCell = firstCell+1; secondCell<9; ++secondCell)
                {
                    if(grid[currRow][secondCell] != 0) continue; // ignore completed cells

                    // store the values that could possibly be in both cells
                    int16_t possibleValuesCommon = possibleValuesMask[currRow][firstCell] 
                                                & possibleValuesMask[currRow][secondCell];

                    // now store all the values that could possibly be in the other 7 cells
                    int16_t possibleValuesOther = 0;

                    for(int otherCell=0; otherCell<9; ++otherCell)
                    {
                        if(otherCell != firstCell && otherCell != secondCell)
                            possibleValuesOther |= possibleValuesMask[currRow][otherCell];
                    }

                    // find the bits that are set in common but not other, i.e. the values that can only go in firstCell and secondCell
                    possibleValuesCommon &= ~possibleValuesOther;

                    // if there are 2 bits set, i.e. 2 values that can only go in firstCell and secondCell,
                    // then they MUST go in those 2 cells. All other possibilities can be cleared
                    if(getCountBitsSet(possibleValuesCommon) == 2)
                    {
                        possibleValuesMask[currRow][firstCell] = possibleValuesCommon;
                        possibleValuesMask[currRow][secondCell] = possibleValuesCommon;
                        break; // continue to next value for firstCell
                    }
                    else for(int thirdCell = secondCell+1; thirdCell<9; ++thirdCell) // no hidden pair, but keep looking for hidden triples: https://sudoku.com/sudoku-rules/hidden-triples/
                    {
                        if(grid[currRow][thirdCell] != 0) continue; // ignore completed cells

                        // store the values that could possibly be in both cells
                        possibleValuesCommon = possibleValuesMask[currRow][firstCell] 
                                                & possibleValuesMask[currRow][secondCell]
                                                & possibleValuesMask[currRow][thirdCell];

                        // now store all the values that could possibly be in the other 6 cells
                        possibleValuesOther = 0;

                        for(int otherCell=0; otherCell<9; ++otherCell)
                        {
                            if(otherCell != firstCell && otherCell != secondCell && otherCell != thirdCell)
                                possibleValuesOther |= possibleValuesMask[currRow][otherCell];
                        }

                        // find the bits that are set in common but not other, i.e. the values that can only go in firstCell and secondCell
                        possibleValuesCommon &= ~possibleValuesOther;

                        // if there are 2 bits set, i.e. 2 values that can only go in firstCell and secondCell,
                        // then they MUST go in those 2 cells. All other possibilities can be cleared
                        if(getCountBitsSet(possibleValuesCommon) == 3)
                        {
                            possibleValuesMask[currRow][firstCell] &= possibleValuesCommon;
                            possibleValuesMask[currRow][secondCell] &= possibleValuesCommon;
                            possibleValuesMask[currRow][thirdCell] &= possibleValuesCommon;
                            break; // continue to next value for secondCell
                        }
                    }
                }
            }*/
        } // box loop
    }
}

void solveNextNumber(char *fileIn, char *fileOut, int countToSolve, int sleepTimeMs) // solves next N cells in the grid
{
    solver solver(fileIn, fileOut, countToSolve, sleepTimeMs);
    solver.solveNextNumber();
}