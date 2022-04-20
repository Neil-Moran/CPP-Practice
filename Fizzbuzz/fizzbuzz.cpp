#include <stdio.h>

int fizz = 3;
int buzz = 5;

void fizzbuzz(int n) //print the first n terms of fizzbuzz
{
    for(int i=1; i<=n; ++i)
    {
        if(i%fizz == 0)
            printf("Fizz");
        if(i%buzz == 0)
            printf("Buzz");
        else if(i%fizz != 0)
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
        if(i%fizz == 0)
            fprintf(file, "Fizz");
        if(i%buzz == 0)
            fprintf(file, "Buzz");
        else if(i%fizz != 0)
            fprintf(file, "%d", i);
        fprintf(file, " ");
    }
}

void fizzbuzzNoModulo(int n) //print the first n terms of fizzbuzz without the modulo operator
{
    int fizzCount = fizz;
    int buzzCount = buzz;

    for(int i=1; i<=n; ++i)
    {
        --fizzCount;
        --buzzCount;
        
        if(fizzCount == 0)
            printf("Fizz"); //we can't reset the fizz counter yet, we do it below
        if(buzzCount == 0)
        {
            printf("Buzz");
            buzzCount = buzz;
        }
        else if(fizzCount != 0)
            printf("%d", i);
        else fizzCount = fizz; //now reset fizz counter
        printf(" ");        
    }
    printf("\n\n");
}

void fizzbuzzNoModulo(int n, char *filename) //write the first n terms of fizzbuzz to the specified file, no modulo operator
{
    FILE *file;
    fopen_s(&file, filename, "w+"); 

    int fizzCount = fizz;
    int buzzCount = buzz;

    for(int i=1; i<=n; ++i)
    {
        --fizzCount;
        --buzzCount;
        
        if(fizzCount == 0)
            fprintf(file, "Fizz"); //we can't reset the fizz counter yet, we do it below
        if(buzzCount == 0)
        {
            fprintf(file, "Buzz");
            buzzCount = buzz;
        }
        else if(fizzCount != 0)
            fprintf(file, "%d", i);
        else fizzCount = fizz; //now reset fizz counter
        fprintf(file, " ");        
    }
}