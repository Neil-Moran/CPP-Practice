#pragma once

#include <stdio.h>
#include "areStringsAlphabetizedTest.h"
#include "areStringsIdenticalTest.h"
#include "convertStringToIntTest.h"
#include "isAnagramTest.h"
#include "sortStringTest.h"

void runAllTests()
{
    bool allTestsPassed = true;
    allTestsPassed &= areStringsAlphabetizedTest(); 
    allTestsPassed &= areStringsIdenticalTest();
    allTestsPassed &= convertStringToIntTest();
    allTestsPassed &= isAnagramTest();
    allTestsPassed &= sortStringTest();

    if(allTestsPassed) printf("\033[0;32mAll Tests Passed!\n\033[0m");
}