#pragma once

#include <stdint.h>

// https://graphics.stanford.edu/~seander/bithacks.html

inline bool isPowerOfTwo(int16_t n)
{
    return (n & (n-1)) == 0;
}

inline int getPowerOfTwo(int16_t n) // assumes n is a power of two
{
    int result = 1;

    while((n >> result) > 1) 
        ++result;

    return result;
}

inline int getCountBitsSet(int16_t n)
{
    int result = 0;

    while(n)
    {
        n &= n - 1;
        ++result;
    }

    return result;
}