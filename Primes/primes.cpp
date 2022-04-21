#include <stdio.h>
#define ULL_MAX 18446744073709551615 //max possible value for unsigned long long

void primes(int n) //print the first n primes
{
    if(n==0) return;
    printf("First %d primes: ", n);

    unsigned long long primeList = ULL_MAX; //list of 1s denoting which indices are prime. We will unset non-prime indices below using the sieve of eratosthenes

    int i=2; //skip 0 and 1, we know they're not prime

    while(n>0) //loop until we've printed n primes
    {
        if((primeList & (1Ull << i)) != 0) //i is prime if i-th bit is not 0
        {
            printf("%d ", i);

            for(int j=i+i; j<sizeof(unsigned long long)*8; j+=i) //unset prime flag for every factor of i
            {
                primeList &= ~(1ULL << j);
            }
            --n; //decrement prime counter
        }
        ++i; //check if next number is prime
    }

    printf("\n");
}