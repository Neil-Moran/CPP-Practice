#pragma once

#include "nam_test.h"
#include "stringUtilities.h"

bool convertStringToIntTest()
{
    stringIntTest convertStringToIntTest("convertStringToInt()", convertStringToInt);

    convertStringToIntTest.addTestCase("EmptyString", "", 0);
    convertStringToIntTest.addTestCase("0", "0", 0);
    convertStringToIntTest.addTestCase("123", "123", 123);
    convertStringToIntTest.addTestCase("Max Int", "2147483647", 2147483647);
    convertStringToIntTest.addTestCase("MaxIntPlus1", "2147483648", 0);
    convertStringToIntTest.addTestCase("ExtremelyLargeNumber", "9999999999999999", 0);
    convertStringToIntTest.addTestCase("VeryLargeNumber", "92147483647", 0);
    convertStringToIntTest.addTestCase("NonNumeric", "one", 0);
    convertStringToIntTest.addTestCase("NegativeNumber", "-123", -123);
    convertStringToIntTest.addTestCase("NegativeMaxInt", "-2147483647", -2147483647);
    convertStringToIntTest.addTestCase("PositiveMaxInt", "+2147483647", +2147483647);
    convertStringToIntTest.addTestCase("NegativeMaxIntMinus1", "-2147483648", 0 - _CRT_INT_MAX - 1);
    convertStringToIntTest.addTestCase("NegativeMaxIntMinus2", "-2147483649", 0);
    convertStringToIntTest.addTestCase("NegativeZero", "-0", 0);
    convertStringToIntTest.addTestCase("PositiveZero", "+0", 0);
    convertStringToIntTest.addTestCase("VeryLargeNegativeNumber", "-92147483647", 0);
    convertStringToIntTest.addTestCase("LeadingZero", "0999", 999);

    return convertStringToIntTest.runAllTests();
}