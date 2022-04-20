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
    printf("\n");
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