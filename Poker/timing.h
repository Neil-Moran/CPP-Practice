/*  Quick way of timing C++ code
    Create an instance of Timer to start timing
    Destroy Timer to stop timing and print the elapsed time in seconds */

#include <chrono>
using namespace std::chrono;

class Timer
{
    public:
    Timer();
    ~Timer();

    private:
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
};

Timer::Timer()
{
    start = high_resolution_clock::now();
}

Timer::~Timer()
{
    end = high_resolution_clock::now();
    nanoseconds elapsed = duration_cast<nanoseconds>(end - start); 
    printf("Time: %.8f seconds\n", elapsed.count() * 1e-9);
}