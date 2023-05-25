#pragma once

#include <stdio.h>
#include "areStringsAlphabetizedTest.h"
#include "areStringsIdenticalTest.h"
#include "convertStringToIntTest.h"

void runAllTests()
{
    test_areStringsAlphabetized();
    test_areStringsIdentical();
    test_convertStringToInt();

    printf("All Tests Passed!\n");
}