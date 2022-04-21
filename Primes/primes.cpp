#include <stdio.h>
#define ULL_MAX 18446744073709551615 //max possible value for unsigned long long

void primes(int n) //print the first n primes
{
    if(n==0) return;
    printf("First %d primes: 2 ", n); //print 2 as we know it's the first prime
    --n; //decrement prime counter

    unsigned long long primeList = ULL_MAX; //series denoting the odd integers starting from 3, i.e. f(i)=3+2i. All bits initialised to 1; if bit is 1 the integer is prime. We will unset the bits of non-primes using the Sieve of Eratosthenes below

    int i=0; //start on index 0 which denotes 3, the next prime

    while(n>0) //loop until we've printed n primes
    {
        if((primeList & (1Ull << i)) != 0) //f(i) is prime if i-th bit is not 0
        {
            int prime = 3+(2*i); //translate from the index value to the actual prime value,
            printf("%d ", prime);

            for(int j=i+prime; j<sizeof(unsigned long long)*8; j+=prime) //Sieve of Eratosthenes
            //knowing that index i is prime, we start at index i+prime
            //set the bit for that factor of prime to 0
            //increment the index by prime and repeat until at the end of the primeList
            {
                primeList &= ~(1ULL << j);
            }
            --n; //decrement prime counter
        }
        ++i; //check if next odd number is prime
    }

    printf("\n");
}