#include "fibonacci.cpp"
#include <stdio.h>

int main()
{
    printFibonacci(0);
    printFibonacci(1);
    printFibonacci(10);
    printFibonacci(20);
    printf("\n");

    printFibonacciTermRecursive(0);
    printFibonacciTermRecursive(1);
    printFibonacciTermRecursive(30);
    //printFibonacciTermRecursive(50); //this takes over a minute!
    printFibonacciTermRecursive(77);
    printf("\n");

    printFibonacciTerm(0);
    printFibonacciTerm(1);
    printFibonacciTerm(30);
    printFibonacciTerm(50);
    printFibonacciTerm(76);
    printFibonacciTerm(77);
    printf("\n");

    compareFibonacciPerf(10);
    compareFibonacciPerf(20);
    compareFibonacciPerf(30);
    compareFibonacciPerf(40);
    //compareFibonacciPerf(50); //this takes over a minute!

    return 0;
}