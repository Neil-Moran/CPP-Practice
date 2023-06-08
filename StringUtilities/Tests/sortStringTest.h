#pragma once
#include <assert.h>
#include "stringUtilities.h"

bool test_sortString_EmptyString()
{
    char actualResult[] = "";
    sortString(actualResult);
    char expectedResult[] = "";

    return (areStringsIdentical(actualResult, expectedResult));
}

bool test_sortString_SingleChar()
{
    char actualResult[] = "a";
    sortString(actualResult);
    char expectedResult[] = "a";

    return (areStringsIdentical(actualResult, expectedResult));
}

bool test_sortString_AlreadySorted()
{
    char actualResult[] = "abcdefghijklmnopqrstuvwxyz";
    sortString(actualResult);
    char expectedResult[] = "abcdefghijklmnopqrstuvwxyz";

    return (areStringsIdentical(actualResult, expectedResult));
}

bool test_sortString_SortsCorrectly()
{
    char actualResult[] = "spoilage";
    sortString(actualResult);
    char expectedResult[] = "aegilops";

    return (areStringsIdentical(actualResult, expectedResult));
}

bool test_sortString_SortBackwardsWord()
{
    char actualResult[] = "ylifeeb";
    sortString(actualResult);
    char expectedResult[] = "beefily";

    return (areStringsIdentical(actualResult, expectedResult));
}

void test_sortString()
{
    assert(test_sortString_EmptyString());
    assert(test_sortString_SingleChar());
    assert(test_sortString_AlreadySorted());
    assert(test_sortString_SortsCorrectly());
    assert(test_sortString_SortBackwardsWord());
}