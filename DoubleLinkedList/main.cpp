#include "DoubleLinkedList.h"

int main()
{
    DoubleLinkedList list1("c");
    list1.addHead("b");
    list1.addTail("d");
    list1.insert("a");
    list1.insert("f");
    list1.insert("e");
    list1.remove("a");
    list1.remove("f");
    list1.print();
    list1.printReverse();
    
    return 0;
}