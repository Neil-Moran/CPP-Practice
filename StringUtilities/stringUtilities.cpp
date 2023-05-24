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

int convertStringToInt(char * s)
{
    if(!s[0]) return 0; // empty string

    int size = 1;
    while(s[size]) ++size;

    if(size > 11) return 0; // ERROR: string is longer than "+2147483648", will overflow 

    int result = 0;
    int multiplier = (s[0] == '-') ? -1 : 1; // if first char is '-' we want to subtract the running total, else add
    int firstChar = ((s[0] == '+') || (s[0] == '-')) ? 1 : 0; // we're about to read through all the chars; if first char is +/-, ignore it

    for(int i=size-1; i>=firstChar; --i, multiplier *= 10) // read through all numeric chars and add them to result
    {
        if((multiplier%10 != 0 && i!=size-1)  // ERROR: overflow, string exceeded max int
            ||(s[i] < '0' || s[i] > '9')) return 0; // ERROR: char is not a digit from 0-9

        else result += (s[i]-48) * multiplier;
    }

    if(result < 0 && s[0] != '-') return 0; // ERROR: overflow, string exceeded max int
    if(result > 0 && s[0] == '-') return 0; // ERROR: underflow, string exceeded min int

    return result;
}