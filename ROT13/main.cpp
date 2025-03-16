#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include "rot13.hpp"
#include "timing.h"

using std::string;

int main()
{
    string dictionary = "words_alpha.txt"; // from https://github.com/dwyl/english-words
    //string dictionary = "mit_10000_words.txt"; // from https://www.mit.edu/~ecprice/wordlist.10000

    std::ifstream fs;
    fs.open(dictionary);

    string word;
    std::vector<string> wordList;
    const size_t MIN_LENGTH = 3;

    // parse dictionary into list
    {
        Timer t1;
        while(std::getline(fs, word))
        {
            if(word.size() < MIN_LENGTH)
            {
                continue;
            }

            if(word[0] <= 'm' || word[0] <= 'M')
            {
                wordList.push_back(rot13(word));
            }
            else
            {
                wordList.push_back(word);            
            }
        }
        printf("Parsed dictionary\n");
    } //destroy t1 and print time

    // sort list
    {
        Timer t2;
        //std::sort(originalWords.begin(), originalWords.end());
        std::sort(wordList.begin(), wordList.end());
        printf("\nSorted list\n");
    } //destroy t2 and print time

    string output;

    // find duplicates in list
    {
        Timer t3;
        for(size_t i = 0; i < wordList.size() - 1; ++i)
        {
            if(wordList[i] == wordList[i+1])
            {
                output += rot13(wordList[i]) + " : " + wordList[i] + "\n";
                ++i;
            }
        }
        printf("\nFound duplicates in list\n");
    } //destroy t3 and print time    

    printf(output.c_str());
    fs.close();
    
    return 0;
}