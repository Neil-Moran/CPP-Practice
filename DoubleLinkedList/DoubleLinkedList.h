#pragma once

class Node
{
    char *value;
    Node *prev, *next;

    public:
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
};