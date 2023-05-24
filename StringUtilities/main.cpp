#include <stdio.h>
#include "test_areStringsAlphabetized.h"
#include "test_areStringsIdentical.h"
#include "test_convertStringToInt.h"

int main()
{
    test_areStringsAlphabetized();
    test_areStringsIdentical();
    test_convertStringToInt();

    printf("All Tests Passed!\n");

    return 0;
}