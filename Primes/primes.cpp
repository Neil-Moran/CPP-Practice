#include <stdint.h>
#include <stdio.h>

void primes(const int MAX_LIMIT) //print all primes between 0 and the specified maximum limit
{    
    printf("All primes between 0 and %d: ", MAX_LIMIT);
    
    if(MAX_LIMIT<2)
    {
        printf("\n");
        return;
    }
    printf("2 "); //print 2 as we know it's the first prime, and this lets us skip all even integers later!

    //series denoting the odd integers starting from 3, i.e. f(i)=3+2i. If bit is 1 the integer is prime. We will unset the bits of non-primes using the Sieve of Eratosthenes below
    int NUM_BUCKETS = MAX_LIMIT/32+1; //the number of 64-bit ints we need is 1+ HALF the maximum limit/64, as we skip all even values!
    uint64_t *primeList = new uint64_t[NUM_BUCKETS];
    int bucketSize = sizeof(*primeList)*8;

    for(int i=0; i<NUM_BUCKETS; ++i) //initialise all bits to 1
    {
        primeList[i] = 0xFFFFFFFFFFFFFFFFULL;
    }
    
    int i=0; //start on index 0 which denotes 3, the next prime
    
    while(3+(2*i)<=MAX_LIMIT) //loop until we've reached the max limit
    {
        //figure out which array (and index within that array) i maps to
        int arrayBucket = i/bucketSize;
        int arrayOffset = i%bucketSize;

        if((primeList[arrayBucket] & (1ULL << arrayOffset)) != 0) //f(i) is prime if i-th bit is not 0
        {
            int prime = 3+(2*i); //translate from the index value to the actual prime value,
            printf("%d ", prime);

            for(int j=i+prime; j<MAX_LIMIT/2; j+=prime) //Sieve of Eratosthenes
            //knowing that index i is prime, we start at index i+prime
            //set the bit for that factor of prime to 0
            //increment the index by prime and repeat until we reach the max limit
            {
                primeList[j/bucketSize] &= ~(1ULL << j%bucketSize);
            }
        }
        ++i; //check if next odd number is prime
    }
    printf("\n");
    delete[] primeList;
}