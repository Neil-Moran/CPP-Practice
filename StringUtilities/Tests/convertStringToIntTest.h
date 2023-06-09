#pragma once

#include "nam_test.h"
#include "stringUtilities.h"

bool convertStringToIntTest()
{
    stringIntTest convertStringToIntTest("convertStringToInt()", convertStringToInt);

    convertStringToIntTest.addTestCase("Empty String", "", 0);
    convertStringToIntTest.addTestCase("0", "0", 0);
    convertStringToIntTest.addTestCase("123", "123", 123);
    convertStringToIntTest.addTestCase("Max Int", "2147483647", 2147483647);
    convertStringToIntTest.addTestCase("Max Int Plus 1", "2147483648", 0);
    convertStringToIntTest.addTestCase("Extremely Large Number", "9999999999999999", 0);
    convertStringToIntTest.addTestCase("Very Large Number", "92147483647", 0);
    convertStringToIntTest.addTestCase("Non Numeric", "one", 0);
    convertStringToIntTest.addTestCase("Negative Number", "-123", -123);
    convertStringToIntTest.addTestCase("Negative Max Int", "-2147483647", -2147483647);
    convertStringToIntTest.addTestCase("Positive Max Int", "+2147483647", +2147483647);
    convertStringToIntTest.addTestCase("Negative Max Int Minus 1", "-2147483648", 0 - _CRT_INT_MAX - 1);
    convertStringToIntTest.addTestCase("Negative Max Int Minus 2", "-2147483649", 0);
    convertStringToIntTest.addTestCase("Negative Zero", "-0", 0);
    convertStringToIntTest.addTestCase("Positive Zero", "+0", 0);
    convertStringToIntTest.addTestCase("Very Large Negative Number", "-92147483647", 0);
    convertStringToIntTest.addTestCase("Leading Zero", "0999", 999);

    return convertStringToIntTest.runAllTests();
}