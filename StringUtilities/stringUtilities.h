#pragma once

// returns true if s1 and s2 are in alphabetical order
// returns true in the case of a tie
// NB:  only tested on strings containing only letters from the Roman alphabet
//      behaviour undefined for other chars e.g. spaces, punctuation, emoji, non-Roman chars...
bool areStringsAlphabetized(char *s1, char *s2); 