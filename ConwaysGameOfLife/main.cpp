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
    {
        game game2("input2.txt");
        game2.play();
    }
    return 0;
}