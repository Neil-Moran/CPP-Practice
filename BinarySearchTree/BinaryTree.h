#pragma once

struct Node
{
    friend struct BinaryTree;

    Node(int v);
    ~Node();

    private:
    int value;  
    Node *left, *right;
    
    int getValue();
    void add(Node *n);
    int findRecursive(int target, int depth);
    int calcDepthRecursive(int currentDepth);
    Node* balanceRecursive(Node *parent);
    void printRecursive();
    void printTree(int depth);
};

struct BinaryTree
{
    Node *root = 0;

    ~BinaryTree();

    void add(Node *n);
    void find(int target);
    void remove(int value);
    int calcDepth() const;
    void balance();
    void print();
    void printAsTree();
};