#pragma once
#include <stdio.h>
#include <chrono>

void printFibonacci(int n)
{
    printf("Printing %d terms of Fibonacci series: ", n);

    if(n == 0) 
    {
        printf("\n");
        return;
    }

    printf("0 ");

    int prev = 0;
    int curr = 1; 

    for(int i=1; i<n; ++i) //i=1 as we've already printed 1 term above
    {
        printf("%d ", curr);

        int next = prev + curr;
        prev = curr;
        curr = next;
    }

    printf("\n");
}

unsigned long long calcFibonacciTermRecursive(int n) //saw this algorithm online and it looked fun, but it's extremely slow!
{
    if(n<2) return unsigned long long(n); //0th and 1st terms are 0 and 1
    
    return calcFibonacciTermRecursive(n-2) + calcFibonacciTermRecursive(n-1); //else return sum of two previous terms
}

void printFibonacciTermRecursive(int n)
{
    if(n>76) printf("Cannot print Fibonacci terms above #76, they're too big. Sorry!\n");
    else printf("Printing Fibonacci term #%d recursively: %I64d\n", n, calcFibonacciTermRecursive(n));
}

unsigned long long calcFibonacciTerm(int n)
{
    if(n<2) return unsigned long long(n); //0th and 1st terms are 0 and 1
    
    unsigned long long prev = 0;
    unsigned long long curr = 1; 

    for(int i=1; i<n; ++i) //iterate until the nth term
    {   
        unsigned long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr; 
}

void printFibonacciTerm(int n)
{
    if(n>76) printf("Cannot print Fibonacci terms above #76, they're too big. Sorry!\n");
    else printf("Printing Fibonacci term #%d: %I64d\n", n, calcFibonacciTerm(n));
}

void compareFibonacciPerf(int n) //measures and compares time taken to calculate nth term by both algorithms
{
    printf("Calculating Fibonacci term #%d\n", n);

    auto start = std::chrono::high_resolution_clock::now();
    unsigned long long result = calcFibonacciTerm(n);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_nonRec = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    printf("Non-recursive: %I64d ", result);    
    printf("(%.8f seconds)\n", elapsed_nonRec.count() * 1e-9);

    start = std::chrono::high_resolution_clock::now();
    result = calcFibonacciTermRecursive(n);
    end = std::chrono::high_resolution_clock::now();
    auto elapsed_Rec = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    printf("Recursive: %I64d ", result);    
    printf("(%.8f seconds)\n", elapsed_Rec.count() * 1e-9);

    double ratio = (double)(elapsed_Rec.count() / elapsed_nonRec.count());
    printf("Non-recursive was %.0fx faster\n", ratio);
    printf("\n");
}