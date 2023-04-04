#include "DoubleLinkedList.h"

int main()
{
    {
        DoubleLinkedList emptyList;
        emptyList.insert("head");
        emptyList.remove("head");
        emptyList.addTail("tail");
        emptyList.remove("tail");
        emptyList.remove("x"); // try to remove value from empty list, should do nothing
        emptyList.print();
        emptyList.printReverse();
    }
    {
        DoubleLinkedList list1("c");
        list1.addHead("b");
        list1.addTail("d");
        list1.insert("a");
        list1.insert("f");
        list1.insert("e");
        list1.remove("a");
        list1.remove("f");
        list1.remove("c");
        list1.remove("c"); // try to remove same value twice, should do nothing
        list1.print();
        list1.printReverse();
    }

    return 0;
}