#include "BinaryTree.h"
#include <stdio.h>

Node::Node(int v)
{
    value = v;
    left = 0;
    right = 0;
};

int Node::getValue()
{
    return value;
};

void Node::add(Node *n)
{
    if(n->value < value)
    {
        if(left == 0)
            left = n;
        else left->add(n);
    }
    else
    {
        if(right == 0)
            right = n;
        else right->add(n);
    }
};

int Node::findRecursive(int target, int depth = 0)
{
    if(target == value) //found!
        return depth;
        
    ++depth;

    if(target < value && left != 0)
        return left->findRecursive(target, depth);
    if(right != 0) //we now know target > value
        return right->findRecursive(target, depth);
    return -1; //not found
};

int Node::calcDepthRecursive(int currentDepth = 0)
{   
    if(left == 0 && right == 0)
        return currentDepth;
    
    ++currentDepth;
    int leftDepth = 0;
    int rightDepth = 0;

    if(left != 0)
        leftDepth = left->calcDepthRecursive(currentDepth);
    if(right != 0)
        rightDepth = right->calcDepthRecursive(currentDepth);
    
    if(leftDepth > rightDepth)
        return leftDepth;
    else return rightDepth;
};

void Node::printRecursive()
{
    if(left != 0)
        left->printRecursive();
    printf("%d ", value);
    if(right != 0)
        right->printRecursive();
};

void Node::printTree(int depth = 0)
{
    for(int i=0; i< depth-1; ++i)
    {
        printf("   ");
    }
    if(depth != 0)
        printf("\\->");

    ++depth;

    printf("%d\n", value);
    if(right != 0)
        right->printTree(depth);
    if(left != 0)
        left->printTree(depth);
};

void BinaryTree::add(Node *n)
{
    if(root == 0) //empty tree
    {
        root = n;
        return;
    }

    root->add(n);
};

void BinaryTree::find(int target)
{
    if(root == 0)
    {
        printf("Empty tree, value: %d not found\n", target);
        return;
    }

    int result = root->findRecursive(target);

    if(result == -1)
        printf("Value: %d not found\n", target);
    else printf("Value: %d found. Depth: %d\n", target, result);
};

int BinaryTree::calcDepth()
{   
    if(root == 0)
        return -1;
    return root->calcDepthRecursive();
};

void BinaryTree::print()
{
    if(root == 0)
        printf("EMPTY TREE");
    else root->printRecursive();
    printf("\n");
};

void BinaryTree::printAsTree()
{
    if(root == 0)
        printf("EMPTY TREE\n");
    else root->printTree();
};