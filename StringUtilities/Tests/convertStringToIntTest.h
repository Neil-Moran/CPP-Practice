#pragma once
#include <assert.h>
#include "stringUtilities.h"

bool test_StoI1_EmptyString()
{
    return (convertStringToInt("") == 0);
}

bool test_StoI2_0()
{
    return (convertStringToInt("0") == 0);
}

bool test_StoI3_123()
{
    return (convertStringToInt("123") == 123);
}

bool test_StoI4_MaxInt()
{
    return (convertStringToInt("2147483647") == 2147483647);
}

bool test_StoI5_MaxIntPlus1()
{
    return (convertStringToInt("2147483648") == 0);
}

bool test_StoI6_ExtremelyLargeNumber()
{
    return (convertStringToInt("9999999999999999") == 0);
}

bool test_StoI7_VeryLargeNumber()
{
    return (convertStringToInt("92147483647") == 0);
}

bool test_StoI8_NonNumeric()
{
    return (convertStringToInt("one") == 0);
}

bool test_StoI9_NegativeNumber()
{
    return (convertStringToInt("-123") == -123);
}

bool test_StoI10_NegativeMaxInt()
{
    return (convertStringToInt("-2147483647") == -2147483647);
}

bool test_StoI11_PositiveMaxInt()
{
    return (convertStringToInt("+2147483647") == +2147483647);
}

bool test_StoI12_NegativeMaxIntMinus1()
{
    return (convertStringToInt("-2147483648") == 0 - _CRT_INT_MAX - 1);
}

bool test_StoI13_NegativeMaxIntMinus2()
{
    return (convertStringToInt("-2147483649") == 0);
}

bool test_StoI14_NegativeZero()
{
    return (convertStringToInt("-0") == 0);
}

bool test_StoI15_PositiveZero()
{
    return (convertStringToInt("+0") == 0);
}

bool test_StoI16_VeryLargeNegativeNumber()
{
    return (convertStringToInt("-92147483647") == 0);
}

void test_convertStringToInt()
{
    assert(test_StoI1_EmptyString());
    assert(test_StoI2_0());
    assert(test_StoI3_123());
    assert(test_StoI4_MaxInt());
    assert(test_StoI5_MaxIntPlus1());
    assert(test_StoI6_ExtremelyLargeNumber());
    assert(test_StoI7_VeryLargeNumber());
    assert(test_StoI8_NonNumeric());
    assert(test_StoI9_NegativeNumber());
    assert(test_StoI10_NegativeMaxInt());
    assert(test_StoI11_PositiveMaxInt());
    assert(test_StoI12_NegativeMaxIntMinus1());
    assert(test_StoI14_NegativeZero());
    assert(test_StoI15_PositiveZero());
    assert(test_StoI16_VeryLargeNegativeNumber());
}