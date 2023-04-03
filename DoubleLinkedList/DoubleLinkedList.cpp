#include "DoubleLinkedList.h"
#include "stringUtilities.h"
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
    printf("Creating List with initial Node %s\n", value);
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

void DoubleLinkedList::addHead(char *value)
{
    Node *n = new Node(value);
    head->prev = n;
    n->next = head;
    head = n;
}

void DoubleLinkedList::addTail(char *value)
{
    Node *n = new Node(value);
    tail->next = n;
    n->prev = tail;
    tail = n;
}

void DoubleLinkedList::insert(char *value)
{
    if(areStringsAlphabetized(value, head->value)) // new head
    {
        addHead(value);
        return;
    }

    if(areStringsAlphabetized(tail->value, value)) // new tail
    {
        addTail(value);
        return;
    }
}


void DoubleLinkedList::print()
{
    Node *curr = head;

    while(curr->next)
    {
        printf("%s <-> ", curr->value);
        curr = curr->next;
    }
    printf("%s\n", curr->value);
}

void DoubleLinkedList::printReverse()
{
    Node *curr = tail;

    while(curr->prev)
    {
        printf("%s <-> ", curr->value);
        curr = curr->prev;
    }
    printf("%s\n", curr->value);
}
