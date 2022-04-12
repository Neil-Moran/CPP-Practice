#include "BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>

Node::Node(int v)
{
    value = v;
    left = 0;
    right = 0;
};

Node::~Node()
{
    if(left != 0)
        delete left;
    if(right != 0)
        delete right;
    printf("Destroying Node: %d\n", value);
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

int Node::findRecursive(int target, int depth = 1)
{
    if(target == value) //found!
        return depth;
        
    ++depth;

    if(target < value && left != 0)
        return left->findRecursive(target, depth);
    if(right != 0) //we now know target > value
        return right->findRecursive(target, depth);
    return 0; //not found
};

int Node::calcDepthRecursive(int currentDepth = 1)
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

Node* Node::balanceRecursive(Node *parent)
{
    //returns a pointer to the new root node, or 0 if on a child branch
    printf("%d ", value);
    int depthL, depthR;
    Node *curr = 0;
    Node *root = 0;

    if(parent == 0)
        root = this;

    while(true)
    {
        if(left != 0) 
            depthL = left->calcDepthRecursive(); 
        else depthL = 0;

        if(right != 0) 
            depthR = right->calcDepthRecursive();
        else depthR = 0;

        if(abs(depthL - depthR) <= 1) //balanced
            break;

        if(depthL > depthR) //left branch is too deep
        {
            curr = left;
            left = 0;            
        }
        else //(depthR > depthL) => right branch is too deep
        {
            curr = right;
            right = 0;
        }
        
        if(parent == 0) //assign new root
        {
            root = curr;
        }
        else //connect parent to curr instead of this
        {
            if(parent->left == this)
                parent->left = curr;
            else parent->right = curr;
        }

        curr->add(this);
        Node * newRoot = curr->balanceRecursive(parent);
        if(newRoot != 0)
            root = newRoot;
    }

    //balance children
    if(left != 0) 
        left->balanceRecursive(this);
    if(right != 0) 
        right->balanceRecursive(this);

    return root;
}

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

BinaryTree::~BinaryTree()
{
    delete root;
}

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

    if(result == 0)
        printf("Value: %d not found\n", target);
    else printf("Value: %d found. Depth: %d\n", target, result);
};

void BinaryTree::remove(int value)
{
    if(root == 0)
        return;

    if(root->value == value) //remove root
    {
        //make right new root and add left to it (could also do vice versa)
        Node *rootNew = root->right;
        rootNew->add(root->left);

        //disconnect and delete root
        root->left = 0;
        root->right = 0;
        delete root;

        //assign new root
        root = rootNew;
        return;
    }

    Node *curr = root;
    Node *parent = 0;

    while(curr != 0)
    {
        if(value < curr->value)
        {            
            parent = curr;
            curr = curr->left;
        }

        else if(value > curr->value)
        {
            parent = curr;
            curr = curr->right;
        }
        
        else //we now know (curr->value == value) => found
        {
            //disconnect curr from parent
            if(curr == parent->left)
                parent->left = 0;
            if(curr == parent->right)
                parent->right = 0;

            //add both children to parent, order doesn't matter
            parent->add(curr->right);
            parent->add(curr->left);

            //disconnect and delete curr
            curr->right = 0;
            curr->left = 0;
            delete curr;
            curr = 0;
        }
    }
};

int BinaryTree::calcDepth()
{   
    if(root == 0)
        return 0;
    return root->calcDepthRecursive();
};

void BinaryTree::balance()
{   
    printf("BALANCING: ");
    root = root->balanceRecursive(0);
    printf("\n");
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