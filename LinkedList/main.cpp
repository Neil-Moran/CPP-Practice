#include <stdio.h>
#include "LinkedList.h"

void addFromFile(LinkedList &list, char *filename);

int main() 
{
    LinkedList list;

    addFromFile(list, "input.txt");

    list.print();

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