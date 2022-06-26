#include "deck.h"
#include <stdio.h>

int main()
{
    deck deck;
    deck.print();
    printf("\n");

    deck.shuffle();
    deck.print();
    printf("\n");

    deck.playHand(1);

    return 0;
}