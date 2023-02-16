#include "GameOfLife.h"

int main()
{
    {
        game game0("FileThatDoesNotExist.txt");
        game0.play();
    }
    {
        game game1("input1.txt");
        game1.play();
    }
    return 0;
}