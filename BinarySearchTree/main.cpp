#include <stdio.h>
#include "BinaryTree.h"

void addFromFile(BinaryTree &tree, char *filename);

int main()
{
    BinaryTree tree;
    tree.print(); //EMPTY TREE

    addFromFile(tree, "scrambledNumbers.txt");
    tree.print(); //1-20

    return 0;
}

void addFromFile(BinaryTree &tree, char *filename)
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
        tree.add(new Node(v));
    }
}