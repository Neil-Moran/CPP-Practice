#include <stdio.h>
#include "LinkedList.h"

void addFromFile(LinkedList &list, char *filename);
void insertFromFile(LinkedList &list, char *filename);
void find(LinkedList &list, int value);

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

        find(listOrdered, 6);   // found
        find(listOrdered, 15);  // found
        find(listOrdered, 21);  // not found

        listOrdered.remove(20); // remove head
        listOrdered.remove(16); // remove node 16
        listOrdered.remove(1);  // remove tail
        listOrdered.remove(50); // not in list, do nothing
        listOrdered.print();    // list with values removed
    }

    return 0;
}

void addFromFile(LinkedList &list, char *filename)
{
    FILE *file;
    fopen_s(&file, filename, "r");
    
    // The first value in the file indicates the number of values
    int numValues;
    fscanf_s(file, "%d", &numValues);
    int v = -99999;

    for(int i=0; i<numValues; ++i)
    {
        fscanf_s(file, "%d", &v);
        list += new Node(v);
    }

    fclose(file);
}

void insertFromFile(LinkedList &list, char *filename)
{
    FILE *file;
    fopen_s(&file, filename, "r");
    
    // The first value in the file indicates the number of values
    int numValues;
    fscanf_s(file, "%d", &numValues);
    int v = -99999;

    for(int i=0; i<numValues; ++i)
    {
        fscanf_s(file, "%d", &v);
        list.insert(new Node(v));
    }

    fclose(file);
}

void find(LinkedList &list, int value)
{
    Node *n = list.find(value);

    if(n == 0)
        printf("Value: %d not found\n", value);

    else printf("Value: %d found\n", n->value);
}