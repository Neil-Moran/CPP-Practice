#include "fizzbuzz.h"
#include "timing.h"
#include <assert.h>
#include <stdio.h>

const int FIZZ = 3;
const int BUZZ = 5;

void fizzbuzz(int n) //print the first n terms of fizzbuzz
{
    for(int i=1; i<=n; ++i)
    {
        if(i%FIZZ == 0)
            printf("Fizz");
        if(i%BUZZ == 0)
            printf("Buzz");
        else if(i%FIZZ != 0)
            printf("%d", i);
        printf(" ");
    }
    printf("\n\n");
}

void fizzbuzz(int n, char *filename) //write the first n terms of fizzbuzz to the specified file
{
    FILE *file;
    fopen_s(&file, filename, "w+");

    for(int i=1; i<=n; ++i)
    {
        if(i%FIZZ == 0)
            fprintf(file, "Fizz");
        if(i%BUZZ == 0)
            fprintf(file, "Buzz");
        else if(i%FIZZ != 0)
            fprintf(file, "%d", i);
        fprintf(file, " ");
    }
    fclose(file);
}

void profileFizzbuzz() //write a large number of terms of fizzbuzz to a file using modulo operator and time it
{
    const int n = 1000000;
    printf("Writing %d terms of Fizzbuzz using modulo operator\n", n);

    {
        Timer timer;
        fizzbuzz(n, "profileFizzbuzz.txt");
    } // destroy timer

    bool fileRemoved = remove("profileFizzbuzz.txt");
    assert(fileRemoved == 0);
}

void fizzbuzzNoModulo(int n) //print the first n terms of fizzbuzz without the modulo operator
{
    int fizzCount = FIZZ;
    int buzzCount = BUZZ;

    for(int i=1; i<=n; ++i)
    {
        --fizzCount;
        --buzzCount;
        
        if(fizzCount == 0)
        {
            if(buzzCount == 0)
            {
                printf("FizzBuzz");
                fizzCount = FIZZ;
                buzzCount = BUZZ;
            }
            else
            {
                printf("Fizz"); 
                fizzCount = FIZZ;
            }
        }
        else if(buzzCount == 0)
        {
            printf("Buzz");
            buzzCount = BUZZ;
        }
        else 
        {
            printf("%d", i);
        }
        printf(" ");        
    }
    printf("\n\n");
}

void fizzbuzzNoModulo(int n, char *filename) //write the first n terms of fizzbuzz to the specified file, no modulo operator
{
    FILE *file;
    fopen_s(&file, filename, "w+"); 

    int fizzCount = FIZZ;
    int buzzCount = BUZZ;

    for(int i=1; i<=n; ++i)
    {
        --fizzCount;
        --buzzCount;

        if(fizzCount == 0)
        {
            if(buzzCount == 0)
            {
                fprintf(file, "FizzBuzz");
                fizzCount = FIZZ;
                buzzCount = BUZZ;
            }
            else
            {
                fprintf(file, "Fizz");
                fizzCount = FIZZ;
            }
        }
        else if(buzzCount == 0)
        {
            fprintf(file, "Buzz");
            buzzCount = BUZZ;
        }
        else 
        {
            fprintf(file, "%d", i);
        }
        fprintf(file, " ");        
    }
    fclose(file);
}

void profileFizzbuzzNoModulo() //write a large number terms of fizzbuzz to a file without using modulo operator and time it
{
    const int n = 1000000;
    printf("Writing %d terms of Fizzbuzz without using modulo operator\n", n);

    {
        Timer timer;
        fizzbuzzNoModulo(n, "profileFizzbuzz.txt");    
    } // destroy timer

    bool fileRemoved = remove("profileFizzbuzz.txt");
    assert(fileRemoved == 0);
}