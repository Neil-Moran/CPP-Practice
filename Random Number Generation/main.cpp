#include "squirrel3.h"
#include <stdio.h>

void printRandomUInt(int n, const unsigned int seed) //print n random but deterministic uints for the given seed
{
    for(int i=0; i<n; ++i)
    {
        printf("%u ", (Get1dNoiseUint(i, seed)));
    }
    printf("\n");
}

void flipCoins(int n)
{
    int tailCount =0, headCount = 0;

    for(int i=0; i<n; ++i)
    {
        switch (flipCoin())
        {
        case false:
            printf("T ");
            ++tailCount;
            break;
        
        case true:
            printf("H ");
            ++headCount;
            break;
        }
    }
    printf("\n#Heads: %i | #Tails: %i\n", headCount, tailCount);
}

int main()
{
    printRandomUInt(1000, 0);
    flipCoins(1000);

    return 0;
}