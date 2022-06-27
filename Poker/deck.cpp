#pragma once

#include "card.h"
#include "deck.h"
#include "hand.h"
#include "RNG.h"
#include <stdio.h>
#include <string>

deck::deck()
{   
    countCardsDrawn = 0;

    for(int i=0; i<52; ++i)
    {
        cards[i] = i+1;
    }
}

deck::~deck()
{
}

void deck::riffleShuffle()
{
    int cards_copy[52];
    memcpy(cards_copy, cards, sizeof(cards));

    RNG rng;

    // simulated riffle shuffle: split the deck in half, then 
    // randomly add cards back into the deck from both halves
    int i=0, l=0, r=26;

    while(l<26 && r<52)
    {
        if(rng.flipCoin()) // flip a coin; if tails we take a card from the left packet...
        {
            cards[i] = cards_copy[l];
            ++l;
        }

        else // ...if heads we take a card from the right packet
        {
            cards[i] = cards_copy[r];
            ++r;
        }

        ++i;
    }

    // we've exhausted one of the packets, finish off the cards from the remaining packet
    if(l<26)
    {
        for(; l<26; ++l, ++i)
        {
            cards[i] = cards_copy[l];
        }
    }

    if(r<52)
    {
        for(; r<52; ++r, ++i)
        {
            cards[i] = cards_copy[r];
        }
    }
}

void deck::shuffle()
{
    // do seven riffle shuffles https://math.hmc.edu/funfacts/seven-shuffles/
    for(int i=0; i<7; ++i)
    {
        riffleShuffle();
    }
    countCardsDrawn = 0;
}

void deck::playGame(int numPlayers, int numHands)
{
    for(int i=0; i<numHands; ++i)
    {
        shuffle();
        print();
        printf("\n");
        playHand(numPlayers);
        printf("\n");
    }
}

void deck::playHand(int numPlayers)
{
    if(numPlayers > 10) numPlayers = 10;

    hand *players = new hand[numPlayers];

    for(int i=0; i<numPlayers; ++i)
    {
        players[i].drawCards(this);
        printf("Player %i: ", i+1);
        players[i].print();
    }
    // print hand result
    {
        int winners = 1; // every i-th bit indicates whether player i is currently considered a winner
        int numWinners = 1;
        int winnerID = 0;
        quickSort(players[0].cards, 0, 4); // sort in case we need to tie break

        for(int i=1; i<numPlayers; ++i)
        {
            if(players[i].result < players[winnerID].result) // new winner
            {
                winners = 1 << i;
                winnerID = i;
                numWinners = 1;
                quickSort(players[i].cards, 0, 4); // sort in case we need to tie break
            }
            else if(players[i].result == players[winnerID].result) // possible tie
            {
                // attempt to tie break 
                int newWinnerID = -1;
                quickSort(players[i].cards, 0, 4);

                int highCardPlayerA, highCardPlayerB;

                switch(players[winnerID].result) // this logic is audacious but correct ;)
                {
                case ROYAL_FLUSH: // identical hands, tie
                    break;                     
                case STRAIGHT_FLUSH: //same as straight, fall through
                case STRAIGHT: // just compare the highest card
                    highCardPlayerA = players[winnerID].cards[4]%13;
                    if(highCardPlayerA < 2) highCardPlayerA += 13;
                    if(highCardPlayerA == 14 && players[winnerID].cards[3]%13 == 5) highCardPlayerA = 5; // if the straight is A 2 3 4 5, the high card is 5

                    highCardPlayerB = players[i].cards[4]%13;
                    if(highCardPlayerB < 2) highCardPlayerB += 13;
                    if(highCardPlayerB == 14 && players[i].cards[3]%13 == 5) highCardPlayerB = 5; // if the straight is A 2 3 4 5, the high card is 5

                    if(highCardPlayerA > highCardPlayerB)
                        newWinnerID = winnerID;
                    else if(highCardPlayerA < highCardPlayerB)
                        newWinnerID = i;
                    break;
                case FULL_HOUSE: // first compare the three of a kind...
                    highCardPlayerA = players[winnerID].getThreeOfAKind();
                    highCardPlayerB = players[i].getThreeOfAKind();

                    if(highCardPlayerA > highCardPlayerB)
                    {
                        newWinnerID = winnerID;
                        break;
                    }
                    else if(highCardPlayerA < highCardPlayerB)
                    {
                        newWinnerID = i;
                        break;
                    }
                    // ... if still a tie then fall through and compare the pair (it could be a high pair or a low pair)
                case FOUR_OF_A_KIND: //FOAK is also a pair, so fall through and compare that!
                case THREE_OF_A_KIND: //TOAK is also a pair, so fall through and compare that!
                case TWO_PAIR: // first compare high pair...
                    highCardPlayerA = players[winnerID].getHighPair();
                    highCardPlayerB = players[i].getHighPair();

                    if(highCardPlayerA > highCardPlayerB)
                    {
                        newWinnerID = winnerID;
                        break;
                    }
                    else if(highCardPlayerA < highCardPlayerB)
                    {
                        newWinnerID = i;
                        break;
                    }
                    // ...if still a tie then fall through and compare low pair
                case ONE_PAIR:
                    highCardPlayerA = players[winnerID].getLowPair();
                    highCardPlayerB = players[i].getLowPair();

                    if(highCardPlayerA > highCardPlayerB)
                    {
                        newWinnerID = winnerID;
                        break;
                    }
                    else if(highCardPlayerA < highCardPlayerB)
                    {
                        newWinnerID = i;
                        break;
                    }
                            // if still a tie fall through and compare highest card(s)
                case FLUSH: // fall through and compare highest card(s)
                case HIGH_CARD:
                    for(int j=4; j>=0; --j)
                    {
                        highCardPlayerA = players[winnerID].cards[j]%13;
                        if(highCardPlayerA < 2) highCardPlayerA += 13;

                        highCardPlayerB = players[i].cards[j]%13;
                        if(highCardPlayerB < 2) highCardPlayerB += 13;

                        if(highCardPlayerA > highCardPlayerB)
                        {
                            newWinnerID = winnerID;
                            break;
                        }
                        else if(highCardPlayerA < highCardPlayerB)
                        {
                            newWinnerID = i;
                            break;
                        }
                    }
                    break;  
                }
                if(newWinnerID != -1) // not a tie
                {
                    if(newWinnerID != winnerID) // new winner
                    {
                        winners = 1 << newWinnerID;
                        winnerID = newWinnerID;
                        numWinners = 1;
                    }
                }
                else // tie
                {
                    winners |= 1 << i;
                    ++numWinners;
                }
            }
        }

        if(numWinners == 1) 
            printf("Player %i Wins\n", winnerID+1);
        
        else 
        {
            std::string output = "Tie:";
            for(int i=0; i<numPlayers, numWinners > 0; ++i)
            {
                if(winners & 1<<i)
                {
                    output.append(" Player ");
                    output.append(std::to_string(i+1));
                    --numWinners;
                    if(numWinners > 0) output.append(" |");
                }
            }
            printf("%s\n", output.c_str());
        }
    }

    delete[] players;
}

void deck::print()
{
    std::string result;
    for(int i=0; i<52; ++i)
    {
        result.append(getCardValue(cards[i]).append(" "));
        if((i+1)%13 == 0) result.append("\n");
    }
    printf("%s", result.c_str());
}