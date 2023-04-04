#pragma once
#include <assert.h>
#include "stringUtilities.h"

bool test_Alphabetized1_TwoEmptyStrings()
{
    return areStringsAlphabetized("", "");
}

bool test_Alphabetized2_FirstStringEmpty()
{
    return areStringsAlphabetized("", "a");
}

bool test_Alphabetized3_SecondStringEmpty()
{
    return !areStringsAlphabetized("a", "");
}

bool test_Alphabetized4_StringsAreAlphabetized()
{
    return areStringsAlphabetized("aardvark", "abacus");
}

bool test_Alphabetized5_StringsAreNotAlphabetized()
{
    return !areStringsAlphabetized("backward", "backgammon");
}

void test_areStringsAlphabetized()
{
    assert(test_Alphabetized1_TwoEmptyStrings());
    assert(test_Alphabetized2_FirstStringEmpty());
    assert(test_Alphabetized3_SecondStringEmpty());
    assert(test_Alphabetized4_StringsAreAlphabetized());
    assert(test_Alphabetized5_StringsAreNotAlphabetized());
}