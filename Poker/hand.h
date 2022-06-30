#pragma once

enum handResult {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH
};

class hand
{
    friend class deck;

private:
    int cards[5];    
    handResult result;
    uint64_t score;
    void drawCards(deck *deck);
    void print();

    void calculateResult();
    void calculateScore();
    bool containsStraight();
    bool containsFlush();
    int getFourOfAKind();
    bool containsFullHouse();
    int getThreeOfAKind();
    int getLowPair();
    int getHighPair();
    bool containsTwoPair();    
};