#include "sorting.h"
#include <stdio.h>

int main()
{
    {
    int array[] = {16, 6, 8, 11, 10, 20, 25, 23, 26, 30, 17, 4, 28, 9, 18, 1, 27, 7, 19, 2, 15, 21, 12, 22, 24, 29, 3, 14, 5, 13};

    printf("Unsorted Array: ");
    print(array, 30);
    bubbleSort(array, 30);
    }

    {
    int array[] = {16, 6, 8, 11, 10, 20, 25, 23, 26, 30, 17, 4, 28, 9, 18, 1, 27, 7, 19, 2, 15, 21, 12, 22, 24, 29, 3, 14, 5, 13};
    selectionSort(array, 30);
    }

    {
    int array[] = {16, 6, 8, 11, 10, 20, 25, 23, 26, 30, 17, 4, 28, 9, 18, 1, 27, 7, 19, 2, 15, 21, 12, 22, 24, 29, 3, 14, 5, 13};
    mergeSort(array, 30);
    }

    {
    int array[] = {16, 6, 8, 11, 10, 20, 25, 23, 26, 30, 17, 4, 28, 9, 18, 1, 27, 7, 19, 2, 15, 21, 12, 22, 24, 29, 3, 14, 5, 13};
    quickSort(array, 30);
    }

    printf("\n");

    profileBubbleSort();
    profileSelectionSort();
    profileMergeSort();
    profileQuickSort();
    
    return 0;
}