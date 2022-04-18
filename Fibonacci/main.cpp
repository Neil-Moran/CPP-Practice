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
    printFibonacciTermRecursive(50);
    printFibonacciTermRecursive(77);
    printf("\n");

    printFibonacciTerm(0);
    printFibonacciTerm(1);
    printFibonacciTerm(30);
    printFibonacciTerm(50);
    printFibonacciTerm(76);
    printFibonacciTerm(77);
    printf("\n");

    return 0;
}