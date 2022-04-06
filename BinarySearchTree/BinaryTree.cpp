#pragma once
#include "BinaryTree.h"
#include <stdio.h>

Node::Node(int v)
{
    value = v;
    left = 0;
    right = 0;
};

void Node::add(Node *n)
{
    if(n->value < this->value)
    {
        if(this->left == 0)
            this->left = n;
        else this->left->add(n);
    }
    else
    {
        if(this->right == 0)
            this->right = n;
        else this->right->add(n);
    }
};

int Node::findRecursive(int target, int depth)
{
    int result = depth + 1;

    if(target == value) //found!
        return result;
    if(target < value && left != 0)
        return left->findRecursive(target, result);
    if(right != 0) //we now know target > value
        return right->findRecursive(target, result);
    return -1; //not found
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

    printf("%d\n", value);
    if(right != 0)
        right->printTree(depth+1);
    if(left != 0)
        left->printTree(depth+1);
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

    int result = root->findRecursive(target, -1);

    if(result == -1)
        printf("Value: %d not found\n", target);
    else printf("Value: %d found. Depth: %d\n", target, result);
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
        printf("EMPTY TREE");
    else root->printTree();
    printf("\n");
};