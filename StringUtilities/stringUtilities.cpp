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

bool isAnagram(char *s1, char *s2)
{
    // algorithm to calculate isAnagram without sorting/modifying either string
    // we store the first 26 primes > 1, each maps to a letter, e.g. A = 2, E = 11
    // we iterate through the strings and calculate the product of their primes
    // at the end the products should match for anagrams, even if the int overflows!
    // NB: any chars other than a-z, A-Z are ignored
    int primes[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

    int product_s1 = 1;
    int i=0;

    while(s1[i])
    {
        if('a' <= s1[i] && s1[i] <= 'z')
        {
            product_s1 *= primes[s1[i] - 'a'];
        }
        else if('A' <= s1[i] && s1[i] <= 'Z')
        {
            product_s1 *= primes[s1[i] - 'A'];
        }
        ++i;
    }

    int product_s2 = 1;
    i=0;

    while(s2[i])
    {
        if('a' <= s2[i] && s2[i] <= 'z')
        {
            product_s2 *= primes[s2[i] - 'a'];
        }
        else if('A' <= s2[i] && s2[i] <= 'Z')
        {
            product_s2 *= primes[s2[i] - 'A'];
        }
        ++i;
    }

    if(product_s1 == product_s2) return true;
    else return false;
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