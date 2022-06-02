/*  Quick and dirty way of timing C++ code
    Use TIME_START to start timing
    Use TIME_END to stop timing and print the elapsed time in seconds */

#include <chrono>
using namespace std::chrono; 
#define TIME_START high_resolution_clock::time_point start = high_resolution_clock::now();
#define TIME_END high_resolution_clock::time_point end = high_resolution_clock::now(); nanoseconds elapsed = duration_cast<nanoseconds>(end - start); printf("Time: %.8f seconds\n", elapsed.count() * 1e-9);