/* implementation of the Squirrel3 noise/RNG algorithm created by Squirrel Eiserloh:
http://www.eiserloh.net/bio/

...described in his GDC 2017 talk "Noise-Based RNG":
https://www.youtube.com/watch?v=LWFzPP8ZbdU
*/

unsigned int Get1dNoiseUint(int position, unsigned int seed)
{
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

bool flipCoin()
{
    static int pos = 0;

    double flip = (double)(Get1dNoiseUint(pos, 123456789))/(4294967295); // random value between 0 and 1
    ++pos;

    if(flip < 0.5) return false;
    else return true;
}