#include "deck.h"
#include <stdio.h>

int main()
{
    {
    deck deck;
    deck.print();
    printf("\n");
    deck.playGame(4, 4);
    printf("\n");
    }

    {
    deck deck(3);
    deck.print();
    printf("\n");
    deck.playGame(32, 1);
    }

    return 0;
}