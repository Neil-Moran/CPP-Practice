#pragma once
#include "sorting.h"
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

void merge(int array[], int l, int mid, int r) //assuming array is sorted from l->mid & mid+1->r, merge those two sub arrays
{
     
    int *arrayTemp = (int*)malloc(sizeof(int)*(r-l+1));

    int i=0;
    int i_l = l;
    int i_r = mid+1;  
    
    while(i<=r-l && i_l <= mid && i_r <= r)
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

    if(i_l <= mid)
    {
        for(int j=i_l; j<=mid; ++j)
        {
            arrayTemp[i] = array[j];
            ++i;
        }
    }

    if(i_r <= r)
    {
        for(int j=i_r; j<=r; ++j)
        {
            arrayTemp[i] = array[j];
            ++i;
        }
    }
    
    for(i=0; i<=r-l; ++i)
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