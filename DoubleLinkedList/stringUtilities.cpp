#pragma once
#include "stringUtilities.h"

bool areStringsAlphabetized(char *s1, char *s2)
{
    for(int i=0; s1[i], s2[i]; ++i)
    {
        if(s1[i] < s2[i]) return true;
        if(s1[i] > s2[i]) return false;

        if(!s1[i+1]) return true;
        if(!s2[i+1]) return false;
    }

    return false;
}