#include <stdio.h>
#define ULL_MAX 18446744073709551615 //max possible value for unsigned long long

void primes(int n) //print the first n primes
{
    if(n==0) return;
    printf("First %d primes: 2 ", n); //print 2 as we know it's the first prime
    --n; //decrement prime counter

    unsigned long long primeList = ULL_MAX; //binary list of 1s denoting which indices are prime. We will unset non-prime indices below using the sieve of eratosthenes

    int i=3; //start on 3, the next prime

    while(n>0) //loop until we've printed n primes
    {
        if((primeList & (1Ull << i)) != 0) //i is prime if i-th bit is not 0
        {
            printf("%d ", i);

            for(int j=3*i; j<sizeof(unsigned long long)*8; j+=i) //unset prime flag for every factor of i
            //we start at j = 3i as we've just processed i and 2i must be even, 
            //we already skip even integers by incrementing i by 2 below
            {
                primeList &= ~(1ULL << j);
            }
            --n; //decrement prime counter
        }
        i+=2; //check if next odd number is prime
    }

    printf("\n");
}