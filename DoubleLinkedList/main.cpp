#include "DoubleLinkedList.h"

int main()
{
    DoubleLinkedList list1("b");
    list1.addHead("a");
    list1.addTail("c");
    list1.print();
    list1.printReverse();
    
    return 0;
}