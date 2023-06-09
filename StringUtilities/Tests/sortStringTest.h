#pragma once

#include "nam_test.h"
#include "stringUtilities.h"

bool sortStringTest()
{
    stringStringTest sortStringTest("sortString()", sortString, areStringsIdentical);

    sortStringTest.addTestCase("Sort Empty String", "", "");
    sortStringTest.addTestCase("Sort Single Char", "a", "a");
    sortStringTest.addTestCase("Sort Already Sorted String", "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz");
    sortStringTest.addTestCase("Sort Scrambled String", "spoilage", "aegilops");
    sortStringTest.addTestCase("Sort Backwards String", "ylifeeb", "beefily");

    return sortStringTest.runAllTests();
}