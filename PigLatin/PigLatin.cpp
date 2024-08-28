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
            if(token[0] == 'Q' || token[0] == 'q')
            {
                result += token.substr(2) + token.substr(0, 2) + "ay ";
            }

            else 
            {
                int i = 1;
                while(token[i] && !isVowel(token[i]) && token[i] != 'Y' && token[i] != 'y')
                {
                    ++i;
                }

                result += token.substr(i) + token.substr(0, i) + "ay ";
            }
        }
    }

    return result;
}