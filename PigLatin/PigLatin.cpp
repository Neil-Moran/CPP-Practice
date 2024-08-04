#pragma once

#include "PigLatin.h"

std::string EngtoPig(std::string s)
{
    std::string result = s.substr(1) + s[0] + "ay";

    return result;
}