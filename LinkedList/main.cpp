#include "LinkedList.h"

int main() 
{
    LinkedList list;
    list += new Node(1);
    list += new Node(5);
    list += new Node(72);

    list.print();

    return 0;
}