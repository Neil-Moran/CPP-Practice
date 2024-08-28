#include "PigLatin.h"
#include <array>
#include <stdio.h>

int main()
{
    std::array<std::string, 7> input{"nix", "apple", "eye", "indigo", "orb", "under", "sentence in pig latin"};

    for(auto& s : input)
    {
        printf("%s\t: %s\n", s.c_str(), EngtoPig(s).c_str());
    }

    return 0;
}