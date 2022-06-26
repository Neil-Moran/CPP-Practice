#pragma once

#include "card.h"
#include "deck.h"
#include "hand.h"
#include "squirrel3.h"
#include <stdio.h>
#include <string>

deck::deck()
{   
    countCardsDrawn = 0;

    for(int i=0; i<52; ++i)
    {
        cards[i] = i+1;
    }
}

deck::~deck()
{
}

void deck::riffleShuffle()
{
    int cards_copy[52];
    memcpy(cards_copy, cards, sizeof(cards));

    // simulated riffle shuffle: split the deck in half, then 
    // randomly add cards back into the deck from both halves
    int i = 0, l = 0, r = 26;

    while(l<26 && r<52)
    {
        if(flipCoin()) // flip a coin; if tails we take a card from the left packet...
        {
            cards[i] = cards_copy[l];
            ++l;
        }

        else // ...if heads we take a card from the right packet
        {
            cards[i] = cards_copy[r];
            ++r;
        }

        ++i;
    }

    // we've exhausted one of the packets, finish off the cards from the remaining packet
    if(l<26)
    {
        for(; l<26; ++l, ++i)
        {
            cards[i] = cards_copy[l];
        }
    }

    if(r<52)
    {
        for(; r<52; ++r, ++i)
        {
            cards[i] = cards_copy[r];
        }
    }
}

void deck::shuffle()
{
    // do seven riffle shuffles https://math.hmc.edu/funfacts/seven-shuffles/
    for(int i=0; i<7; ++i)
    {
        riffleShuffle();
    }
    countCardsDrawn = 0;
}

void deck::playHand(int numPlayers)
{
    hand player1(this);
    player1.print();
}

void deck::print()
{
    std::string result;
    for(int i=0; i<52; ++i)
    {
        result.append(getCardValue(cards[i]).append(" "));
        if((i+1)%13 == 0) result.append("\n");
    }
    printf("%s", result.c_str());
}