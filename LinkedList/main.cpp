#include "LinkedList.h"

int main() 
{
    LinkedList list;
    list.add(new Node(1));
    list.add(new Node(5));
    list.add(new Node(72));

    list.print();

    return 0;
}