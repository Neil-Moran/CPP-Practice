#pragma once

struct Node 
{
    int value;
    Node *next;

    Node(int n);
    ~Node();

    void print();
};

struct LinkedList
{
    Node *head, *tail;

    LinkedList();
    ~LinkedList();
    
    void add(Node *n);
    void insert(Node *n);
    Node* find(int value);
    void remove(int value);
    void reverse();
    LinkedList& operator+=(Node *n);
    void print();
};