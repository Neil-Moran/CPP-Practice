#include "deck.h"
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

std::string deck::getCardValue(int card)
{
    std::string currentCard;
    
    int value = card%13;

    switch(value)
    {
    case 1:
        currentCard.append("A");
        break;

    case 11:
        currentCard.append("J");
        break;

    case 12:
        currentCard.append("Q");
        break;

    case 0:
        currentCard.append("K");
        break;
    
    default:
        currentCard.append(std::to_string(value));
        break;
    }

    int suit = (card-1)/13;

    switch (suit)
    {
    case 0:
        currentCard.append("C");
        break;

    case 1:
        currentCard.append("H");
        break;

    case 2:
        currentCard.append("S");
        break;

    case 3:
        currentCard.append("D");
        break;
    
    default:
        break;
    }

    return currentCard;
}