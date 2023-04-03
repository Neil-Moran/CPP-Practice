#include "DoubleLinkedList.h"
#include <stdio.h>
#define verbose // print various debug messages

Node::Node(char *value)
{
    #ifdef verbose
    printf("Creating Node %s\n", value);
    #endif

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

    #ifdef verbose
    printf("Deleting Node %s\n", value);
    #endif
}

DoubleLinkedList::DoubleLinkedList()
{
    #ifdef verbose
    printf("Creating List\n");
    #endif

    head = 0;
    tail = 0;    
}

DoubleLinkedList::DoubleLinkedList(char *value)
{
    #ifdef verbose
    printf("Creating List with Head %s\n", value);
    #endif

    head = new Node(value);
    tail = head;    
}

DoubleLinkedList::~DoubleLinkedList()
{
    #ifdef verbose
    printf("Deleting List\n");
    #endif

    if(head)
        delete head;
}