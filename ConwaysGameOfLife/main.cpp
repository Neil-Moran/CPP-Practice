#include "GameOfLife.h"

int main()
{
    {
        game game0("FileThatDoesNotExist.txt");
        game0.play();
    }
    return 0;
}