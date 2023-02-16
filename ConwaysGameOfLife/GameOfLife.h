#include <vector>

struct cell
{
    friend struct game;

    private:
    bool curr, next;
};

struct game
{
    game(char* fileIn, char* fileOut = "");

    void play();

    private:
    char* file;
    int width, height;
    std::vector<std::vector<cell>> cells;

    void calculate();
    void update();
    void write();
};