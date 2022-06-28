#include "timing.h"
#include <stdint.h>
#include <stdio.h>
#include <string>

void primes(const int MAX_LIMIT) //print all primes between 0 and the specified maximum limit
{   
    printf("All primes between 0 and %d: ", MAX_LIMIT);
    
    Timer timer;

    if(MAX_LIMIT<2)
    {
        printf("\n");
        return;
    }

    //Series denoting the odd integers starting from 3, i.e. f(i)=3+2i. If bit is 1 the integer is prime. 
    //We will unset the bits of non-primes using the Sieve of Eratosthenes below
    int NUM_BUCKETS = MAX_LIMIT/32 + 1; //the number of 64-bit ints we need is 1 + HALF the maximum limit/64, as we skip all even values!
    uint64_t *primeList = new uint64_t[NUM_BUCKETS];
    int bucketSize = sizeof(*primeList)*8;

    for(int i=0; i<NUM_BUCKETS; ++i) //initialise all bits to 1
    {
        primeList[i] = 0xFFFFFFFFFFFFFFFFULL;
    }

    std::string primes = "2 "; //add 2 to output as we know it's the first prime, and this lets us skip all even integers later! 

    for(int i=0, arrayBucket=0, arrayOffset=0; //i is our global index but we have multiple arrays; arrayBucket is the current array and arrayOffset is the index into the current array
        i <= (MAX_LIMIT-3)/2; //loop until we've reached the max limit, i.e. while 3+2i <= MAX_LIMIT
        ++i, ++arrayOffset) 
    {
        if(arrayOffset==bucketSize) //if we've reached the end of current array, move to next one
        {
            arrayOffset = 0;
            ++arrayBucket;
        }

        if((primeList[arrayBucket] & (1ULL << arrayOffset)) != 0) //f(i) is prime if i-th bit is not 0
        {
            int prime = 3+(2*i); //translate from the index value to the actual prime value
            primes.append(std::to_string(prime).append(" "));
            
            for(int j=i+prime; j<MAX_LIMIT/2; j+=prime) //Sieve of Eratosthenes
            //knowing that index i is prime, we start at index i+prime
            //set the bit for that factor of prime to 0
            //increment the index by prime and repeat until we reach the max limit
            {
                primeList[j/bucketSize] &= ~(1ULL << j%bucketSize);
            }            
        }
    }

    timer.stop();
    printf("%s\n", primes.c_str());
    
    delete[] primeList;
}

bool isPrime(const uint64_t n)
{
    if(n<2) return false;
    if(n==2) return true;
    if((n&1) == 0) return false; //check if n is even now, if not we only need to check for odd factors below

    const double SQRT_N = sqrt(n);

    for(int i=3; i<= SQRT_N; i+=2)
    {
        if(n%i ==0) return false;
    }
    return true;
}