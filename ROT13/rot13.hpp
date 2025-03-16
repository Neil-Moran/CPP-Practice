#pragma once

#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include "timing.h"

using std::string;

// return the ROT13 of the input word
string rot13(string w)
{
    for(int i=0; w[i]; ++i)
    {
        // if char is A-M, shift it 13 forward
        if(w[i] >= 'a' && w[i] <= 'm'
            || w[i] >= 'A' && w[i] <= 'M')
        {
            w[i] += 13;
        }
        // if char is A-N, shift it 13 backward
        else if(w[i] >= 'n' && w[i] <= 'z'
            || w[i] >= 'N' && w[i] <= 'Z')
        {
            w[i] -=13;
        }
    }

    return w;
}

// using the input file as a dictionary, search for words that ROT13 to other valid words,
// ignoring all words shorter than the minimum length
string findRot13Pairs(string file, size_t minLength)
{
    std::vector<string> wordList;
    
    // parse dictionary into list
    {
        Timer t1;
        std::ifstream fs;
        fs.open(file);
        string word;

        while(std::getline(fs, word))
        {
            // ignore words that are shorter that minLength
            if(word.size() < minLength)
            {
                continue;
            }

            // if word is in first half of alphabet, ROT13 it and add to list
            if(word[0] <= 'm' || word[0] <= 'M')
            {
                wordList.push_back(rot13(word));
            }
            // if word is in second half of alphabet, just add it to list
            else
            {
                wordList.push_back(word);            
            }
        }

        fs.close();
        printf("Parsed dictionary\n");
    } //destroy t1 and print time

    // sort list
    {
        Timer t2;        
        std::sort(wordList.begin(), wordList.end());
        printf("\nSorted list\n");
    } //destroy t2 and print time

    string output;

    // find duplicates in list, these are are ROT13 pairs
    {
        Timer t3;
        for(size_t i = 0; i < wordList.size() - 1; ++i)
        {
            if(wordList[i] == wordList[i+1])
            {
                output += rot13(wordList[i]) + "\t<->\t" + wordList[i] + "\n";
                ++i; // skip the duplicate word
            }
        }
        printf("\nFound duplicates in list\n");
    } //destroy t3 and print time    

    return output;
}