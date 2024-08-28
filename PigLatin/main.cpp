#include "PigLatin.h"
#include <stdio.h>
#include <vector>

int main()
{
    std::vector<std::string> input 
    {
        "nix", "apple", "eye", "indigo", "orb", "under", "yacht", "stick", "rhythm", "sentence in pig latin"
    };

    for(auto& s : input)
    {
        printf("%s\t: %s\n", s.c_str(), EngtoPig(s).c_str());
    }

    return 0;
}