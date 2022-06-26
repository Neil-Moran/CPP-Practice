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
    int partition(int array[], int low, int high);
    void quickSort(int array[], int low, int high);
    bool containsCard(int value);
    int containsOnePair();
    void drawCards(deck *deck);
    void print();

    friend class deck;
};