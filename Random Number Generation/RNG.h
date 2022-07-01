#pragma once

class RNG
{
public:
    RNG();
    bool flipCoin();
    bool rollRandomChance(double probabilityOfTrue);

private:
    unsigned int seed;
    int position;
    unsigned int Get1dNoiseUint();
};