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

int hand::partition(int array[], int low, int high)
{
    int pivot = array[high]%13; //select the right-most element as a pivot (arbitrary)
    if(pivot == 0) pivot = 13;
    int pi = low; // will be the partition index, the index where the pivot belongs

    //find the correct index for the pivot
    for(int i=low; i<high; ++i)
    {
        int curr = array[i]%13;
        if(curr == 0) curr = 13;
        if(curr<=pivot)
        {
            if(i!=pi)
            {
                int temp = array[pi];
                array[pi] = array[i];
                array[i] = temp;
            }
            ++pi;
        }
    }

    if(pi != high) //move the pivot to the correct index, if not already there
    {
        int temp = array[pi];
        array[pi] = array[high];
        array[high] = temp;
    }
    return pi;
}

void hand::quickSort(int array[], int low, int high)
{
    if(low < high)
    {
        int pivot = partition(array, low, high);
        
        quickSort(array, low, pivot-1);
        quickSort(array, pivot+1, high);
    }
}

bool hand::containsCard(int value)
{
    for(int i=0; i<5; ++i)
    {
        if(cards[i] == value) return true;
    }
    return false;
}

bool hand::containsStraight()
{
    for(int i=0; i<4; ++i)
    {
        if(cards[i]%13 + 1 != cards[i+1]%13) return false;
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
        if(value == 0) return 13; //King%13 = 0 but 0 is reserved as the negative result
        else return value;
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
        if(value == 0) return 13; //King%13 = 0 but 0 is reserved as the negative result
        else return value;
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
            if(value == 0) return 13; //King%13 = 0 but 0 is reserved as the negative result
            else return value;
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
            if(value == 0) return 13; //King%13 = 0 but 0 is reserved as the negative result
            else return value;
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

void hand::drawCards(deck *deck)
{
    int cardsCopy[5]; // we're going to sort the hand for easier result calculation, but store the original order to be displayed on the screen

    for(int i=0; i<5; ++i)
    {
        cards[i] = deck->cards[deck->countCardsDrawn];
        cardsCopy[i] = cards[i];
        ++deck->countCardsDrawn;
    }

    quickSort(cards, 0, 4); // sort the hand by value, ignoring suit

    // calculate result   
    if(containsCard(27) && containsCard(39) && containsCard(38) && containsCard(37) && containsCard(36)) result = ROYAL_FLUSH;
    else 
    {
        bool straight = containsStraight();
        bool flush = containsFlush();
        if(straight && flush) result = STRAIGHT_FLUSH;
        else if(straight) result = STRAIGHT; // there are better results but none are possible if there is a straight
        else if(flush) result = FLUSH; // there are better results but none are possible if there is a flush
        else if(getFourOfAKind()) result = FOUR_OF_A_KIND;
        else if(containsFullHouse()) result = FULL_HOUSE;
        else if(getThreeOfAKind()) result = THREE_OF_A_KIND;
        else if(containsTwoPair()) result = TWO_PAIR;
        else if(getLowPair()) result = ONE_PAIR;
        else result = HIGH_CARD;
    }

    // return hand to original order
    for(int i=0; i<5; ++i)
    {
        cards[i] = cardsCopy[i];
    }
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