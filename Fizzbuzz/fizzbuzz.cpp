#include <assert.h>
#include <chrono>
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
    using namespace std::chrono;
    const int n = 1000000;
    high_resolution_clock::time_point start = high_resolution_clock::now();  

    fizzbuzz(n, "profileFizzbuzz.txt");

    high_resolution_clock::time_point end = high_resolution_clock::now();
    nanoseconds elapsed = duration_cast<nanoseconds>(end - start);

    printf("Wrote %d terms of Fizzbuzz using modulo operator in %.8f seconds\n", n, elapsed.count() * 1e-9);
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
            printf("Fizz"); //we can't reset the fizz counter yet, we do it below
        if(buzzCount == 0)
        {
            printf("Buzz");
            buzzCount = BUZZ;
        }
        else if(fizzCount != 0)
            printf("%d", i);
        else fizzCount = FIZZ; //now reset fizz counter
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
            fprintf(file, "Fizz"); //we can't reset the fizz counter yet, we do it below
        if(buzzCount == 0)
        {
            fprintf(file, "Buzz");
            buzzCount = BUZZ;
        }
        else if(fizzCount != 0)
            fprintf(file, "%d", i);
        else fizzCount = FIZZ; //now reset fizz counter
        fprintf(file, " ");        
    }
    fclose(file);
}

void profileFizzbuzzNoModulo() //write a large number terms of fizzbuzz to a file without using modulo operator and time it
{
    using namespace std::chrono;
    const int n = 1000000;
    high_resolution_clock::time_point start = high_resolution_clock::now();

    fizzbuzzNoModulo(n, "profileFizzbuzz.txt");

    high_resolution_clock::time_point end = high_resolution_clock::now();
    nanoseconds elapsed = duration_cast<nanoseconds>(end - start);

    printf("Wrote %d terms of Fizzbuzz without using modulo operator in %.8f seconds\n", n, elapsed.count() * 1e-9);
    bool fileRemoved = remove("profileFizzbuzz.txt");
    assert(fileRemoved == 0);
}