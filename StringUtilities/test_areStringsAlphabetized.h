#pragma once
#include "stringUtilities.h"

bool test_alphabetized1_TwoEmptyStrings()
{
    return(areStringsAlphabetized("", ""));
}

bool test_alphabetized2_FirstStringEmpty()
{
    return(areStringsAlphabetized("", "a"));
}

bool test_alphabetized3_SecondStringEmpty()
{
    return(!areStringsAlphabetized("a", ""));
}

bool test_alphabetized4_StringsAreAlphabetized()
{
    return(areStringsAlphabetized("aardvark", "abacus"));
}

bool test_alphabetized5_StringsAreNotAlphabetized()
{
    return(!areStringsAlphabetized("backward", "backgammon"));
}

void test_areStringsAlphabetized()
{
    assert(test_alphabetized1_TwoEmptyStrings());
    assert(test_alphabetized2_FirstStringEmpty());
    assert(test_alphabetized3_SecondStringEmpty());
    assert(test_alphabetized4_StringsAreAlphabetized());
    assert(test_alphabetized5_StringsAreNotAlphabetized());
}