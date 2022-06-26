#pragma once
#include <string>

class deck
{
private:
    int cards[52];
    int countCardsDrawn;

    std::string getCardValue(int index);

public:
    deck();
    ~deck();
    void print();
};


