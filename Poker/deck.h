#pragma once
#include <string>

class deck
{
    friend class hand;

public:
    deck(int numPacks = 1);
    ~deck();
    void shuffle();
    void playGame(int numPlayers, int numHands);
    static std::string calculateResultOld(hand *players, int numPlayers);
    static std::string calculateResult(hand *players, int numPlayers);
    void print();  

private:
    int* cards;
    int numCards;
    int countCardsDrawn;

    void riffleShuffle();
    void playHand(int numPlayers);  
};