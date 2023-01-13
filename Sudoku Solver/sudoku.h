#pragma once
#include <stdint.h>

void solve(char *fileIn, char *fileOut); // attempts to solve the grid from the input file by brute force, and writes the result to the output file
void solveN(char *fileIn, char *fileOut, int8_t countToSolve = 1, int sleepTimeMs = 0); // solves next N cells in the grid from the input file, and writes the result to the output file

struct cell
{
    int8_t row, column;

    cell(){};
    cell(int8_t row, int8_t column)
    {
        this->row = row;
        this->column = column;
    };
};

struct solver
{
    solver(char *fileIn, char *fileOut);
    
    void solveFull(); // attempt to solve the grid fully by brute force
    void solveN(int8_t N = 1, int SLEEP_TIME_MS = 0); // solve the next N cells in the grid, set SLEEP_TIME_MS for an animated solve!

    private:
    int8_t grid[9][9];
    int16_t possibleValuesMask[9][9]; // stores the possible values for every empty cell, e.g. if 4th bit is set then 4 is still a possible value
    char *file;
    int8_t countUnsolved;
    int8_t countSolved;
    int8_t countToSolve;
    int sleepTimeMs;
    bool finished;
    
    void fillGridFromFile(char* fileIn);
    void writeError(char* message);
    void writeResult();
    bool bruteForceSolve(int8_t row = 0, int8_t column = 0);
    void setCell(cell cell, int8_t value);
    void solveValueForRegion(int8_t value, cell region[9]);
    void findHiddenPairs(cell region[9]);    
};