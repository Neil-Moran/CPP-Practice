#pragma once

#include <stdio.h>
#include <string>
#include <vector>

/*  A specific test case for a function with an input of two strings and output of bool
    testCaseName: a description of what use case you're testing
    input1: first input string
    input2: second input string
    expectedResult: output bool
*/
struct stringStringBoolTestCase
{
    char *testCaseName;
    char *input1, *input2;
    bool expectedResult;

    stringStringBoolTestCase(char *_testCaseName, char *_input1, char *_input2, bool _expectedResult) 
        : testCaseName(_testCaseName), input1(_input1), input2(_input2), expectedResult(_expectedResult){}

    bool run(bool (*testFunction)(char*, char*))
    {
        if(testFunction(input1, input2) != expectedResult)
        {
            printf("%s failed; Actual: %s Expected: %s\n", testCaseName, expectedResult ? "false" : "true", expectedResult ? "true" : "false");
            return false;
        }
        return true;
    }
};

/*  A test for a function with an input of two strings and output of bool
    testName: a descriptive name (I recommend the function you're testing)
    testFunction: the function you're testing
*/
struct stringStringBoolTest
{
    char *testName;
    bool (*testFunction)(char*, char*);
    std::vector<stringStringBoolTestCase> testCases;

    stringStringBoolTest(char *_testName, bool (*_testFunction)(char*, char*))
    : testName(_testName), testFunction(_testFunction){}

    void addTestCase(char *testCaseName, char *input1, char *input2, bool expectedResult)
    {
        testCases.push_back(stringStringBoolTestCase(testCaseName, input1, input2, expectedResult));
    }

    bool runAllTests()
    {
        int failedTests = 0;

        for(size_t i=0; i<testCases.size(); ++i)
        {
            if(!testCases[i].run(testFunction)) ++failedTests;
        }

        if(failedTests > 0)
        {
            printf("%s: %i/%i tests failed\n", testName, failedTests, testCases.size());
            return false;
        }
        else 
        {
            printf("%s: All tests passed\n", testName);
            return true;
        }
    }
};

/*  A specific test case for a function with an input of string and output of string
    testCaseName: a description of what use case you're testing
    inputString: input string
    expectedResult: output string
*/
struct stringStringTestCase
{
    char *testCaseName;
    char *inputString;
    char *expectedResult;

    stringStringTestCase(char *_testCaseName, char *_inputString, char *_expectedResult) 
        : testCaseName(_testCaseName), inputString(_inputString), expectedResult(_expectedResult){}

    bool run(void (*testFunction)(char[]), bool (*compareFunction)(char[], char[]))
    {
        char actualResult[99];
        strcpy_s(actualResult, inputString);
        testFunction(actualResult);

        if(!compareFunction(actualResult, expectedResult))
        {
            printf("%s failed; Actual: %s Expected: %s\n", testCaseName, actualResult, expectedResult);
            return false;
        }
        return true;
    }
};

/*  A test for a function with an input of string and output of string
    testName: a descriptive name (I recommend the function you're testing)
    testFunction: the function you're testing
    compareFunction: a function to compare the actual and expected result of the test
*/
struct stringStringTest
{
    char *testName;
    void (*testFunction)(char[]);
    bool (*compareFunction)(char[], char[]);
    std::vector<stringStringTestCase> testCases;

    stringStringTest(char *_testName, void (*_testFunction)(char[]),
    bool (*_compareFunction)(char[], char[]))
    : testName(_testName), testFunction(_testFunction),
    compareFunction(_compareFunction) {}

    void addTestCase(char *testCaseName, char *inputString, char *expectedResult)
    {
        testCases.push_back(stringStringTestCase(testCaseName, inputString, expectedResult));
    }

    bool runAllTests()
    {
        int failedTests = 0;

        for(size_t i=0; i<testCases.size(); ++i)
        {
            if(!testCases[i].run(testFunction, compareFunction)) ++failedTests;
        }

        if(failedTests > 0)
        {
            printf("%s: %i/%i tests failed\n", testName, failedTests, testCases.size());
            return false;
        }
        else 
        {
            printf("%s: All tests passed\n", testName);
            return true;
        }
    }
};

