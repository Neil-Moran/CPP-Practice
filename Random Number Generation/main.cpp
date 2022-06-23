#include "squirrel3.h"
#include <stdio.h>

void printRandomUInt(int n, const unsigned int seed) //print n random but deterministic uints for the given seed
{
    for(int i=0; i<n; ++i)
    {
        printf("%u ", Get1dNoiseUint(i, seed));
    }
}

int main()
{
    printRandomUInt(1000, 0);

    return 0;
}