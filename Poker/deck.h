#pragma once
#include <string>

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

class deck
{
private:
    int cards[52];
    int countCardsDrawn;

    void riffleShuffle();

public:
    deck();
    ~deck();
    void shuffle();
    void playHand(int numPlayers);
    void print();

    friend class hand;
};

class hand
{
private:
    int cards[5];    
    handResult result;

    hand(deck *deck);
    ~hand();
    void print();

    friend class deck;
};