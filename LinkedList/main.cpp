#include <stdio.h>
#include "LinkedList.h"

void addFromFile(LinkedList &list, char *filename);
void insertFromFile(LinkedList &list, char *filename);

int main() 
{
    {
        LinkedList listPrimes;
        listPrimes.print(); // EMPTY LIST

        addFromFile(listPrimes, "primes.txt");
        listPrimes.print(); // list of first ten prime numbers
    }

    {
        LinkedList listOrdered;
        insertFromFile(listOrdered, "scrambledNumbers.txt");
        listOrdered.print(); // list of 1-20 ordered

        listOrdered.reverse();
        listOrdered.print(); // reversed list of 20-1
    }

    return 0;
}

void addFromFile(LinkedList &list, char *filename)
{
    FILE *file;
    file = fopen(filename, "r");
    
    // The first value in the file indicates the number of values
    int numValues;
    fscanf_s(file, "%d", &numValues);
    int v = -99999;

    for(int i=0; i<numValues; ++i)
    {
        fscanf_s(file, "%d", &v);
        list += new Node(v);
    }
}

void insertFromFile(LinkedList &list, char *filename)
{
    FILE *file;
    file = fopen(filename, "r");
    
    // The first value in the file indicates the number of values
    int numValues;
    fscanf_s(file, "%d", &numValues);
    int v = -99999;

    for(int i=0; i<numValues; ++i)
    {
        fscanf_s(file, "%d", &v);
        list.insert(new Node(v));
    }
}