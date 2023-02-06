#include "GameOfLife.h"
#include <stdio.h>

game::game(char* fileIn, char* fileOut)
{
    file = fileOut ? fileOut : fileIn; // if fileOut is blank output to the input file

    FILE *input;
    fopen_s(&input, fileIn, "r");

    if(!input)
    {
        printf("Could not open input file: %s\n", fileIn);
        return;
    }
}

void game::play()
{
    if(cells.empty()) return;
}