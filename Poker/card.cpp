#pragma once

#include <string>

std::string getCardValue(int card)
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