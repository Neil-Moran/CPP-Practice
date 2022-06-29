#pragma once
#include <string>

class deck
{
    friend class hand;

public:
    deck();
    void shuffle();
    void playGame(int numPlayers, int numHands);
    static std::string calculateResult(hand *players, int numPlayers);
    void print();  

private:
    int cards[52];
    int countCardsDrawn;

    void riffleShuffle();
    void playHand(int numPlayers);  
};