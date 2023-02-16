#include "GameOfLife.h"
#include <stdio.h>
#include <Windows.h>

const int NUM_ITERATIONS = 10;
const int SLEEP_TIME_MS = 1000;

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

    for(int currRow=0; currRow<height; ++currRow)
    {
        for(int currCol=0; currCol<width; ++currCol)
        {
            fscanf_s(input, "%d", &temp);

            if(temp == 1)
            {
                cells[currRow][currCol].curr = true;
            }
            else
            {
                cells[currRow][currCol].curr = false;        
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
    // iterate over every cell and calculate if it should be alive next generation    
    for(int currRow=0; currRow<height; ++currRow)
    {
        for(int currCol=0; currCol<width; ++currCol)
        {
            if(calculateCell(currRow, currCol))
                cells[currRow][currCol].next = true;
        }
    }
}

bool game::calculateCell(int row, int col)
{
    /* 
        From https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Rules:
        - Any live cell with two or three live neighbours survives.
        - Any dead cell with three live neighbours becomes a live cell.
        - All other live cells die in the next generation. Similarly, all other dead cells stay dead.
    */

   int countLiveNeighbours = 0;

    // check state of all neighbours (NB: check neighbour exists, current cell may be on the edge of the grid)
    for(int currRow = (row!=0) ? row-1 : 0; currRow<=row+1 && currRow<height; ++currRow)
    {
        for(int currCol = (col!=0) ? col-1 : 0; currCol<=col+1 && currCol<width; ++currCol)
        {
            if(currRow == row && currCol == col) continue; // ignore the current cell itself

            if(cells[currRow][currCol].curr)
            {
                ++countLiveNeighbours;

                if(countLiveNeighbours > 3) return false; // if 4+ live neighbours this cell will definitely die/stay dead, can stop here
            }
        }
    }

    if(cells[row][col].curr) // cell is currently alive
    {
        if(countLiveNeighbours >= 2) // we already checked above that countLiveNeighbours <= 3
            return true;
    }           
    else // cell is currently dead
    {
        if(countLiveNeighbours == 3)
            return true;
    }

    return false;
}

void game::update()
{
    for(int currRow=0; currRow<height; ++currRow)
    {
        for(int currCol=0; currCol<width; ++currCol)
        {
            cells[currRow][currCol].curr = cells[currRow][currCol].next;
            cells[currRow][currCol].next = false;
        }
    }
}

void game::write()
{
    FILE *output;
    fopen_s(&output, file, "w+");

    fprintf(output, "%d %d", width, height);

    for(int currRow=0; currRow<height; ++currRow)
    {
        fprintf(output, "\n");

        for(int currCol=0; currCol<width; ++currCol)
        {
            if(cells[currRow][currCol].curr)
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