#pragma once

class Node
{
    public:
    char *value;
    Node *prev, *next;
    
    Node(char *value);
    ~Node();
};

class DoubleLinkedList
{
    Node *head, *tail;

    public:
    DoubleLinkedList();
    DoubleLinkedList(char *value);
    ~DoubleLinkedList();

    void addHead(char *value);
    void addTail(char *value);
    void insert(char *value);
    void remove(char *value);
    void print();
    void printReverse();
};