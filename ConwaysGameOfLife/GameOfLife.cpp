#include "GameOfLife.h"
#include <stdio.h>
#include <Windows.h>

const int NUM_ITERATIONS = 10;
const int SLEEP_TIME_MS = 300;

game::game(char* fileIn, char* fileOut)
{
    file = (fileOut && fileOut[0]) ? fileOut : fileIn; // if fileOut is null or empty output to the input file

    FILE *input;
    fopen_s(&input, fileIn, "r");

    if(!input)
    {
        printf("Could not open input file: %s\n", fileIn);
        return;
    }

    fscanf_s(input, "%d", &width);
    fscanf_s(input, "%d", &height);

    cells.resize(height, std::vector<cell>(width));
    
    int temp = -1;

    for(int i=0; i<height; ++i)
    {
        for(int j=0; j<width; ++j)
        {
            fscanf_s(input, "%d", &temp);

            if(temp == 1)
            {
                cells[i][j].curr = true;
            }
            else
            {
                cells[i][j].curr = false;        
            }
        }
    }

    fclose(input);
}

void game::play()
{
    if(cells.empty()) return;

    for(int loop=0; loop<NUM_ITERATIONS; ++loop)
    {
        calculate();
        update();
        write();
        Sleep(SLEEP_TIME_MS);
    }
}

void game::calculate()
{
    for(int i=0; i<height; ++i)
    {
        for(int j=0; j<width; ++j)
        {
            cells[i][j].next = cells[i][j].curr;            
        }
    }
}

void game::update()
{
    for(int i=0; i<height; ++i)
    {
        for(int j=0; j<width; ++j)
        {
            cells[i][j].curr = cells[i][j].next;
            cells[i][j].next = false;
        }
    }
}

void game::write()
{
    FILE *output;
    fopen_s(&output, file, "w+");

    fprintf(output, "%d %d", width, height);

    for(int i=0; i<height; ++i)
    {
        fprintf(output, "\n");

        for(int j=0; j<width; ++j)
        {
            if(cells[i][j].curr)
            {
                fprintf(output, "1 ");
            }
            else 
            {
                fprintf(output, "0 ");
            }
        }
    }

    fclose(output);
}