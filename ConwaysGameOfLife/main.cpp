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
    {
        game game3("input3.txt", "output3.txt");
        game3.play(150, 200);
    }
    return 0;
}