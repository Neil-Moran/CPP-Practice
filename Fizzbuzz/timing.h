/*  Quick way of timing C++ code
    Create an instance of Timer to start timing
    (optional) Use stop() to stop timing
    Destroy Timer to stop timing (if not already) and print the elapsed time in seconds */

#pragma once
#include <chrono>
#include <stdio.h>

using namespace std::chrono;

class Timer
{
    public:
    Timer();
    ~Timer();
    void stop();

    private:
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    double elapsed;
};

Timer::Timer()
{
    start = high_resolution_clock::now();
    elapsed = 0;
}

Timer::~Timer()
{
    if(elapsed == 0) // calculate elapsed if stop() was never called
    {
        end = high_resolution_clock::now();
        nanoseconds timeDiff = duration_cast<nanoseconds>(end - start); 
        elapsed = (double)timeDiff.count();
    }
    printf("Time: %.8f seconds\n",  elapsed * 1e-9);
}

void Timer::stop()
{
    end = high_resolution_clock::now();
    nanoseconds timeDiff = duration_cast<nanoseconds>(end - start);
    elapsed = (double)timeDiff.count();
}