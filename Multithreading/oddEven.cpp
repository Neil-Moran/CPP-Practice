#pragma once

#include <condition_variable>
#include <mutex>
#include <stdio.h>
#include <thread>

std::condition_variable cv;
std::mutex m;
bool isOdd_global = true;

void printOdd()
{
    std::unique_lock<std::mutex> ul(m);

    for(int i=1; i<100; i+=2)
    {        
        cv.wait(ul, [] { return isOdd_global;}); // wait for isOdd to be true
        printf("%i ", i);
        isOdd_global = false;
        cv.notify_one();
    }
}

void printEven()
{
    std::unique_lock<std::mutex> ul(m);
        
    for(int i=2; i<100; i+=2)
    {
        cv.wait(ul, [] { return !isOdd_global;}); // wait for isOdd to be false
        printf("%i ", i);
        isOdd_global = true;
        cv.notify_one();
    }
}

void printOddEven()
{
    std::thread worker1(printOdd);
    std::thread worker2(printEven);

    worker1.join();
    worker2.join();
    
    printf("\n");
}