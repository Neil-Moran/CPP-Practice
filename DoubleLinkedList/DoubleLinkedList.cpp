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
    if(head)
    {
        head->prev = n;
        n->next = head;
    }
    else tail = n; // if list was empty the new head is also the new tail

    head = n;
}

void DoubleLinkedList::addTail(char *value)
{
    if(!head) // empty list
    {
        addHead(value);
        return;
    }

    Node *n = new Node(value);
    if(tail) // we checked there is a head above so this should always be true, but just in case
    {   
        tail->next = n;
        n->prev = tail;
    }
    tail = n;
}

void DoubleLinkedList::insert(char *value)
{
    if(!head || areStringsAlphabetized(value, head->value)) // new head
    {
        addHead(value);
        return;
    }

    if(areStringsAlphabetized(tail->value, value)) // new tail
    {
        addTail(value);
        return;
    }

    // find correct position in list
    Node *curr = head;

    // proceed to next node unless it comes after value alphabetically
    while(areStringsAlphabetized(curr->next->value, value)) 
    {
        curr = curr->next;
    }

    // insert value between curr and curr->next
    Node *n = new Node(value);
    n->next = curr->next;
    curr->next->prev = n;
    n->prev = curr;
    curr->next = n;
}

void DoubleLinkedList::remove(char *value)
{
    if(!head) return; // empty list

    if(areStringsIdentical(value, head->value)) // remove head
    {
        Node *curr = head;
        if(curr->next)
        {
            head = curr->next;
            head->prev = 0;
            curr->next = 0;
        }
        else head = 0; // list only had one node, now empty

        delete curr;
        return;
    }

    if(areStringsIdentical(value, tail->value)) // remove tail
    {
        Node *curr = tail;
        if(curr->prev) // if list only had one node then head == tail and we shouldn't have gotten here, but just in case
        {
            tail = curr->prev;
            tail->next = 0;
            curr->prev = 0;
        }
        delete curr;
        return;
    }

    // search for value in list
    Node *curr = head->next;

    while(curr != tail) // search for value until we reach the tail 
    {
        if(areStringsIdentical(value, curr->value)) // value found, remove it
        {
            Node *prev = curr->prev;
            Node *next = curr->next;
            curr->prev = 0;
            curr->next = 0;
            prev->next = next;
            next->prev = prev;
            delete curr;
            return;
        }

        curr = curr->next;
    }    
}

void DoubleLinkedList::print()
{
    if(!head) 
    {
        printf("Empty List\n");
        return;
    }

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
    if(!head) 
    {
        printf("Empty List\n");
        return;
    }

    Node *curr = tail;

    while(curr->prev)
    {
        printf("%s <-> ", curr->value);
        curr = curr->prev;
    }
    printf("%s\n", curr->value);
}
