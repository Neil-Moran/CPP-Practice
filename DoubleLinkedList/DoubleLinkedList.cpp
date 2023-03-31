#include "DoubleLinkedList.h"

Node::Node(char *value)
{
    this->value = value;
    prev = 0;
    next = 0;
}

Node::~Node()
{
    if(next) 
        delete next;

    prev = 0;
    next = 0;
}

DoubleLinkedList::DoubleLinkedList()
{
    head = 0;
    tail = 0;
}

DoubleLinkedList::DoubleLinkedList(char *value)
{
    head = new Node(value);
    tail = head;
}

DoubleLinkedList::~DoubleLinkedList()
{
    if(head)
        delete head;
}