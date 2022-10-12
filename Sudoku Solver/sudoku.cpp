#pragma once

#include <stdio.h>
#include "sudoku.h"

void print(int grid[]) // print the current state of the grid, for testing
{
    for(int i=0, j=0; i<81; ++i, ++j)
    {
        printf("%i ", grid[i]);

        if(j == 8) // print a new line every row (9 values)
        {
            printf("\n");
            j = -1;
        }
    }
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

    bool completed = false; // completed either means the Sudoku is solved or our algorithm cannot solve it any further

    while(!completed)
    {
        completed = true;

        for(int i=0; i<81; ++i)
        {
            if(grid[i] != 0) continue; // ignore solved values
            
        }
    }

    print(grid);

    fclose(input);

    // write result to output file
    FILE *output;
    fopen_s(&output, fileOut, "w+");

    for(int i=0, j=0; i<81; ++i, ++j)
    {
        fprintf(output, "%d ", grid[i]);

        if(j == 8) // print a new line every row (9 values)
        {
            fprintf(output, "\n");
            j = -1;
        }
    }

    fclose(output);
}