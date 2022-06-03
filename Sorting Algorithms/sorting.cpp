#pragma once
#include "bigArray.h"
#include "sorting.h"
#include "timing.h"
#include <stdio.h>
#include <stdlib.h>

void print(int array[], int size) 
{
    for(int i=0; i<size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

inline void bubbleSortPrivate(int array[], int size)
{
    bool sorted = false;     

    for(int sortedIndex = size-1; !sorted; --sortedIndex) //everything after sorted index in array is sorted
    {
        sorted = true;
        int temp = -999;

        for(int i=0; i<sortedIndex; ++i)
        {
            if(array[i] > array[i+1])
            {
                sorted = false;
                temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;                
            }            
        }        
        //print(array, size); //print each iteration, for testing
    }
}

void bubbleSort(int array[], int size)
{
    if(size <= 0) return;

    printf("Bubble Sort: ");

    bubbleSortPrivate(array, size);

    print(array, size);
}

void profileBubbleSort()
{
    BIG_ARRAY 
    printf("Profiling Bubble Sort\n");
    TIME_START
    bubbleSortPrivate(array, 10000);
    TIME_END
}

inline void selectionSortPrivate(int array[], int size)
{
    for(int sortedIndex = 0; sortedIndex < size; ++sortedIndex) //everything before sorted index in array is sorted
    {
        //find the min value in the unsorted sub array...
        int minValueIndex = sortedIndex;
        for(int i=sortedIndex; i<size; ++i)
        {
            if(array[i] < array[minValueIndex])
                minValueIndex = i;            
        }

        //...and move it to the end of the sorted sub array
        int temp = array[minValueIndex];
        array[minValueIndex] = array[sortedIndex];
        array[sortedIndex] = temp;
    }
}

void selectionSort(int array[], int size)
{
    if(size <= 0) return;

    printf("Selection Sort: ");
    
    selectionSortPrivate(array, size);

    print(array, size);
}

void profileSelectionSort()
{
    BIG_ARRAY
    printf("Profiling Selection Sort\n");
    TIME_START
    selectionSortPrivate(array, 10000);
    TIME_END
}

void merge(int array[], int l, int mid, int r) //assuming array is sorted from l->mid & mid+1->r, merge those two sub arrays
{     
    int *arrayTemp = (int*)malloc(sizeof(int)*(r-l+1));

    int i=0;
    int i_l = l;
    int i_r = mid+1;  
    
    while(i_l <= mid && i_r <= r)
    {
        if(array[i_l] < array[i_r])
        {
            arrayTemp[i] = array[i_l];
            ++i_l;
        }
        else 
        {
            arrayTemp[i] = array[i_r];
            ++i_r;
        }

        ++i;
    }

    if(i_l <= mid) //finish reading all the values from the left sub array into the temp array
    {
        for(int j=i_l; j<=mid; ++j)
        {
            arrayTemp[i] = array[j];
            ++i;
        }
    }
    
    // if we haven't finished reading all the values from the right sub array into
    // the temp array then we don't need to bother - they're already in the correct
    // position in the result array! Set the temp_end variable to denote at what index 
    // we should stop reading results from the temp array
    int temp_end = (i_r <= r) ? i_r-l-1 : r-l;
    
    for(i=0; i<=temp_end; ++i)
        array[l+i] = arrayTemp[i];

    free(arrayTemp);
}

void mergeSort(int array[], int l, int r)
{
    if(l == r) return;    

    if(l == r-1)
    {
        if(array[l] > array[r])
        {
            int temp = array[l];
            array[l] = array[r];
            array[r] = temp;
        }
        return;
    }

    int mid = l + ( (r-l)/2 );

    mergeSort(array, l, mid);
    mergeSort(array, mid+1, r);

    merge(array, l, mid, r);
}

void mergeSort(int array[], int size)
{    
    if(size <= 0) return;

    printf("Merge Sort: ");
    
    mergeSort(array, 0, size-1);

    print(array, size);
}

void profileMergeSort()
{
    BIG_ARRAY
    printf("Profiling Merge Sort\n");
    TIME_START
    mergeSort(array, 0, 10000-1);
    TIME_END
}

int partition(int array[], int low, int high)
{
    int pivot = array[high]; //select the right-most element as a pivot (arbitrary)
    int pi = low; // will be the partition index, the index where the pivot belongs

    //find the correct index for the pivot
    for(int i=low; i<high; ++i)
    {
        if(array[i]<=pivot)
        {
            if(i!=pi)
            {
                int temp = array[pi];
                array[pi] = array[i];
                array[i] = temp;
            }
            ++pi;
        }
    }

    if(pi != high) //move the pivot to the correct index, if not already there
    {
        int temp = array[pi];
        array[pi] = array[high];
        array[high] = temp;
    }
    return pi;
}

void quickSort(int array[], int low, int high)
{
    if(low < high)
    {
        int pivot = partition(array, low, high);
        
        quickSort(array, low, pivot-1);
        quickSort(array, pivot+1, high);
    }
}

void quickSort(int array[], int size)
{
    if(size <= 0) return;

    printf("Quick Sort: ");
    
    quickSort(array, 0, size-1);

    print(array, size);
}

void profileQuickSort()
{
    BIG_ARRAY
    printf("Profiling Quick Sort\n");
    TIME_START
    quickSort(array, 0, 10000-1);
    TIME_END
}