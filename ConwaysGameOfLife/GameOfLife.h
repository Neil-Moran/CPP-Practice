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

    void play(int NUM_GENERATIONS = 10, int SLEEP_TIME_MS = 1000);

    private:
    char* file;
    int width, height;
    std::vector<std::vector<cell>> cells;

    void calculate();
    bool calculateCell(int row, int col);
    void update();
    void write();
};