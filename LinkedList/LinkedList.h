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
            delete next;
        printf("Destroying Node: %d\n", value);
    }

    void print()
    {
        printf("%d -> ", value);

        if(next == 0)
            printf("END\n");
        
        else next->print();        
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
            delete head;
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
    }

    Node* find(int value)
    {
        if(head == 0) //empty list
            return NULL;

        for(Node *curr = head; ; curr = curr->next)
        {
            if(curr->value == value)
                return curr;

            if(curr == tail)
                return NULL;
        }
    }

    void remove(int value)
    {
        if(head == 0) //empty list
            return;

        Node *curr = head;

        if(curr->value == value) //remove head
        {
            head = curr->next;
            curr->next = 0;
            delete curr;
            return;
        }

        Node *prev = curr;
        curr = curr-> next;

        while(curr != tail)
        {
            if(curr->value == value)
            {
                prev->next = curr->next;
                curr->next = 0;
                delete curr;
                return;
            }

            prev = curr;
            curr = curr-> next;
        }

        if(curr->value == value) //remove tail (curr = tail)
        {
            tail = prev;
            prev->next = 0;                
            curr->next = 0;
            delete curr;
        }
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
    }
};