#pragma once

#include <stdio.h>
#include "areStringsAlphabetizedTest.h"
#include "areStringsIdenticalTest.h"
#include "convertStringToIntTest.h"
#include "sortStringTest.h"

void runAllTests()
{
    test_areStringsAlphabetized();
    test_areStringsIdentical();
    test_convertStringToInt();
    
    if(sortStringTest()) printf("All Tests Passed!\n");
}