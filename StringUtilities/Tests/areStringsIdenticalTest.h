#pragma once

#include "nam_test.h"
#include "stringUtilities.h"

bool areStringsIdenticalTest()
{
    stringStringBoolTest areStringsIdenticalTest("areStringsIdentical()", areStringsIdentical);

    areStringsIdenticalTest.addTestCase("Two Empty Strings", "", "", true);
    areStringsIdenticalTest.addTestCase("First String Empty", "", "x", false);
    areStringsIdenticalTest.addTestCase("Second String Empty", "X", "", false);
    areStringsIdenticalTest.addTestCase("Strings Match", "wonderful", "wonderful", true);
    areStringsIdenticalTest.addTestCase("Strings Match Except Capital Letter", "Polish","polish", false);
    areStringsIdenticalTest.addTestCase("Strings Match With Spaces And Punctuation", "To die, to sleep— To sleep—perchance to dream.","To die, to sleep— To sleep—perchance to dream.", true);
    areStringsIdenticalTest.addTestCase("Strings Match Numeric", "0123456789", "0123456789", true);
    
    return areStringsIdenticalTest.runAllTests();
}