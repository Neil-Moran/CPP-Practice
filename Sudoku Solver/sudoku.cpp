#pragma once

#include <stdio.h>
#include <Windows.h>
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

        // all values should be 0 or 1, so OR-ing them should be 0 or 1 also
        if((countOnes | countTwos | countThrees
            | countFours | countFives | countSixes
            | countSevens | countEights | countNines) > 1) return false;
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

bool isCellValid(int grid[], int cell) // checks that the regions of the grid containing the specified cell do not violate Sudoku constraints, but does not check for solvability
{    
    if(!isRegionValid(grid, regions[getRow(cell)])) return false; // check row is valid
    if(!isRegionValid(grid, regions[getColumn(cell)])) return false; // check column is valid
    // finding the box co-ord looks ugly but is intuitive; 
    // box row (from 0-2) = row/3 = cell/27
    // box column (from 0-2) = column/3 = (cell%9)/3
    // box co-ord (from 0-9) = 3*box row + box column
    // NB: 3*row/3 != row as it is an integer and gets rounded down when divided!
    if(!isRegionValid(grid, regions[getBox(cell)])) return false; // check box is valid

    return true; // all three regions are still valid
}

bool bruteForceSolve(int grid[], int index = 0) // recursively try every value from 1 to 9 at the specified index and every empty cell onwards
{  
    // note: assumes the grid is a proper Sudoku, i.e. there is only one solution

    while(index < 81 && grid[index] != 0) ++index; //find the next empty cell

    if(index >= 81) return true; // if we've filled all cells then this solution is correct!
    
    for(int value=1; value<=9; ++value)
    {
        grid[index] = value;

        if(!isCellValid(grid, index)) continue; // if current value makes the grid invalid, continue to the next

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
        
        if(grid[i] == 0) fprintf(output, "_ ");
        else fprintf(output, "%d ", grid[i]);
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

void solveNextNumber(char *fileIn, char *fileOut, int countToSolve) // solves next N cells in the grid
{
    int grid[81];
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
    int possibleValues[81] = {0}; // stores the possible values for every empty cell, e.g. if 4th bit is set then 4 is still a possible value

    for(int i=0; i<81; ++i) // initialise possible values
    {
        if(grid[i] == 0) possibleValues[i] = 0b1111111110;
    }
    
    for(int numLoops = 0; numLoops <= countToSolve; ++numLoops) // if we don't solve at least one number every iteration (after the first initialisation pass), the grid is unsolvable
    {
        printf("Starting Loop %i\n", numLoops);
        // check possible values for every empty cell
        for(int currCell=0; currCell<81; ++currCell)
        {
            if(grid[currCell] != 0) continue; // ignore completed cells

            // try all values in the empty cell, if the grid is still valid then that value is possible
            for(int value=1; value<=9; ++value)
            {
                if(!(possibleValues[currCell] & (1 << value))) continue; // skip if we already know value is not possible
                grid[currCell] = value;

                if(!isCellValid(grid, currCell)) // if grid is now invalid remove possible value for this cell
                    possibleValues[currCell] &= ~(1 << value); 
            }
            if(possibleValues[currCell] == 0)
                printf("Made a mistake! \n"); 

            if((possibleValues[currCell] & (possibleValues[currCell] - 1)) == 0) // if possible value is a power of 2 there is only one possible value
            {
                // find the correct value
                int value = 1;
                while((possibleValues[currCell] >> value) != 1 && value <= 9) 
                    ++value;

                grid[currCell] = value;
                possibleValues[currCell] = 0;

                if(!isCellValid(grid, currCell)) 
                printf("Made a mistake! \n");                

                writeGridToFile(fileOut, grid);

                ++countSolved;
                if(countSolved == countToSolve) return; // stop if we've solved enough cells, continue otherwise

                // we now know that value cannot go anywhere in the three regions containing the current cell; clear the appropriate bit for those cells
                int row = getRow(currCell);
                int column = getColumn(currCell);
                int box = getBox(currCell);

                for(int i=0; i<9; ++i)
                {
                    possibleValues[regions[row][i]] &= ~(1 << value); // row
                    possibleValues[regions[column][i]] &= ~(1 << value); //column
                    possibleValues[regions[box][i]] &= ~(1 << value); // box
                }
                Sleep(300);
            }

            else grid[currCell] = 0; // else reset cell to empty
        } // cell loop

        // search every region to see if any values can only be in one cell
        for(int currRegion=0; currRegion<27; ++currRegion)
        {
            for(int value=1; value<=9; ++value) // see if we can solve any of the numbers 1-9 for this region
            {
                int countCandidates = 0; // number of candidate cells where value could go
                int cell1 = -999, cell2 = -999, cell3 = -999;

                for(int currCell=0; currCell<9; ++currCell)
                {
                    if((possibleValues[regions[currRegion][currCell]] & (1 << value)) > 0) // value can go in currCell
                    {   
                        switch (countCandidates++) // note the increment
                        {
                        case 0: // first candidate
                            cell1 = currCell;
                            break;
                        // if there is more than one candidate cell, we don't know where value goes 
                        // but we may have new info if there are only 2 or 3
                        case 1: // second candidate
                            cell2 = currCell;
                            break;
                        case 2: // third candidate
                            cell3 = currCell;
                            break;                        
                        // if there are more than 3 then no possible info, continue to next value
                        default: currCell = 10; // this will terminate the for loop                            
                        }
                    }
                }
                switch(countCandidates)
                {
                    case 1: // found where value goes
                    {
                        int cell = regions[currRegion][cell1];
                        grid[cell] = value;
                        possibleValues[cell] = 0;

                        if(!isCellValid(grid, cell)) 
                        printf("Made a mistake! \n");

                        writeGridToFile(fileOut, grid);                    

                        ++countSolved;
                        if(countSolved == countToSolve) return; // stop if we've solved enough cells, continue otherwise

                        // we now know value cannot go anywhere in the three regions containing the current cell; clear the value-th bit for those cells
                        // however we can ignore the current region - the reason we're here is because value couldn't go anywhere else there
                        int region1, region2;

                        if(currRegion < 9) // current region is row
                        {
                            region1 = getColumn(cell); // column
                            region2 = getBox(cell); // box
                        }
                        else if (currRegion < 18) // current region is column
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

                            if((!possibleValues[regions[region1][i]] && !grid[regions[region1][i]]) || (!possibleValues[regions[region2][i]] && !grid[regions[region2][i]]))
                                printf("Made a mistake! \n");  
                        }
                        Sleep(300);
                    }
                        break;

                    // if value only has 2 or 3 candidates in the current region that are also all in another region, we can eliminate value from other cells in that region
                    // e.g. see Step 14 here: https://www.websudoku.com/images/example-steps.html
                    case 2: // pointing pairs: https://sudoku.com/sudoku-rules/pointing-pairs/
                    {
                        // transform cells from region space to grid space
                        cell1 = regions[currRegion][cell1];
                        cell2 = regions[currRegion][cell2];

                        if(currRegion >= 18) // if current region is a box, check if candidates are in the same row or column
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

                                    if(!possibleValues[regions[row][i]] && !grid[regions[row][i]])
                                        printf("Made a mistake! \n"); 
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
                                
                                    if(!possibleValues[regions[column][i]] && !grid[regions[column][i]])
                                        printf("Made a mistake! \n");
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

                                    if(!possibleValues[regions[box][i]] && !grid[regions[box][i]])
                                        printf("Made a mistake! \n");
                                }
                            }
                        }
                    }
                        break;

                    case 3: // pointing triples: https://sudoku.com/sudoku-rules/pointing-triples/
                    {
                        // transform cells from region space to grid space
                        cell1 = regions[currRegion][cell1];
                        cell2 = regions[currRegion][cell2];
                        cell3 = regions[currRegion][cell3];

                        if(currRegion >= 18) // if current region is a box, check if candidates are in the same row or column
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

                                    if(!possibleValues[regions[row][i]] && !grid[regions[row][i]])
                                        printf("Made a mistake! \n"); 
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
                                
                                    if(!possibleValues[regions[column][i]] && !grid[regions[column][i]])
                                        printf("Made a mistake! \n");
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

                                    if(!possibleValues[regions[box][i]] && !grid[regions[box][i]])
                                        printf("Made a mistake! \n");
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
                    int possibleValuesCommon = possibleValues[regions[currRegion][firstCell]] 
                                                & possibleValues[regions[currRegion][secondCell]];

                    // now store all the values that could possibly be in the other 7 cells
                    int possibleValuesOther = 0;

                    for(int otherCell=0; otherCell<9; ++otherCell)
                    {
                        if(otherCell != firstCell && otherCell != secondCell)
                            possibleValuesOther |= possibleValues[regions[currRegion][otherCell]] ;
                    }

                    // find the bits that are set in common but not other, i.e. the values that can only go in firstCell and secondCell
                    possibleValuesCommon &= ~possibleValuesOther;

                    // count the bits set, i.e. the number of values that can only go in firstCell and secondCell
                    // https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
                    int countBits = 0;

                    for(int bitsCopy = possibleValuesCommon; bitsCopy; ++countBits)
                    {
                        bitsCopy &= bitsCopy - 1;
                    }

                    // if there are 2 bits set, i.e. 2 values that can only go in firstCell and secondCell,
                    // then they MUST go in those 2 cells. All other possibilities can be cleared
                    if(countBits == 2)
                    {
                        possibleValues[regions[currRegion][firstCell]] = possibleValuesCommon;
                        possibleValues[regions[currRegion][secondCell]] = possibleValuesCommon;
                    }
                }
            }
        } // region loop
    }
}