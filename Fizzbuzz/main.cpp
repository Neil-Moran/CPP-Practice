#include "fizzbuzz.h"

void main()
{
    fizzbuzz(30);
    fizzbuzz(100);

    fizzbuzz(100, "fizzbuzz100.txt");

    fizzbuzzNoModulo(30);

    profileFizzbuzz();
    profileFizzbuzzNoModulo();
}