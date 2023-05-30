#pragma once

#include <stdio.h>
#include <thread>

void printSymbol(char symbol)
{
    for(int i=0; i<100; ++i)
    {
        printf("%c", symbol);
    }
}

void printPlusMinus()
{
    std::thread worker1(printSymbol, '+');
    std::thread worker2(printSymbol, '-');

    worker1.join();
    worker2.join();
    
    printf("\n");
}