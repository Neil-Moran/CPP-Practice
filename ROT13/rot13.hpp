#pragma once
#include <string>

using std::string;

string rot13(string w)
{
    string result = w;

    for(int i=0; result[i]; ++i)
    {
        if(result[i] >= 'a' && result[i] <= 'm'
            || result[i] >= 'A' && result[i] <= 'M')
        {
            result[i] += 13;
        }
        else if(result[i] >= 'n' && result[i] <= 'z'
            || result[i] >= 'N' && result[i] <= 'Z')
        {
            result[i] -=13;
        }
    }

    return result;
}