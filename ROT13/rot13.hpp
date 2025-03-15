#pragma once
#include <string>

std::string rot13(std::string w)
{
    std::string result = w;

    for(int i=0; result[i]; ++i)
    {
        if(result[i] > 'a' && result[i] <= 'm'
            || result[i] > 'A' && result[i] < 'M')
        {
            result[i] += 13;
        }
        else if(result[i] > 'm' && result[i] <= 'z'
            || result[i] > 'M' && result[i] < 'Z')
        {
            result[i] -=13;
        }
    }

    return result;
}