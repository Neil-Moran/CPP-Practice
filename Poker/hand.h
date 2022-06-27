#pragma once

enum handResult {
    ROYAL_FLUSH,
    STRAIGHT_FLUSH,
    FOUR_OF_A_KIND,
    FULL_HOUSE,
    FLUSH,
    STRAIGHT,
    THREE_OF_A_KIND,
    TWO_PAIR,
    ONE_PAIR,
    HIGH_CARD
};

class hand
{
private:
    int cards[5];    
    handResult result;

    hand();
    ~hand();   
    bool containsCard(int value);
    bool containsStraight();
    bool containsFlush();
    int getFourOfAKind();
    bool containsFullHouse();
    int getThreeOfAKind();
    int getLowPair();
    int getHighPair();
    bool containsTwoPair();
    void drawCards(deck *deck);
    void print();

    friend class deck;
};