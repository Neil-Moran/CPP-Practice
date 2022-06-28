#pragma once

#include <string>

std::string getCardValue(int card)
{
    std::string currentCard;
    
    int value = card%13;

    switch(value)
    {
    case 1:
        currentCard.append("A");
        break;

    case 11:
        currentCard.append("J");
        break;

    case 12:
        currentCard.append("Q");
        break;

    case 0:
        currentCard.append("K");
        break;
    
    default:
        currentCard.append(std::to_string(value));
        break;
    }

    int suit = (card-1)/13;

    switch (suit) // suits are ordered by their ranking for a royal flush
    {
    case 0:
        currentCard.append("C");
        break;

    case 1:
        currentCard.append("D");
        break;

    case 2:
        currentCard.append("H");
        break;

    case 3:
        currentCard.append("S");
        break;
    
    default:
        break;
    }

    return currentCard;
}

int partition(int array[], int low, int high)
{
    int pivot = array[high]%13; //select the right-most element as a pivot (arbitrary)
    if(pivot < 2) pivot += 13; //ensure Ace(1) and King(13) are high
    int pi = low; // will be the partition index, the index where the pivot belongs

    //find the correct index for the pivot
    for(int i=low; i<high; ++i)
    {
        int curr = array[i]%13;
        if(curr < 2) curr += 13; //ensure Ace(1) and King(13) are high
        if(curr<=pivot)
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