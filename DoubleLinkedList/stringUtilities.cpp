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