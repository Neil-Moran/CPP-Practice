#pragma once
#include <stdio.h>

struct Node 
{
    int value;
    Node *next;

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

    void print()
    {
        if(head == 0)
            printf("EMPTY LIST\n");
        
        else head->print();
        return;
    }
};