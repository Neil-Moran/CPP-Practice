#include <stdio.h>
#include "BinaryTree.h"

void addFromFile(BinaryTree &tree, char *filename);
void printDepth(BinaryTree &tree);

int main()
{
    BinaryTree tree;
    tree.print();       //EMPTY TREE
    tree.find(14);      //empty tree, not found
    printDepth(tree);
    printf("//////////\n");

    addFromFile(tree, "scrambledNumbers.txt");
    tree.print();       //1-20
    tree.printAsTree();
    printDepth(tree);

    tree.find(14);  //found
    tree.find(4);   //found, root
    tree.find(21);  //not found
    printf("//////////\n");

    tree.remove(4);     //remove root
    tree.remove(15);    //remove middle node
    tree.remove(21);    //not in tree, do nothing
    tree.print();
    tree.printAsTree();
    printf("//////////\n");

    tree.balance();
    tree.printAsTree();
    printDepth(tree);

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

    fclose(file);
}

void printDepth(BinaryTree &tree)
{
    printf("Tree Depth: ");

    int depth = tree.calcDepth();

    if (depth == 0)
        printf("Empty Tree\n");

    else printf("%d\n", depth); 
}