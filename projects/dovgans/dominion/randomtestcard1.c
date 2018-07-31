/*******************************************************************************
** Assignment: CS362 - Assignment 4
** Filename: randomtestcard1.c
** Author: Seth Dovgan
** Date: 23 JUL 2018
**
** Description: Tests the Smithy card with random testing.
*******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "tester.h"

#define CARD "Smithy"
#define TYPE "Card"
#define CARDS_DRAWN 3 	// Number of cards drawn by the Smithy card
#define CARDS_PLAYED 1 	// Smithy card played

/*******************************************************************************
**  Function: main
**  Description: Tests the Smithy card effect on the state of the game with
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

		int *actionCards = generateRandomGameState(&game, smithy, &handPos);
		int selectedPlayer = game.whoseTurn;

		// Copy a test instance
		memcpy(&test, &game, sizeof(struct gameState));

		// Call smithy function
		smithyCardEffect(&test, selectedPlayer, handPos);

		int deckCount = game.deckCount[selectedPlayer];
		int discardCount = game.discardCount[selectedPlayer];

		// Calculate expected outcomes for various deck and discard counts
		// Deck has less than the amount of cards to draw
		if(deckCount < CARDS_DRAWN && discardCount >= CARDS_DRAWN){

			testCurrentPlayerState(&game, &test, selectedPlayer, (CARDS_DRAWN - CARDS_PLAYED),
								   (discardCount - CARDS_DRAWN), CARDS_PLAYED,
								   (-discardCount), NO_CHANGE, NO_CHANGE,
								   NO_CHANGE, NO_CHANGE, &passed, &tests);

		// Deck and discard have less than the amount of cards to draw
		// but combined they both do
		} else if(deckCount < CARDS_DRAWN && discardCount < CARDS_DRAWN
		   && (deckCount + discardCount) >= CARDS_DRAWN){

			testCurrentPlayerState(&game, &test, selectedPlayer, (CARDS_DRAWN - CARDS_PLAYED),
								   (discardCount - CARDS_DRAWN), CARDS_PLAYED,
								   (-discardCount), NO_CHANGE, NO_CHANGE,
								   NO_CHANGE, NO_CHANGE, &passed, &tests);

		// Deck and discard have less than the amount of cards to draw
		// and combined they still do not have enough
		} else if(deckCount < CARDS_DRAWN && discardCount < CARDS_DRAWN
				  && (deckCount + discardCount) < CARDS_DRAWN){

			testCurrentPlayerState(&game, &test, selectedPlayer, ((deckCount + discardCount) - CARDS_PLAYED),
								   (-deckCount), CARDS_PLAYED, (-discardCount),
								   NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE,
								   &passed, &tests);

		} else { // Deck has enough cards to draw.

			testCurrentPlayerState(&game, &test, selectedPlayer, (CARDS_DRAWN - CARDS_PLAYED),
								   (-CARDS_DRAWN), CARDS_PLAYED, NO_CHANGE,
								   NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE,
								   &passed, &tests);
		}

		// Check if the card was actually played
		testCardPlayed(&game, &test, selectedPlayer, handPos, &passed, &tests);

		// Check the effects the Smithy card has on the game state for a non current player
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

		randomTests--;

		if((testCase - passedCaseTests) != (tests - passed)){

			printf("\n* Preconditions for Player %d Playing %s card...\n\n",
			       selectedPlayer, CARD);
			printf("Smithy Card Hand Position: %d\n", handPos);
			printf("Hand Count: %d\n", game.handCount[selectedPlayer]);
			printf("Deck Count: %d\n", game.deckCount[selectedPlayer]);
			printf("Discard Count: %d\n", game.discardCount[selectedPlayer]);
			printf("\n#--------------------------------------------------------"
		  "----------------------#\n\n");
		}
	}

	// Print Test Summary
	printTestSummary(passed, tests);
}

