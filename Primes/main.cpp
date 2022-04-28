#include "primes.cpp"

void main()
{
    primes(1000);
    printf("Is 1000 prime: %s\n", isPrime(999) ? "True" : "False");
    printf("Is 9999991 prime: %s\n", isPrime(9999991) ? "True" : "False");
}