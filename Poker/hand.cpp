#pragma once

#include "card.h"
#include "deck.h"
#include "hand.h"

hand::hand()
{
}

hand::~hand()
{
}

void hand::drawCards(deck *deck)
{
    for(int i=0; i<5; ++i)
    {
        cards[i] = deck->cards[deck->countCardsDrawn];
        ++deck->countCardsDrawn;
    }
}

void hand::print()
{
    std::string output;
    for(int i=0; i<5; ++i)
    {
        output.append(getCardValue(cards[i]).append(" "));
    }
    printf("%s\n", output.c_str());
}