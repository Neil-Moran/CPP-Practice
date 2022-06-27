#include "RNG.h"
#include <chrono>

RNG::RNG()
{
    // seed RNG using current epoch
    using namespace std::chrono;
    seed = (unsigned int) system_clock::now().time_since_epoch().count();
    position = 0;
}

RNG::~RNG()
{
}

unsigned int RNG::Get1dNoiseUint()
{
    /* implementation of the Squirrel3 noise/RNG algorithm created by Squirrel Eiserloh:
    http://www.eiserloh.net/bio/

    ...described in his GDC 2017 talk "Noise-Based RNG":
    https://www.youtube.com/watch?v=LWFzPP8ZbdU
    */
    const unsigned int BIT_NOISE1 = 0x68E31DA4;
    const unsigned int BIT_NOISE2 = 0xB5297A4D;
    const unsigned int BIT_NOISE3 = 0x1B56C4E9;

    unsigned int mangledBits = (unsigned int) position;
    mangledBits *= BIT_NOISE1;
    mangledBits += seed;
    mangledBits ^= (mangledBits >> 8);
    mangledBits += BIT_NOISE2;
    mangledBits ^= (mangledBits << 8);
    mangledBits *= BIT_NOISE3;
    mangledBits ^= (mangledBits >> 8);
    return mangledBits;
}

bool RNG::flipCoin()
{
    double flip = (double)(Get1dNoiseUint())/(4294967295); // random value between 0 and 1
    ++position;

    if(flip < 0.5) return false;
    else return true;
}