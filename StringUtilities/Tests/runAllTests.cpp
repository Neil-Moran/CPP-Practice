#pragma once

#include <stdio.h>
#include "areStringsAlphabetizedTest.h"
#include "areStringsIdenticalTest.h"
#include "convertStringToIntTest.h"
#include "sortStringTest.h"

void runAllTests()
{
    test_convertStringToInt();

    if(areStringsAlphabetizedTest() && areStringsIdenticalTest() && sortStringTest()) printf("All Tests Passed!\n");
}