#include "deck.h"
#include <stdio.h>

int main()
{
    deck deck;
    deck.print();
    printf("\n");
    deck.playGame(10, 10);    

    return 0;
}