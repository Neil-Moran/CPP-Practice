#include "LinkedList.h"

int main() 
{
    LinkedList list;

    Node node1;
    node1.value = 1;
    node1.next = 0;
    list.head = &node1;

    Node node2;
    node2.value = 5;
    node2.next = 0;
    node1.next = &node2;

    list.print();

    return 0;
}