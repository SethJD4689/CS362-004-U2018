/*******************************************************************************
** Assignment: CS362 - Assignment 4
** Filename: randomtestcard2.c
** Author: Seth Dovgan
** Date: 29 JUL 2018
**
** Description: Tests the Council room card with random testing.
*******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "tester.h"

#define CARD "Council Room"
#define TYPE "Card"
#define NUM_OF_TESTS 100000
#define CARDS_DRAWN 4 	    // Number of cards drawn by the Council Room card
#define CARDS_PLAYED 1 	    // Council Room card played
#define BUY_GAIN 1          // Buys gained playing Council Room card
#define OTHER_CARDS_DRAWN 1 // Cards drawn by other players
#define EMPTY_DECK 0

/*******************************************************************************
**  Function: main
**  Description: Tests the Council Room card effect on the state of the game
**  with random testing.
*******************************************************************************/
int main() {

    srand(time(NULL));

    struct gameState game, test;

    int tests = 0;
    int passed = 0;
    int handPos;
    long randomTests = NUM_OF_TESTS;

    // Print Test Header
    printTestHeader(CARD, TYPE);

    while(randomTests > 0){

        int *actionCards = generateRandomGameState(&game, council_room, &handPos);
        int selectedPlayer = game.whoseTurn;

        // Copy a test instance
        memcpy(&test, &game, sizeof(struct gameState));

        // Call Council Room function
        councilRoomCardEffect(&test, selectedPlayer, handPos);

        // Check the effects the Council Room card has on the game state for player.
        printf("\n* Testing Player %d Playing %s card...\n\n", selectedPlayer, CARD);

        printf("Council Room Card Hand Position: %d\n", handPos);

        int deckCount = game.deckCount[selectedPlayer];
        int discardCount = game.discardCount[selectedPlayer];

        // Calculate expected outcomes for various deck and discard counts
        // Deck has less than the amount of cards to draw
        if(deckCount < CARDS_DRAWN && discardCount >= CARDS_DRAWN){

            testCurrentPlayerState(&game, &test, selectedPlayer, (CARDS_DRAWN - CARDS_PLAYED),
                                   (discardCount - CARDS_DRAWN), CARDS_PLAYED,
                                   (-discardCount), NO_CHANGE, BUY_GAIN,
                                   NO_CHANGE, NO_CHANGE, council_room, &passed, &tests);

        // Deck and discard have less than the amount of cards to draw
        // but combined they both do
        } else if(deckCount < CARDS_DRAWN && discardCount < CARDS_DRAWN
                  && (deckCount + discardCount) >= CARDS_DRAWN){

            testCurrentPlayerState(&game, &test, selectedPlayer, (CARDS_DRAWN - CARDS_PLAYED),
                                   (discardCount - CARDS_DRAWN), CARDS_PLAYED,
                                   (-discardCount), NO_CHANGE, BUY_GAIN,
                                   NO_CHANGE, NO_CHANGE, council_room, &passed, &tests);

        // Deck and discard have less than the amount of cards to draw
        // and combined they still do not have enough
        } else if(deckCount < CARDS_DRAWN && discardCount < CARDS_DRAWN
                  && (deckCount + discardCount) < CARDS_DRAWN){

            testCurrentPlayerState(&game, &test, selectedPlayer, ((deckCount + discardCount) - CARDS_PLAYED),
                                   (-deckCount), CARDS_PLAYED, (-discardCount),
                                   NO_CHANGE, BUY_GAIN, NO_CHANGE, NO_CHANGE,
                                   council_room, &passed, &tests);

        } else { // Deck has enough cards to draw.

            testCurrentPlayerState(&game, &test, selectedPlayer, (CARDS_DRAWN - CARDS_PLAYED),
                                   (-CARDS_DRAWN), CARDS_PLAYED, NO_CHANGE,
                                   NO_CHANGE, BUY_GAIN, NO_CHANGE, NO_CHANGE,
                                   council_room, &passed, &tests);
        }

        // Check if the card was actually played
        testCardPlayed(&game, &test, selectedPlayer, handPos, &passed, &tests);

        // Check the effects the Council Room card has on the game state for a non current player
        for(int i = 0; i < test.numPlayers; i++){

            if(i != selectedPlayer){

                printf("\n* Testing Player %d...\n\n", i);

                deckCount = game.deckCount[i];
                discardCount = game.discardCount[i];

                // Calculate expected outcomes for various deck and discard counts
                // Deck has less than the amount of cards to draw
                if(deckCount < OTHER_CARDS_DRAWN && discardCount >= OTHER_CARDS_DRAWN){

                    testOtherPlayerState(&game, &test, i, OTHER_CARDS_DRAWN,
                                         (discardCount - OTHER_CARDS_DRAWN), (-discardCount), NO_CHANGE,
                                         &passed, &tests);

                // Deck and discard have less than the amount of cards to draw
                // but combined they both do
                } else if(deckCount < OTHER_CARDS_DRAWN && discardCount < OTHER_CARDS_DRAWN
                          && (deckCount + discardCount) >= OTHER_CARDS_DRAWN){

                    testOtherPlayerState(&game, &test, i, OTHER_CARDS_DRAWN,
                                         (discardCount - OTHER_CARDS_DRAWN), (-discardCount), NO_CHANGE,
                                         &passed, &tests);

                // Deck and discard have less than the amount of cards to draw
                // and combined they still do not have enough
                } else if(deckCount < OTHER_CARDS_DRAWN && discardCount < OTHER_CARDS_DRAWN
                          && (deckCount + discardCount) < OTHER_CARDS_DRAWN){

                    testOtherPlayerState(&game, &test, i, NO_CHANGE,
                                         (-deckCount), (-discardCount), NO_CHANGE,
                                         &passed, &tests);

                } else { // Deck has enough cards to draw.

                    testOtherPlayerState(&game, &test, i, OTHER_CARDS_DRAWN,
                                         (- OTHER_CARDS_DRAWN), NO_CHANGE, NO_CHANGE,
                                         &passed, &tests);
                }
            }
        }

        // Verify no victory card piles were effected.
        printf("\n* Testing Victory Card Piles...\n\n");
        testVictoryCardPilesNoChange(&game, &test, &passed, &tests);

        // Verify no treasure card piles were affected
        printf("\n* Testing Treasure Card Piles...\n\n");
        testTreasureCardPilesNoChange(&game, &test, &passed, &tests);

        // Verify no kingdom card piles were affected
        printf("\n* Testing Kingdom Card Piles...\n\n");
        testKingdomCardPilesNoChange(&game, &test, actionCards, &passed, &tests);

        randomTests--;
    }

    // Print Test Summary
    printTestSummary(passed, tests);
}



