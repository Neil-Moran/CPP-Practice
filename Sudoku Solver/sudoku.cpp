#pragma once

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <Windows.h>
#include "bitHacks.h"
#include "sudoku.h"

// Glossary of Sudoku Terms:
// https://en.wikipedia.org/wiki/Glossary_of_Sudoku

void solve(char *fileIn, char *fileOut) // attempts to solve the grid from the input file by brute force, and writes the result to the output file
{
    solver solver(fileIn, fileOut);
    solver.solveFull();     
}

void solveN(char *fileIn, char *fileOut, int8_t countToSolve, int sleepTimeMs) // solves next N cells in the grid from the input file, and writes the result to the output file
{
    solver solver(fileIn, fileOut);
    solver.solveN(countToSolve, sleepTimeMs);
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

bool isValid(int8_t grid[9][9]) // checks that the grid does not violate Sudoku constraints, but does not check for solvability
{
    // we will check each region (row, column or box) and verify no number appears more than once

    // the count of each value is stored in valuesHistogram
    // e.g. valuesHistogram[2] stores the number of 2s in the region 
    // ([0] is unused so that the indices and values match)

    /* --- CHECK ROWS ARE VALID --- */
    for(int8_t row=0; row<9; ++row)
    {
        int8_t valuesHistogram[10] = {0,0,0,0,0,0,0,0,0,0};
        
        for(int8_t column=0; column<9; ++column)
        {
            if(grid[row][column] > 0 && grid[row][column] < 10)
                ++valuesHistogram[grid[row][column]];
        }

        // hack to see if any are > 1: all values should be 0 or 1, so OR-ing them should be 0 or 1 also
        if((valuesHistogram[1] | valuesHistogram[2] | valuesHistogram[3]
            | valuesHistogram[4] | valuesHistogram[5] | valuesHistogram[6] 
            | valuesHistogram[7] | valuesHistogram[8] | valuesHistogram[9]) > 1) return false;
    }

    /* --- CHECK COLUMNS ARE VALID --- */
    for(int8_t column=0; column<9; ++column)
    {
        int8_t valuesHistogram[10] = {0,0,0,0,0,0,0,0,0,0};
        
        for(int8_t row=0; row<9; ++row)
        {
            if(grid[row][column] > 0 && grid[row][column] < 10)
                ++valuesHistogram[grid[row][column]];
        }
        
        // hack to see if any are > 1: all values should be 0 or 1, so OR-ing them should be 0 or 1 also
        if((valuesHistogram[1] | valuesHistogram[2] | valuesHistogram[3]
            | valuesHistogram[4] | valuesHistogram[5] | valuesHistogram[6] 
            | valuesHistogram[7] | valuesHistogram[8] | valuesHistogram[9]) > 1) return false;
    }

    /* --- CHECK BOXES ARE VALID --- */
    for(int8_t rowOffset=0; rowOffset<=6; rowOffset+=3)
    {
        for(int8_t colOffset=0; colOffset<=6; colOffset+=3)
        {
            int8_t valuesHistogram[10] = {0,0,0,0,0,0,0,0,0,0};

            for(int8_t row=rowOffset; row<3+rowOffset; ++row)
            {
                for(int8_t column=colOffset; column<3+colOffset; ++column)
                {
                    if(grid[row][column] > 0 && grid[row][column] < 10)
                        ++valuesHistogram[grid[row][column]];
                }
            }

        // hack to see if any are > 1: all values should be 0 or 1, so OR-ing them should be 0 or 1 also
        if((valuesHistogram[1] | valuesHistogram[2] | valuesHistogram[3]
            | valuesHistogram[4] | valuesHistogram[5] | valuesHistogram[6] 
            | valuesHistogram[7] | valuesHistogram[8] | valuesHistogram[9]) > 1) return false;    
        }
    }

    return true; // grid is valid if we made it here
}

bool isRowValid(int8_t grid[9][9], int8_t row, int8_t value) // checks that the specified value does not appear more than once in the specified row
{
    int8_t countValue = 0; // number of occurences of value in the row

    for(int8_t column=0; column<9; ++column)
    {
        if(grid[row][column] == value)
        {
            if(++countValue > 1) return false;
        }
    }
    return true; // if we made it here value appears 0 or 1 times
}

bool isColumnValid(int8_t grid[9][9], int8_t column, int8_t value) // checks that the specified value does not appear more than once in the specified column
{
    int8_t countValue = 0; // number of occurences of value in the column

    for(int8_t row=0; row<9; ++row)
    {
        if(grid[row][column] == value)
        {
            if(++countValue > 1) return false;
        }
    }
    return true; // if we made it here value appears 0 or 1 times
}

bool isBoxValid(int8_t grid[9][9], int8_t row, int8_t column, int8_t value) // checks that the specified value does not appear more than once in the specified box
{
    int8_t countValue = 0; // number of occurences of value in the box

    // round down the current row and column to the nearest factor of 3
    int8_t rowOffset = 3*(row/3);
    int8_t colOffset = 3*(column/3);

    for(int8_t rowIt=rowOffset; rowIt<3+rowOffset; ++rowIt)
    {
        for(int8_t columnIt=colOffset; columnIt<3+colOffset; ++columnIt)
        {
            if(grid[rowIt][columnIt] == value)
            {
                if(++countValue > 1) return false;
            }
        }
    }
    return true; // if we made it here value appears 0 or 1 times
}

bool isCellValid(int8_t grid[9][9], int8_t row, int8_t column) // checks that the value at the specified cell does not violate Sudoku constraints
{
    int8_t value = grid[row][column];

    // check that the three regions containing the cell do not have the same value anywhere else
    if(isRowValid(grid, row, value) && isColumnValid(grid, column, value) && isBoxValid(grid, row, column, value))
        return true; 
    else return false;
}

solver::solver(char *fileIn, char *fileOut)
{
    file = fileOut;
    
    fillGridFromFile(fileIn);

    if(countUnsolved == 0) // already solved?!
    {
        writeResult(); // write "result" to output file
        return;
    }
    
    countSolved = 0;
    finished = false;

    for(int8_t row=0; row<9; ++row) // initialise possible values
    {
        for(int8_t column=0; column<9; ++column)
        {
            if(grid[row][column] == 0) possibleValuesMask[row][column] = 0b1111111110;

            else possibleValuesMask[row][column] = 0;
        }
    }
}

void solver::solveFull() // attempt to solve the grid fully by brute force
{
    if(!isValid(grid)) // cannot solve grid as it already violates the constraints of Sudoku
    {
        writeError("Could not solve the specified grid as it violates the constraints of Sudoku - found the same number more than once in a row, column or box.");
        return;
    }     

    bool solved = bruteForceSolve();

    if(!solved) 
    {
        writeError("Could not solve the specified grid as no solution exists.");
    }

    else writeResult(); // write result to output file   
}

void solver::solveN(int8_t N, int SLEEP_TIME_MS) // solve the next N cells in the grid, set SLEEP_TIME_MS for an animated solve!
{
    if(!isValid(grid)) // cannot solve grid as it already violates the constraints of Sudoku
    {
        writeError("Could not solve the specified grid as it violates the constraints of Sudoku - found the same number more than once in a row, column or box.");
        return;
    }

    countToSolve = N;
    if(countToSolve > countUnsolved) countToSolve = countUnsolved;
    sleepTimeMs = SLEEP_TIME_MS;

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

    for(int8_t numLoops = 0; numLoops <= countToSolve; ++numLoops) // if we don't solve at least one number every iteration (after the first initialisation pass), the grid is unsolvable
    {
        // check possible values for every empty cell
        for(int8_t currRow=0; currRow<9; ++currRow)
        {
            for(int8_t currCol=0; currCol<9; ++currCol)
            {
                if(grid[currRow][currCol] != 0) continue; // ignore completed cells

                // try all values in the empty cell, if the grid is still valid then that value is possible
                for(int8_t value=1; value<=9; ++value)
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
                    int8_t value = getPowerOfTwo(possibleValuesMask[currRow][currCol]);
                    setCell(cell(currRow, currCol), value);

                    if(finished) return;
                }

                else grid[currRow][currCol] = 0; // else reset cell to empty
            }
        } // cell loop

        // search every region to see if any values can only be in one cell
        for(int8_t currRegion=0; currRegion<27; ++currRegion) 
        {
            for(int8_t value=1; value<=9; ++value) // see if we can solve any of the numbers 1-9 for this region
            {
                solveValueForRegion(value, regions[currRegion]);

                if(finished) return; // stop if we've solved enough cells, continue otherwise
            } // value loop

            findHiddenPairs(regions[currRegion]); // look for hidden pairs

        } // region loop
    }
}

void solver::fillGridFromFile(char* fileIn) // reads the values from the file into the grid array
{
    countUnsolved = 0;

    FILE *input;
    fopen_s(&input, fileIn, "r");

    for(int8_t row=0; row<9; ++row)
    {
        for(int8_t column=0; column<9; ++column)
        {
            fscanf_s(input, "%hhu", &grid[row][column]);

            if(grid[row][column] == 0) ++countUnsolved;
        }
    }

    fclose(input);
}

void solver::writeError(char* message) // writes the specified message to the output file
{
    FILE *output;
    fopen_s(&output, file, "w+");
    fprintf(output, message);
    fclose(output);
}

void solver::writeResult() // writes the current grid state to the output file
{
    FILE *output;
    fopen_s(&output, file, "w+");

    for(int8_t row=0; row<9; ++row)
    {
        for(int8_t column=0; column<9; ++column)
        {
            if(grid[row][column] == 0) fprintf(output, "_ ");
            else fprintf(output, "%d ", grid[row][column]);
        }
        fprintf(output, "\n"); // print a new line every row
    }

    fclose(output);
}

bool solver::bruteForceSolve(int8_t row, int8_t column) // recursively try every value from 1 to 9 at the specified index and every empty cell onwards
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
    
    for(int8_t value=1; value<=9; ++value)
    {
        grid[row][column] = value;

        if(!isCellValid(grid, row, column)) continue; // if current value makes the grid invalid, continue to the next

        if(bruteForceSolve(row, column+1)) return true; // if all other empty cells can be filled, this value is correct!
    }

    // if no value from 1-9 is valid in this cell then the solution up to now is wrong
    grid[row][column] = 0; // remove the incorrect value, we'll try setting it again in another recursion
    return false; 
}

void solver::setCell(cell cell, int8_t value) // enter value into cell and write the result to file
{
    int8_t row = cell.row;
    int8_t column = cell.column;

    grid[row][column] = value;
    possibleValuesMask[row][column] = 0;

    assert(isCellValid(grid, row, column));

    writeResult();

    ++countSolved;
    if(countSolved == countToSolve) // stop if we've solved enough cells, continue otherwise
    {
        finished = true;
        return;
    }

    // we now know that value cannot go anywhere in the three regions containing the current cell; clear the appropriate bit for those cells
    {
        for(int8_t i=0; i<9; ++i)
        {
            possibleValuesMask[row][i] &= ~(1 << value); // row
            possibleValuesMask[i][column] &= ~(1 << value); // column

            assert(possibleValuesMask[row][i] || grid[row][i]);
            assert(possibleValuesMask[i][column] || grid[i][column]);
        }

        // round down the current row and column to the nearest factor of 3
        int8_t rowOffset = 3*(row/3);
        int8_t colOffset = 3*(column/3);

        for(int8_t rowIt=rowOffset; rowIt<3+rowOffset; ++rowIt)
        {
            for(int8_t columnIt=colOffset; columnIt<3+colOffset; ++columnIt)
            {
                possibleValuesMask[rowIt][columnIt] &= ~(1 << value); // box

                assert(possibleValuesMask[rowIt][columnIt] || grid[rowIt][columnIt]);
            }
        }
    }
    Sleep(sleepTimeMs); // sleep if desired, for an animated solve effect!
}

void solver::solveValueForRegion(int8_t value, cell region[9]) // checks where specified value could go in the specified region, and updates grid or possible values accordingly
{
    int8_t countCandidates = 0; // number of candidate cells where value could go
    cell candidateCells[3]; // co-ordinates of first 3 candidate cells

    for(int8_t currCell=0; currCell<9; ++currCell)
    {
        int8_t currRow = region[currCell].row;
        int8_t currCol = region[currCell].column;

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
            setCell(candidateCells[0], value);            
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
                    int8_t row = candidateCells[0].row;

                    for(int8_t currCol=0; currCol<9; ++currCol)
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
                    int8_t column = candidateCells[0].column;

                    for(int8_t currRow=0; currRow<9; ++currRow)
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
                int8_t rowOffset = 3*(candidateCells[0].row/3);
                int8_t colOffset = 3*(candidateCells[0].column/3);

                if( (isRow(region) && (colOffset == 3*(candidateCells[1].column/3)))
                    || (isColumn(region) && (rowOffset == 3*(candidateCells[1].row/3))))
                    {
                        for(int8_t rowIt=rowOffset; rowIt<3+rowOffset; ++rowIt)
                        {
                            for(int8_t columnIt=colOffset; columnIt<3+colOffset; ++columnIt)
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
            // if current region is a box, check if candidates are also in the same row or column
            if(isBox(region)) 
            {
                if(candidateCells[0].row == candidateCells[1].row
                    && candidateCells[0].row == candidateCells[2].row) // candidates are in the same row
                {
                    int8_t row = candidateCells[0].row;

                    for(int8_t currCol=0; currCol<9; ++currCol)
                    {
                        // clear possible value for non-candidate cells
                        if((currCol != candidateCells[0].column) 
                            && (currCol != candidateCells[1].column)
                            && (currCol != candidateCells[2].column))
                        {
                            possibleValuesMask[row][currCol] &= ~(1 << value);

                            assert(possibleValuesMask[row][currCol] || grid[row][currCol]);
                        }
                    }
                }
                else if(candidateCells[0].column == candidateCells[1].column
                        && candidateCells[0].column == candidateCells[2].column) // candidates are in the same column
                {
                    int8_t column = candidateCells[0].column;

                    for(int8_t currRow=0; currRow<9; ++currRow)
                    {
                        // clear possible value for non-candidate cells
                        if((currRow != candidateCells[0].row) 
                            && (currRow != candidateCells[1].row)
                            && (currRow != candidateCells[2].row))
                        {
                            possibleValuesMask[currRow][column] &= ~(1 << value);

                            assert(possibleValuesMask[currRow][column] || grid[currRow][column]);
                        }
                    }
                }
            }            
            else // else current region is a row or column, check if candidates are also in the same box
            {
                int8_t rowOffset = 3*(candidateCells[0].row/3);
                int8_t colOffset = 3*(candidateCells[0].column/3);

                if( (isRow(region) && (colOffset == 3*(candidateCells[1].column/3)) && (colOffset == 3*(candidateCells[2].column/3)))
                    || (isColumn(region) && (rowOffset == 3*(candidateCells[1].row/3)) && (rowOffset == 3*(candidateCells[2].row/3))))
                {
                    for(int8_t rowIt=rowOffset; rowIt<3+rowOffset; ++rowIt)
                    {
                        for(int8_t columnIt=colOffset; columnIt<3+colOffset; ++columnIt)
                        {
                            // clear possible value for non-candidate cells
                            if(((rowIt != candidateCells[0].row) || (columnIt != candidateCells[0].column))
                                && ((rowIt != candidateCells[1].row) || (columnIt != candidateCells[1].column))
                                && ((rowIt != candidateCells[2].row) || (columnIt != candidateCells[2].column)))
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
        default: break; // too many candidates, no info
    }
}

void solver::findHiddenPairs(cell region[9]) // search the specified region for hidden pairs: https://sudoku.com/sudoku-rules/hidden-pairs/
{
    for(int8_t cellA=0; cellA<9; ++cellA) 
    {
        int8_t cellARow = region[cellA].row;
        int8_t cellACol = region[cellA].column;

        if(grid[cellARow][cellACol] != 0) continue; // ignore completed cells

        for(int8_t cellB = cellA+1; cellB<9; ++cellB)
        {
            int8_t cellBRow = region[cellB].row;
            int8_t cellBCol = region[cellB].column;
            
            if(grid[cellBRow][cellBCol] != 0) continue; // ignore completed cells

            // store the values that could possibly be in both cells
            int16_t possibleValuesCommon = possibleValuesMask[cellARow][cellACol] 
                                        & possibleValuesMask[cellBRow][cellBCol];

            // now store all the values that could possibly be in the other 7 cells
            int16_t possibleValuesOther = 0;

            for(int8_t otherCell=0; otherCell<9; ++otherCell)
            {
                if(otherCell != cellA && otherCell != cellB)
                    possibleValuesOther |= possibleValuesMask[region[otherCell].row][region[otherCell].column];
            }
            
            // find the bits that are set in common but not other, i.e. the values that can only go in cellA and cellB
            possibleValuesCommon &= ~possibleValuesOther;

            // if there are 2 bits set, i.e. 2 values that can only go in cellA and cellB,
            // then they MUST go in those 2 cells. All other possibilities can be cleared
            if(getCountBitsSet(possibleValuesCommon) == 2)
            {
                possibleValuesMask[cellARow][cellACol] = possibleValuesCommon;
                possibleValuesMask[cellBRow][cellBCol] = possibleValuesCommon;
                break; // continue to next value for cellA
            }
            else for(int8_t cellC = cellB+1; cellC<9; ++cellC) // no hidden pair, but keep looking for hidden triples: https://sudoku.com/sudoku-rules/hidden-triples/
            {
                int8_t cellCRow = region[cellC].row;
                int8_t cellCCol = region[cellC].column;

                if(grid[cellCRow][cellCCol] != 0) continue; // ignore completed cells

                // store the values that could possibly be in all three cells
                possibleValuesCommon = possibleValuesMask[cellARow][cellACol] 
                                        & possibleValuesMask[cellBRow][cellBCol]
                                        & possibleValuesMask[cellCRow][cellCCol];

                // now store all the values that could possibly be in the other 6 cells
                possibleValuesOther = 0;

                for(int8_t otherCell=0; otherCell<9; ++otherCell)
                {
                    if(otherCell != cellA && otherCell != cellB && otherCell != cellC)
                        possibleValuesOther |= possibleValuesMask[region[otherCell].row][region[otherCell].column];
                }

                // find the bits that are set in common but not other, i.e. the values that can only go in cellA, cellB and cellC
                possibleValuesCommon &= ~possibleValuesOther;

                // if there are 3 bits set, i.e. 3 values that can only go in cellA, cellB, and cellC,
                // then they MUST go in those 3 cells. All other possibilities can be cleared
                if(getCountBitsSet(possibleValuesCommon) == 3)
                {
                    possibleValuesMask[cellARow][cellACol] &= possibleValuesCommon;
                    possibleValuesMask[cellBRow][cellBCol] &= possibleValuesCommon;
                    possibleValuesMask[cellCRow][cellCCol] &= possibleValuesCommon;
                    break; // continue to next value for cellB
                }
            }
        }
    }
}