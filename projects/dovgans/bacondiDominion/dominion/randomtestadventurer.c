/*******************************************************************************
** Assignment: CS362 - Assignment 4
** Filename: randomtestadventurer.c
** Author: Seth Dovgan
** Date: 23 JUL 2018
**
** Description: Tests the Adventurer card with random testing.
*******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "tester.h"

#define CARD "Adventurer"
#define TYPE "Card"
#define CARDS_DRAWN 2 	// Number of cards drawn by the Adventurer card
#define CARDS_PLAYED 1 	// Adventurer card played

/*******************************************************************************
**  Function: getNumberOfTreasureCardsInDeck
**  Description: Returns the number of treasure cards in a deck
**
**  param:	int deck[][MAX_DECK] - deck to search for the treasure cards in
**	param:  const int deckCount[] - deck size
**	param:	int player - player's the deck belongs to
**
**  return:	total number of cards assigned to all the players
*******************************************************************************/
int getNumberOfTreasureCardsInDeck(int deck[][MAX_DECK], const int deckCount[],
                                   int player){

    int treasureCardCount = 0;

    // Search the deck for treasure cards
    for(int i = 0; i < deckCount[player]; i++){

        if(deck[player][i] == copper || deck[player][i] == silver
           || deck[player][i] == gold){

            treasureCardCount++;
        }
    }

    return treasureCardCount;
}

/*******************************************************************************
**  Function: testDrawnTreasureCards
**  Description: Tests if treasure cards are drawn
*******************************************************************************/
void testDrawnTreasureCards(struct gameState test, int player, int *passed,
                            int *tests, int cardsDrawn){

    int count = cardsDrawn;

    while(count > 0){

        if(test.handCount[player] >= count){

            int cardPosition = test.handCount[player] - count;

            char title[100];
            char name[MAX_STRING_LENGTH];

	        cardNumToName(test.hand[player][cardPosition], name);
	        sprintf(title, "Current Player %d - %s Card Drawn", player, name);

            assertTrue(TRUE, (test.hand[player][cardPosition] == copper
                              || test.hand[player][cardPosition] == silver
                              || test.hand[player][cardPosition] == gold),
                       title, passed, tests);

        } else {

        	char title[100];
	        sprintf(title, "Current Player %d - No Treasure Card Drawn", player);
            assertTrue(FALSE, TRUE, title, passed, tests);
        }

        count--;
    }
}


/*******************************************************************************
**  Function: main
**  Description: Tests the Adventurer card effect on the state of the game with
**  random testing.
*******************************************************************************/
int main() {

    srand(time(NULL));

    struct gameState game, test;

    int tests = 0;
    int passed = 0;
	int testCase;
	int passedCaseTests;
    int handPos;
    long randomTests = NUM_OF_TESTS;

    // Print Test Header
    printTestHeader(CARD, TYPE);

    while(randomTests > 0){

	    testCase = tests;
	    passedCaseTests = passed;

        int *actionCards = generateRandomGameState(&game, adventurer, &handPos);
        int selectedPlayer = game.whoseTurn;
	    int deckCount = getNumberOfTreasureCardsInDeck(game.deck, game.deckCount,
	    		selectedPlayer);
	    int discardCount = getNumberOfTreasureCardsInDeck(game.discard, game.discardCount,
	    		selectedPlayer);

	    // Copy a test instance
	    memcpy(&test, &game, sizeof(struct gameState));

        // Call Adventurer function
        adventurerCardEffect(&test, selectedPlayer);

        // Calculate expected outcomes for various deck and discard counts
        // Deck has less than the amount of cards treasure cards to draw
        if(deckCount < CARDS_DRAWN && discardCount >= CARDS_DRAWN){

	        testCurrentPlayerStateModified(&game, &test, selectedPlayer,
	                                       (CARDS_DRAWN - CARDS_PLAYED),
	                                       CARDS_PLAYED, NO_CHANGE, NO_CHANGE,
	                                       NO_CHANGE, NO_CHANGE, &passed, &tests);

            testDrawnTreasureCards(test, selectedPlayer, &passed, &tests,
                                   CARDS_DRAWN);

	    // Deck and discard have less than the amount of treasure cards to draw
	    // but combined they both do
        } else if(deckCount < CARDS_DRAWN && discardCount < CARDS_DRAWN
                  && (deckCount + discardCount) >= CARDS_DRAWN){

	        testCurrentPlayerStateModified(&game, &test, selectedPlayer,
	                                       (CARDS_DRAWN - CARDS_PLAYED),
	                                       CARDS_PLAYED, NO_CHANGE, NO_CHANGE,
	                                       NO_CHANGE, NO_CHANGE, &passed, &tests);

            testDrawnTreasureCards(test, selectedPlayer, &passed, &tests,
                                   CARDS_DRAWN);

        // Deck and discard have less than the amount of treasure cards to draw
	    // and combined they still do not have enough
        } else if(deckCount < CARDS_DRAWN && discardCount < CARDS_DRAWN
                  && (deckCount + discardCount) < CARDS_DRAWN){

	        testCurrentPlayerStateModified(&game, &test, selectedPlayer,
	                                       (deckCount + discardCount - CARDS_PLAYED),
	                                       CARDS_PLAYED, NO_CHANGE, NO_CHANGE,
	                                       NO_CHANGE, NO_CHANGE, &passed, &tests);

            testDrawnTreasureCards(test, selectedPlayer, &passed, &tests,
                                   (deckCount + discardCount));

        } else { // Deck has enough treasure cards to draw.

            testCurrentPlayerStateModified(&game, &test, selectedPlayer,
                                           CARDS_PLAYED, NO_CHANGE, NO_CHANGE,
                                           NO_CHANGE, NO_CHANGE, NO_CHANGE,
                                           &passed, &tests);

            testDrawnTreasureCards(test, selectedPlayer, &passed, &tests,
                                   CARDS_DRAWN);
        }

        // Check if the card was actually played
        testCardPlayed(&game, &test, selectedPlayer, handPos, &passed, &tests);

        // Check the effects the Adventurer card has on the game state for a non
	    // current player
        for(int i = 0; i < test.numPlayers; i++){

            if(i != selectedPlayer){

                testOtherPlayerNoStateChange(&game, &test, i, &passed, &tests);
            }
        }

        // Verify no victory card piles were effected.
        testVictoryCardPilesNoChange(&game, &test, &passed, &tests);

        // Verify no treasure card piles were affected
        testTreasureCardPilesNoChange(&game, &test, &passed, &tests);

        // Verify no kingdom card piles were affected
        testKingdomCardPilesNoChange(&game, &test, actionCards, &passed, &tests);

	    if((testCase - passedCaseTests) != (tests - passed)){

		    printf("\n* Preconditions for Player %d Playing %s card...\n\n",
		           selectedPlayer, CARD);
		    printf("Adventurer Card Hand Position: %d\n", handPos);
		    printf("Hand Count: %d\n", game.handCount[selectedPlayer]);
		    printf("Deck Count: %d\n", game.deckCount[selectedPlayer]);
		    printf("Discard Count: %d\n", game.discardCount[selectedPlayer]);
		    printf("Treasurer Cards in Deck: %d\n", deckCount);
		    printf("Treasurer Cards in Discard: %d\n", discardCount);
		    printf("\n#--------------------------------------------------------"
			 "----------------------#\n\n");
	    }

        randomTests--;
    }

    // Print Test Summary
    printTestSummary(passed, tests);
}


