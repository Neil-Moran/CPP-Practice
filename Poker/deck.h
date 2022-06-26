#pragma once
#include <string>

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