#pragma once

#include "PigLatin.h"
#include <sstream>
#include <string>

// pre-condition: v is alphabetic ASCII, upper or lower case
bool isVowel(char c) 
{
    return (0x208222>>(c&0x1f))&1;
}

std::string EngtoPig(std::string s)
{
    std::string result;
    std::stringstream ss(s);
    std::string token;

    while(getline(ss, token, ' '))
    {
        if(isVowel(token[0]))
        {
            result += token + "way ";
        }

        else
        {
            result += token.substr(1) + token[0] + "ay ";
        }
    }

    return result;
}

