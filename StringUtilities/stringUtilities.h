#pragma once

// NB: assuming null-terminated strings for all functions

// returns true if s1 and s2 are in alphabetical order
// returns true in the case of a tie
// NB:  only tested on strings containing only letters from the Roman alphabet
//      behaviour undefined for other chars e.g. spaces, punctuation, emoji, non-Roman chars...
bool areStringsAlphabetized(char *s1, char *s2); 

// returns true if s1 and s2 are completely identical, 
// including punctuation, white space, capitalization...
bool areStringsIdentical(char *s1, char *s2);

// returns s as a signed integer, or 0 if s is not a valid int
// valid examples: "0", "-123", "999", "+2147483647"
// invalid examples: "", "one", "0x123","-2147483648" (exceeds max int)
int convertStringToInt(char *s);

// returns true if s1 and s2 are anagrams of each other
// ignores case, i.e. isAnagram(Neil, line) = true
// ignores characters other than a-z, A-Z, i.e. isAnagram(racecar, car race!) = true
bool isAnagram(char *s1, char *s2); 

// sorts the string into alphabetical order
// only testing for strings comprising lowercase a-z
void sortString(char s[]);