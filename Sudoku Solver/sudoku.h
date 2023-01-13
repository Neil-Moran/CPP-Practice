#pragma once
#include <stdint.h>

void solve(char *fileIn, char *fileOut);
void solveNextNumber(char *fileIn, char *fileOut, int countToSolve = 1, int sleepTimeMs = 0);

struct cell
{
    int row, column;

    cell(){};
    cell(int row, int column)
    {
        this->row = row;
        this->column = column;
    };
};

struct solver
{
    int grid[9][9];
    int16_t possibleValuesMask[9][9]; // stores the possible values for every empty cell, e.g. if 4th bit is set then 4 is still a possible value
    char *file;
    int countToSolve;
    int countSolved;
    int sleepTimeMs;
    bool finished;

    solver(char *fileIn, char *fileOut, int countToSolve, int sleepTimeMs);
    void write();
    void writeCell(cell cell, int value);
    void solveValueForRegion(int value, cell region[]);
    void solveNextNumber();
};