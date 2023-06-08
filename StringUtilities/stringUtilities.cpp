#pragma once
#include "stringUtilities.h"

bool areStringsAlphabetized(char *s1, char *s2)
{
    for(int i=0; ; ++i)
    {
        if(!s1[i]) return true;
        if(!s2[i]) return false;

        if(s1[i] < s2[i]) return true;
        if(s1[i] > s2[i]) return false;      
    }
}

bool areStringsIdentical(char *s1, char *s2)
{
    int i=0;

    while(s1[i] && s2[i])
    {
        if(s1[i] != s2[i])
            return false;

        ++i;
    }

    if(!s1[i] && !s2[i])
        return true;
    else return false;
}

int getStringSize(char *s)
{
    if(!s[0]) return 0; // empty string

    int size = 1;
    while(s[size]) ++size;

    return size;
}

int convertStringToInt(char *s)
{
    if(!s[0]) return 0; // empty string

    int size = getStringSize(s);

    if(size > sizeof("+2147483647")-1) return 0; // ERROR: string is longer than "+2147483647" (minus null terminator), will overflow 

    int result = 0;
    int multiplier = (s[0] == '-') ? -1 : 1; // if first char is '-' we want to subtract the running total, else add
    int firstChar = ((s[0] == '+') || (s[0] == '-')) ? 1 : 0; // we're about to read through all the chars; if first char is +/-, ignore it

    for(int i=size-1; i>=firstChar; --i, multiplier *= 10) // read through all numeric chars and add them to result
    {
        if((multiplier%10 != 0 && i!=size-1)  // ERROR: overflow, string exceeded max int
            ||(s[i] < '0' || s[i] > '9')) return 0; // ERROR: char is not a digit from 0-9

        else result += (s[i]-48) * multiplier;
    }

    if((result < 0) ^ (s[0] == '-')) return 0; // ERROR: over/underflow, string exceeded int limits

    return result;
}

int partition(char s[], int low, int high)
{
    char pivot = s[high]; //select the right-most element as a pivot (arbitrary)
    int pi = low; // will be the partition index, the index where the pivot belongs

    //find the correct index for the pivot
    for(int i=low; i<high; ++i)
    {
        if(s[i]<=pivot)
        {
            if(i!=pi)
            {
                char temp = s[pi];
                s[pi] = s[i];
                s[i] = temp;
            }
            ++pi;
        }
    }

    if(pi != high) //move the pivot to the correct index, if not already there
    {
        char temp = s[pi];
        char temp2 = s[high];
        s[pi] = temp2;
        s[high] = temp;
    }
    return pi;
}

void quickSort(char s[], int low, int high)
{
    if(low < high)
    {
        int pivot = partition(s, low, high);
        
        quickSort(s, low, pivot-1);
        quickSort(s, pivot+1, high);
    }
}

void sortString(char s[])
{
    if(!s[0]) return; // empty string

    int size = getStringSize(s);

    quickSort(s, 0, size-1);
}