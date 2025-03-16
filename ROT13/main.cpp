#include <stdio.h>
#include <string>
#include "rot13.hpp"

using std::string;

int main()
{
    const int MIN_LENGTH = 3;
    string dictionary = "words_alpha.txt"; // from https://github.com/dwyl/english-words
    //string dictionary = "mit_10000_words.txt"; // from https://www.mit.edu/~ecprice/wordlist.10000

    string output = findRot13Pairs(dictionary, MIN_LENGTH);

    printf("\n--- ROT13 PAIRS ---\n%s", output.c_str());
    
    return 0;
}