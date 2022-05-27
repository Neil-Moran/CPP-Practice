#include "sorting.h"
#include <stdio.h>

void print(int array[], int size) 
{
    for(int i=0; i<size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void bubbleSort(int array[], int size)
{       
    printf("Bubble Sort: ");
    bool sorted = false;

    while(!sorted)
    {
        sorted = true;
        int temp = -999;

        for(int i=0; i<size-1; ++i)
        {
            if(array[i] > array[i+1])
            {
                sorted = false;
                temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                //print(array, size); //print each swap, for testing
            }
        }
    }

    print(array, size);
}