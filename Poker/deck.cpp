#pragma once

#include "card.h"
#include "deck.h"
#include "hand.h"
#include "RNG.h"
#include "timing.h"
#include <stdio.h>
#include <string>

deck::deck(int numPacks)
{   
    numCards = numPacks*52;
    countCardsDrawn = 0;
    cards = new int[numCards];

    for(int i=0; i<numCards; ++i)
    {
        cards[i] = i%52+1;
    }
}

deck::~deck()
{
    delete[] cards;
}

void deck::riffleShuffle()
{
    int *cards_copy = new int[numCards];
    memcpy(cards_copy, cards, numCards*sizeof(int));

    RNG rng;

    // simulated riffle shuffle: split the deck in half, then 
    // randomly add cards back into the deck from both halves
    int i=0, l=0, r=numCards/2;

    while(l<numCards/2 && r<numCards)
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
    if(l<numCards/2)
    {
        while(l<numCards/2)
        {
            cards[i++] = cards_copy[l++];
        }
    }

    if(r<numCards)
    {
        while(r<numCards)
        {
            cards[i++] = cards_copy[r++];
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
    Timer timer;
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
    if(numPlayers > numCards/5) numPlayers = numCards/5; // max numPlayers is numCards/5, as everyone needs 5 cards

    hand *players = new hand[numPlayers];

    // deal and print hands
    for(int i=0; i<numPlayers; ++i)
    {
        players[i].drawCards(this);
        printf("Player %i: ", i+1);
        players[i].print();
    }

    // print result
    // std::string result = calculateResultOld(players, numPlayers); 
    std::string result = calculateResult(players, numPlayers); 
    printf("%s\n", result.c_str());

    delete[] players;
}

// keeping this for posterity, cool logic but scoring    
// the hands seems a much better solution
// PERF:
// 100,000 hands of 4 players in 63.83209910 seconds
// ""            ""               1.20923790 seconds without printf
// 1,000,000 hands of 10 players in 14.06920920 seconds without printf
std::string deck::calculateResultOld(hand *players, int numPlayers)
{
    std::string result;

    int winners = 1; // every i-th bit indicates whether player i is currently considered a winner
    int numWinners = 1;
    int winnerID = 0;
    
    handResult bestResult = players[0].result;

    // first find the first instance of the best hand result, ignoring ties
    for(int i=0; i<numPlayers; ++i)
    {
        if(players[i].result > bestResult)
        {
            winners = 1 << i;
            winnerID = i;
            bestResult = players[i].result;
        }
    }

    quickSort(players[winnerID].cards, 0, 4); // sort in case we need to tie break

        // then find the player(s) with the best hand
        for(int i=winnerID+1; i<numPlayers; ++i)
        {
            if(players[i].result > bestResult) // new winner
            {
                winners = 1 << i;
                winnerID = i;
                numWinners = 1;
                quickSort(players[i].cards, 0, 4); // sort in case we need to tie break
            }
            else if(players[i].result == bestResult) // possible tie
            {
                // attempt to tie break 
                int newWinnerID = -1;
                quickSort(players[i].cards, 0, 4);

                int highCardPlayerA, highCardPlayerB;

                switch(bestResult) // this logic is audacious but correct ;)
                {
                case ROYAL_FLUSH: // whichever hand is composed of the highest ranking suit wins
                    // the card IDs are ordered so that S > H > D > C!
                    highCardPlayerA = players[winnerID].cards[4];
                    highCardPlayerB = players[i].cards[4];

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
        {
            result.append("Player ").append(std::to_string(winnerID+1)).append(" Wins");
        }
        
        else 
        {
            result = "Tie:";
            for(int i=winnerID; i<numPlayers && numWinners>0; ++i)
            {
                if(winners & 1<<i)
                {
                    result.append(" Player ").append(std::to_string(i+1));
                    --numWinners;
                    if(numWinners > 0) result.append(" |");
                }
            }
        }

        return result;
}

// PERF:
// 100,000 hands of 4 players in 63.39656060 seconds
// ""            ""               1.21232670 seconds without printf
// 1,000,000 hands of 10 players in 13.66677420 seconds without printf
std::string deck::calculateResult(hand *players, int numPlayers)
{
    std::string result;

    int winnerID = 0;   // ID of the winner, initialise to the first player
    int numWinners = 1; // in the very unlikely event of a tie

    for(int i=1; i<numPlayers; ++i)
    {
        if(players[i].score > players[winnerID].score)
        {
            winnerID = i;
            numWinners = 1;
        }
        else if(players[i].score == players[winnerID].score)
        {
            ++numWinners;
        }
    }

    if(numWinners == 1) 
    {
        result.append("Player ").append(std::to_string(winnerID+1)).append(" Wins");
    }
    else 
    {
        result = "Tie:";
        for(int i=winnerID; i<numPlayers && numWinners>0; ++i)
        {
            if(players[i].score == players[winnerID].score)
            {
                result.append(" Player ").append(std::to_string(i+1));
                --numWinners;
                if(numWinners > 0) result.append(" |");
            }
        }
    }

    return result;
}

void deck::print()
{
    std::string result;
    for(int i=0; i<numCards; ++i)
    {
        result.append(getCardValue(cards[i]).append(" "));
        if((i+1)%13 == 0) result.append("\n");
    }
    printf("%s", result.c_str());
}