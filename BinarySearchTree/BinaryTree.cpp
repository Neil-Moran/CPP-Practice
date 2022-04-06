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

void Node::printRecursive()
{
    if(left != 0)
        left->printRecursive();
    printf("%d ", value);
    if(right != 0)
        right->printRecursive();
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

void BinaryTree::print()
{
    if(root == 0)
        printf("EMPTY TREE");
    else root->printRecursive();
    printf("\n");
};