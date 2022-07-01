#pragma once

class RNG
{
public:
    RNG();
    bool flipCoin();
    bool rollRandomChance(double probabilityOfTrue);
    unsigned int rollDie();
    unsigned int rollRandomIntLessThan(unsigned int maxValueNotInclusive);
    int rollRandomIntBetween(int minValueInclusive, int maxValueInclusive);

private:
    unsigned int seed;
    int position;
    unsigned int get1dNoiseUint();
};