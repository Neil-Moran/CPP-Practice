#pragma once
#include <assert.h>
#include "stringUtilities.h"

bool test_STOI1_EmptyString()
{
    return (convertStringToInt("") == 0);
}

bool test_STOI2_0()
{
    return (convertStringToInt("0") == 0);
}

bool test_STOI3_123()
{
    return (convertStringToInt("123") == 123);
}

bool test_STOI4_MaxInt()
{
    return (convertStringToInt("2147483647") == 2147483647);
}

bool test_STOI5_MaxIntPlus1()
{
    return (convertStringToInt("2147483648") == 0);
}

bool test_STOI6_ExtremelyLargeNumber()
{
    return (convertStringToInt("9999999999999999") == 0);
}

bool test_STOI7_VeryLargeNumber()
{
    return (convertStringToInt("92147483647") == 0);
}

bool test_STOI8_NonNumeric()
{
    return (convertStringToInt("one") == 0);
}

void test_convertStringToInt()
{
    assert(test_STOI1_EmptyString());
    assert(test_STOI2_0());
    assert(test_STOI3_123());
    assert(test_STOI4_MaxInt());
    assert(test_STOI5_MaxIntPlus1());
    assert(test_STOI6_ExtremelyLargeNumber());
    assert(test_STOI7_VeryLargeNumber());
    assert(test_STOI8_NonNumeric());
}