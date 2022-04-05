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
    Node *head, *tail;

    LinkedList()
    {
        head = 0;
        tail = 0;
    }

    ~LinkedList()
    {
        if(head != 0)
            head->~Node();
        printf("Destroying List\n");
    }
    
    void add(Node *n) //add a node to the end of the list, no ordering
    {
        if(head == 0) //empty list
        {
            head = n;
            tail = n;
            return;
        }

        tail->next = n;
        tail = n;
        return;
    }

    void insert(Node *n) //insert a node into the list, numerical order
    {
        if(head == 0) //empty list
        {
            head = n;
            tail = n;
            return;
        }

        if(n->value <= head->value) //new head
        {
            n->next = head;
            head = n;
            return;
        }

        if(n->value >= tail->value) //new tail
        {
            tail->next = n;
            tail = n;
            return;
        }

        Node *prev = head;
        Node *curr = head->next;
        while(n->value > curr->value)
        {
            prev = curr;
            curr = curr->next;
        }

        prev->next = n;
        n->next = curr;

        return;
    }

    void reverse()
    {
        Node *prev = 0;
        Node *curr = head;
        Node *next = 0;

        bool complete = false;
        
        while(!complete)
        {            
            next = curr->next; //store next node before we overwrite it
            curr->next = prev; //reverse

            if (curr == tail)
                complete = true;

            else //move to next node
            {
                prev = curr;
                curr = next;
            }
        }

        //swap head and tail
        tail = head;
        head = curr;                

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