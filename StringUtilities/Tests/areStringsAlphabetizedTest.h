#pragma once

#include "nam_test.h"
#include "stringUtilities.h"

bool areStringsAlphabetizedTest()
{
    stringStringBoolTest areStringsAlphabetizedTest("areStringsAlphabetized()", areStringsAlphabetized);

    areStringsAlphabetizedTest.addTestCase("Two Empty Strings", "", "", true);
    areStringsAlphabetizedTest.addTestCase("First String Empty", "", "a", true);
    areStringsAlphabetizedTest.addTestCase("Second String Empty", "a", "", false);
    areStringsAlphabetizedTest.addTestCase("Strings Are Alphabetized", "aardvark", "abacus", true);
    areStringsAlphabetizedTest.addTestCase("Strings Are Not Alphabetized", "backward", "backgammon", false);
    
    return areStringsAlphabetizedTest.runAllTests();
}