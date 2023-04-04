#pragma once
#include <assert.h>
#include "stringUtilities.h"

bool test_Identical1_TwoEmptyStrings()
{
    return areStringsIdentical("","");
}

bool test_Identical2_FirstStringEmpty()
{
    return !areStringsIdentical("","x");
}

bool test_Identical3_SecondStringEmpty()
{
    return !areStringsIdentical("X","");
}

bool test_Identical4_StringsMatch()
{
    return areStringsIdentical("wonderful","wonderful");
}

bool test_Identical5_StringsMatchExceptCapitalLetter()
{
    return !areStringsIdentical("Polish","polish");
}

bool test_Identical6_StringsMatchWithSpacesAndPunctuation()
{
    return areStringsIdentical("To die, to sleep— To sleep—perchance to dream.","To die, to sleep— To sleep—perchance to dream.");
}

bool test_Identical7_StringsMatchNumeric()
{
    return areStringsIdentical("0123456789","0123456789");
}

void test_areStringsIdentical()
{
    assert(test_Identical1_TwoEmptyStrings());
    assert(test_Identical2_FirstStringEmpty());
    assert(test_Identical3_SecondStringEmpty());
    assert(test_Identical4_StringsMatch());
    assert(test_Identical5_StringsMatchExceptCapitalLetter());
    assert(test_Identical6_StringsMatchWithSpacesAndPunctuation());
    assert(test_Identical7_StringsMatchNumeric());
}