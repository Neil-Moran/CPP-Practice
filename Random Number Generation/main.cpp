#include "RNG.h"
#include <stdio.h>

void flipCoins(int numFlips)
{
    int tailCount = 0, headCount = 0;

    RNG coinFlipRNG;

    for(int i=0; i<numFlips; ++i)
    {
        switch (coinFlipRNG.flipCoin())
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

void rollChances(double probabilityOfTrue, int numRolls)
{
    int passCount = 0, failCount = 0;

    RNG rollChanceRNG;

    for(int i=0; i<numRolls; ++i)
    {
        switch (rollChanceRNG.rollRandomChance(probabilityOfTrue))
        {
        case false:
            printf("0 ");
            ++failCount;
            break;
        
        case true:
            printf("1 ");
            ++passCount;
            break;
        }
    }
    printf("\nP(Pass): %.2f | P(Fail): %.2f\n#Passes: %i | #Fails: %i\n", probabilityOfTrue, (1-probabilityOfTrue), failCount, passCount);
}

void rollIntsLessThan(unsigned int maxValue, int numRolls)
{
    RNG rollIntsRNG;

    for(int i=0; i<numRolls; ++i)
    {
        printf("%i ", rollIntsRNG.rollRandomIntLessThan(maxValue));
    }
    printf("\n");
}

void rollIntsBetween(int minValue, int maxValue, int numRolls)
{
    RNG rollIntsRNG;

    for(int i=0; i<numRolls; ++i)
    {
        printf("%i ", rollIntsRNG.rollRandomIntBetween(minValue, maxValue));
    }
    printf("\n");
}

void rollDice(int numRolls)
{
    RNG rollDiceRNG;

    for(int i=0; i<numRolls; ++i)
    {
        printf("%i ", rollDiceRNG.rollDie());
    }
    printf("\n");
}

int main()
{
    flipCoins(1000);
    printf("\n");
    rollChances(0.75, 1000);
    printf("\n");
    rollIntsLessThan(10, 100);
    printf("\n");
    rollIntsBetween(-5, 5, 100);
    printf("\n");
    rollDice(1000);

    return 0;
}