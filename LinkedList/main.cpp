#include <stdio.h>
#include "LinkedList.h"

void addFromFile(LinkedList &list, char *filename);

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
        listOrdered.insert(new Node(4));
        listOrdered.insert(new Node(1));
        listOrdered.insert(new Node(3));
        listOrdered.insert(new Node(5));
        listOrdered.insert(new Node(2));
        listOrdered.print(); // list of 1-5 ordered
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

    return;
}