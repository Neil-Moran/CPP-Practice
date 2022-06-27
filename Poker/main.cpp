#include "deck.h"
#include <stdio.h>

int main()
{
    deck deck;
    deck.print();
    printf("\n");
    deck.playGame(4, 10);

    return 0;
}