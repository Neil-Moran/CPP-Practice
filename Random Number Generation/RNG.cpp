#include "RNG.h"
#include <chrono>

RNG::RNG()
{
    // seed RNG using current epoch
    using namespace std::chrono;
    seed = (unsigned int) system_clock::now().time_since_epoch().count();
    position = 0;
}

bool RNG::flipCoin()
{
    // NB: DO NOT update position, rollRandomChance already does
    return rollRandomChance(0.5);
}

bool RNG::rollRandomChance(double probabilityOfTrue)
{
    double roll = (double)(get1dNoiseUint())/(UINT32_MAX); // random value between 0 and 1
    ++position;

    if(roll <= probabilityOfTrue) return true;
    else return false;
}

unsigned int RNG::rollDie()
{
    // NB: DO NOT update position, rollRandomIntLessThan already does
    return rollRandomIntLessThan(6) + 1;
}

unsigned int RNG::rollRandomIntLessThan(unsigned int maxValueNotInclusive)
{
    double randomInt = (double)(get1dNoiseUint())/(UINT32_MAX) * maxValueNotInclusive; // random value between 0 and max value
    ++position;

    return (unsigned int) randomInt;
}

int RNG::rollRandomIntBetween(int minValueInclusive, int maxValueInclusive)
{
    // NB: DO NOT update position, rollRandomIntLessThan already does
    unsigned int randomInt = rollRandomIntLessThan(maxValueInclusive - minValueInclusive + 1);

    return randomInt + minValueInclusive;
}

unsigned int RNG::get1dNoiseUint()
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