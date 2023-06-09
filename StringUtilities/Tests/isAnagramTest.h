#pragma once

#include "nam_test.h"
#include "stringUtilities.h"

bool isAnagramTest()
{
    stringStringBoolTest isAnagramTest("isAnagram()", isAnagram);

    isAnagramTest.addTestCase("Both Strings Empty", "", "", true);
    isAnagramTest.addTestCase("Identical Strings", "popcorn", "popcorn", true);
    isAnagramTest.addTestCase("Strings Are Anagrams", "listen", "silent", true);
    isAnagramTest.addTestCase("Strings Are Not Anagrams", "thing", "glint", false);
    isAnagramTest.addTestCase("Strings Are Anagrams All Caps", "RESISTANCE", "ANCESTRIES", true);
    isAnagramTest.addTestCase("Strings Are Anagrams Mixed Caps", "Neil", "line", true);
    isAnagramTest.addTestCase("Extremely Long Strings", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "zyxwvutsrqponmlkjihgfedcba", true);
    isAnagramTest.addTestCase("Strings Are Anagrams With Non Alphabetic Chars", 
    "To be or not to be: that is the question, whether tis nobler in the mind to suffer the slings and arrows of outrageous fortune.", 
    "In one of the Bard's best-thought-of tragedies, our insistent hero, Hamlet, queries on two fronts about how life turns rotten.", true);
    isAnagramTest.addTestCase("First String Much Longer", "  ######Alec Guinness !!!!!!!", "Genuine Class", true);
    isAnagramTest.addTestCase("Second String Much Longer", "Slot Machines", "$$$ Cash Lost In 'Em €€€", true);

    return isAnagramTest.runAllTests();
}