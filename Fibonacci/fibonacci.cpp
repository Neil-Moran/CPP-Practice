#pragma once
#include <stdio.h>

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

    return;
}