#include <stdio.h>
#include <string>
#include "rot13.hpp"

int main()
{
    std::string s = "Test";

    printf("%s\n", rot13(s).c_str());
    printf("%s\n", rot13(rot13(s)).c_str());
    
    return 0;
}