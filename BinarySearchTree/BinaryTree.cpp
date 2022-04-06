#pragma once
#include "BinaryTree.h"

Node::Node(int v)
{
    value = v;
    left = 0;
    right = 0;
};

void BinaryTree::add(Node *n)
{
    if(root == 0) //empty tree
    {
        root = n;
        return;
    }

};