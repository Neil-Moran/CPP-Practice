#pragma once

class RNG
{
private:
    unsigned int seed;
    int position;
    unsigned int Get1dNoiseUint();
public:
    RNG();
    ~RNG();
    bool flipCoin();
};