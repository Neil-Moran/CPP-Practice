#pragma once

#include "card.h"
#include "deck.h"
#include "hand.h"

void hand::drawCards(deck *deck)
{
    for(int i=0; i<5; ++i)
    {
        cards[i] = deck->cards[deck->countCardsDrawn];
        ++deck->countCardsDrawn;
    }

    calculateResult();
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

void hand::calculateResult()
{
    // we're going to sort the hand for easier result calculation, but store the original order to be displayed on the screen
    int cardsCopy[5] = 
    {
        cards[0], cards[1], cards[2], cards[3], cards[4], 
    }; 

    quickSort(cards, 0, 4); // sort the hand by value, ignoring suit

    // calculate result   
    bool straight = containsStraight();
    bool flush = containsFlush();
    
    if(straight && flush) 
    {
        if(cards[3]%13 == 0) result = ROYAL_FLUSH; //if there is a straight flush and the fourth card is a King (can't check fifth card is an Ace as it could be 2 3 4 5 A)
        else result = STRAIGHT_FLUSH;
    }
    else if(straight) result = STRAIGHT; // there are better results but none are possible if there is a straight
    else if(flush) result = FLUSH; // there are better results but none are possible if there is a flush
    else if(getFourOfAKind()) result = FOUR_OF_A_KIND;
    else if(containsFullHouse()) result = FULL_HOUSE;
    else if(getThreeOfAKind()) result = THREE_OF_A_KIND;
    else if(containsTwoPair()) result = TWO_PAIR;
    else if(getLowPair()) result = ONE_PAIR;
    else result = HIGH_CARD;

    calculateScore();

    // return hand to original order
    for(int i=0; i<5; ++i)
    {
        cards[i] = cardsCopy[i];
    }
}

void hand::calculateScore()
{
    // NB: Assumes hand is currently sorted

    uint64_t multiplier = 100000000000; // multiplier to weight different tie break conditions, reduced every time it's used
    score = result * multiplier; // result is most important differentiator
    multiplier /= 100;

    int highCard, secondPair, currCard; // various card variables used below

    // add tie break scores depending on hand
    switch(result)
    {
    case ROYAL_FLUSH: // whichever hand is composed of the highest ranking suit wins
        // the card IDs are ordered so that S > H > D > C, so just add any one card to the score
        score += cards[4];
        break;
    case STRAIGHT_FLUSH: //same as straight, fall through
    case STRAIGHT: // only highest card matters 
        highCard = cards[4]%13;
        if(highCard < 2) highCard += 13;

        if(highCard == 14 && cards[3]%13 == 5) highCard = 5; // if the straight is A 2 3 4 5, the high card is 5

        score += highCard;
        break;
    case FULL_HOUSE: // fall through, check TOAK then the pair
    case FOUR_OF_A_KIND:
        highCard = getThreeOfAKind(); // TOAK is also FOAK, and this lets Full House use the same logic! 
        score += highCard * multiplier;
        multiplier /= 100;
        
        // add the score of the other card (if FOAK) or pair (if Full House) apart from the TOAK
        // that value must be either the first or last card 
        if(cards[4]%13 != cards[2]%13) 
            currCard = cards[4]%13;
        else currCard = cards[0]%13;

        if(currCard < 2) currCard += 13;

        score += currCard * multiplier;
        break;
    case THREE_OF_A_KIND:
        // add TOAK value
        highCard = getThreeOfAKind();
        score += highCard * multiplier;
        multiplier /= 100;

        // add non-TOAK values
        for(int j=4; j>=0; --j)
        {
            currCard = cards[j]%13;
            if(currCard < 2) currCard += 13;

            if(currCard != highCard)
            {
                score += currCard * multiplier;
                multiplier /= 100;
            }
        }
        break;
    case TWO_PAIR:
        // add high pair value
        highCard = getHighPair();
        score += highCard * multiplier;
        multiplier /= 100;

        // add low pair value
        secondPair = getLowPair();
        score += secondPair * multiplier;
        multiplier /= 100;

        // add the non-pair value, it must be card 1, 3 or 5
        for(int j=4; j>=0; j-=2)
        {
            currCard = cards[j]%13;
            if(currCard < 2) currCard += 13;

            if(currCard != highCard && currCard != secondPair)
            {
                score += currCard * multiplier;
                break;
            }
        }
        break;
    case ONE_PAIR:
        // add pair value
        highCard = getLowPair();
        score += highCard * multiplier;
        multiplier /= 100;

        // add non-pair values
        for(int j=4; j>=0; --j)
        {
            currCard = cards[j]%13;
            if(currCard < 2) currCard += 13;

            if(currCard != highCard)
            {
                score += currCard * multiplier;
                multiplier /= 100;
            }
        }
        break;
    case FLUSH: // fall through and add high card scores
    case HIGH_CARD:
        for(int j=4; j>=0; --j)
        {
            highCard = cards[j]%13;
            if(highCard < 2) highCard += 13;

            score += highCard * multiplier;
            multiplier /= 100;
        }
        break;
    }
}

bool hand::containsStraight()
{
    for(int i=0; i<4; ++i)
    {
        // this is ugly - we order the hand with Aces high
        // so if the last two cards are 5 and an Ace, then
        // we have a straight of A 2 3 4 5 and should return true;
        if(i==3 && cards[i]%13 == 5 && cards[i+1]%13 == 1) return true;

        if((cards[i]%13 + 1)%13 != cards[i+1]%13) return false;
    }
    return true;
}

bool hand::containsFlush()
{
    int suit = (cards[0]-1)/13;
    for(int i=1; i<5; ++i)
    {
        if((cards[i]-1)/13 != suit) return false;
    }
    return true;
}

int hand::getFourOfAKind()
{
    // since the hand is in order we can verify this by comparing
    // cards 1 and 4, 2 and 5 - if either match we have FOAK!

    if(cards[0]%13 == cards[3]%13 
    || cards[1]%13 == cards[4]%13)
    {
        int value = cards[2]%13; //if we have FOAK the middle card must have the correct value to return
        if(value < 2) value += 13; //ensure Ace(1) and King(13) are high
        return value;
    }

    return 0;
}

bool hand::containsFullHouse()
{
    // since the hand is in order we can verify this with a few comparisons
    // we need either a pair on the left and three of a kind on the right,
    // or vice versa
    if(cards[0]%13 == cards[1]%13 && cards[2]%13 == cards[4]%13
    || cards[0]%13 == cards[2]%13 && cards[3]%13 == cards[4]%13)
        return true;
    else return false;
}

int hand::getThreeOfAKind()
{
    // used to check for three of a kind - NB: assumes you've already  
    // verified the hand does not contain a better result!
    // since the hand is in order we can verify this by comparing
    // cards 1 and 3, 2 and 4, 3 and 5 - if any match we have TOAK!

    if(cards[0]%13 == cards[2]%13 
    || cards[1]%13 == cards[3]%13 
    || cards[2]%13 == cards[4]%13)
    {
        int value = cards[2]%13; //if we have TOAK the middle card must have the correct value to return
        if(value < 2) value += 13; //ensure Ace(1) and King(13) are high
        return value;
    }

    return 0;
}

int hand::getLowPair()
{
    // used to check for one pair - NB: assumes you've already  
    // verified the hand does not contain a better result!
    // traverses the sorted hand and returns the value of the first pair 
    // (e.g. pair of Queens -> 12) or 0 if no pair found

    for(int i=1; i<5; ++i)
    {
        int value = cards[i]%13;
        if(value == cards[i-1]%13)
        {
            if(value < 2) value += 13; //ensure Ace(1) and King(13) are high
            return value;
        }
    }

    return 0;
}

int hand::getHighPair()
{
    // traverses the sorted hand BACKWARDS and returns the value 
    // of the first pair, i.e. the pair with the highest value
    // (e.g. pair of Queens -> 12) or 0 if no pair found
    for(int i=4; i>0; --i)
    {
        int value = cards[i]%13;
        if(value == cards[i-1]%13)
        {
            if(value < 2) value += 13; //ensure Ace(1) and King(13) are high
            return value;
        }
    }

    return 0;
}

bool hand::containsTwoPair()
{
    // used to check for two pair - NB: assumes you've already  
    // verified the hand does not contain a better result!
    // if the hand contains a low pair and a high pair, and
    // they don't have the same value, then there must be two pairs
    int lowPair = getLowPair();
    int highPair = getHighPair();

    if(lowPair && highPair && lowPair != highPair) return true;
    else return false;
}