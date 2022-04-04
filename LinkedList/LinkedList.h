#pragma once
#include <stdio.h>

struct Node 
{
    int value;
    Node *next;

    Node(int n)
    {
        value = n;
        next = 0;
    }

    ~Node()
    {
        if(next != 0)
            next->~Node();
        printf("Destroying Node: %d\n", value);
    }

    void print()
    {
        printf("%d -> ", value);

        if(next == 0)
            printf("END\n");
        
        else next->print();
        
        return;
    }
};

struct LinkedList 
{
    Node *head;

    LinkedList()
    {
        head = 0;
    }

    ~LinkedList()
    {
        if(head != 0)
            head->~Node();
        printf("Destroying List\n");
    }
    
    void add(Node *n)
    {
        if(head == 0)
        {
            head = n;
            return;
        }

        Node *curr = head;

        while(curr->next != 0)
        {
            curr = curr->next;
        }

        curr->next = n;
        return;
    }

    LinkedList& operator+=(Node *n)
    {
        add(n);
        return *this;
    }

    void print()
    {
        if(head == 0)
            printf("EMPTY LIST\n");
        
        else head->print();
        return;
    }
};