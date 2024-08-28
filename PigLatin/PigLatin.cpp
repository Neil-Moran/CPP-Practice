#pragma once

#include "PigLatin.h"

// pre-condition: v is alphabetic ASCII, upper or lower case
bool isVowel(char c) 
{
    return (0x208222>>(c&0x1f))&1;
}

std::string EngtoPig(std::string s)
{
    std::string result;

    if(isVowel(s[0]))
    {
        result = s + "way";
    }

    else
    {
        result = s.substr(1) + s[0] + "ay";
    }

    return result;
}

