#include "PigLatin.h"
#include <stdio.h>

int main()
{
    std::string eng = "nix";
    printf("%s : %s\n", eng.c_str(), EngtoPig(eng).c_str());
    
    return 0;
}