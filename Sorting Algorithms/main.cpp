#include "sorting.h"

int main()
{
    int array[] = {16, 6, 8, 11, 10, 20, 25, 23, 26, 30, 17, 4, 28, 9, 18, 1, 27, 7, 19, 2, 15, 21, 12, 22, 24, 29, 3, 14, 5, 13};

    print(array, 30);
    bubbleSort(array, 30);

    return 0;
}