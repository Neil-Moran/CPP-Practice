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
            int i = 1;
            while(token[i] && !isVowel(token[i]))
            {
                ++i;
            }

            result += token.substr(i) + token.substr(0, i) + "ay ";
        }
    }

    return result;
}