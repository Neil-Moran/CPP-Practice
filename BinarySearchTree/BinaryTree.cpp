#pragma once
#include "BinaryTree.h"

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

void BinaryTree::add(Node *n)
{
    if(root == 0) //empty tree
    {
        root = n;
        return;
    }

    root->add(n);

};