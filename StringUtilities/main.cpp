#include <stdio.h>
#include "test_areStringsAlphabetized.h"
#include "test_areStringsIdentical.h"

int main()
{
    test_areStringsAlphabetized();
    test_areStringsIdentical();

    printf("All Tests Passed!\n");

    return 0;
}