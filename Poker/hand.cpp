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

bool hand::containsCard(int value)
{
    for(int i=0; i<5; ++i)
    {
        if(cards[i] == value) return true;
    }
    return false;
}

int hand::containsOnePair()
{
    // NB: assumes you've already verified the hand  
    // does not contain a better result!
    // returns the value of the pair (e.g. pair of Queens -> 12)
    // or 0 if no pair found

    for(int i=0; i<5; ++i)
    {
        int value = cards[i]%13;
        for(int j=i+1; j<5; ++j)
        {
            if(value == cards[j]%13)
            {
                if(value == 0) return 13; //King%13 = 0 but 0 is reserved as the negative result
                else return value;
            }
        }
    }

    return 0;
}

void hand::drawCards(deck *deck)
{
    for(int i=0; i<5; ++i)
    {
        cards[i] = deck->cards[deck->countCardsDrawn];
        ++deck->countCardsDrawn;
    }

    //calculate result   
    if(containsCard(39) && containsCard(38) && containsCard(37) && containsCard(36) && containsCard(35)) result = ROYAL_FLUSH;
    else if(false) result = STRAIGHT_FLUSH;
    else if(false) result = FOUR_OF_A_KIND;
    else if(false) result = FULL_HOUSE;
    else if(false) result = FLUSH;
    else if(false) result = STRAIGHT;
    else if(false) result = THREE_OF_A_KIND;
    else if(false) result = TWO_PAIR;
    else if(containsOnePair()) result = ONE_PAIR;
    else result = HIGH_CARD;
}

void hand::print()
{
    std::string output;
    for(int i=0; i<5; ++i)
    {
        output.append(getCardValue(cards[i]).append(" "));
    }

    switch (result)
    {
    case ROYAL_FLUSH:
        output.append("- Royal Flush\n");
        break;
    case STRAIGHT_FLUSH:
        output.append("- Straight Flush\n");
        break;
    case FOUR_OF_A_KIND:
        output.append("- Four of a Kind\n");
        break;
    case FULL_HOUSE:
        output.append("- Full House\n");
        break;
    case FLUSH:
        output.append("- Flush\n");
        break;
    case STRAIGHT:
        output.append("- Straight\n");
        break;
    case THREE_OF_A_KIND:
        output.append("- Three of a Kind\n");
        break;
    case TWO_PAIR:
        output.append("- Two Pair\n");
        break;
    case ONE_PAIR:
        output.append("- One Pair\n");
        break;
    case HIGH_CARD:
        output.append("- High Card\n");
        break;  
    }
    printf("%s", output.c_str());
}