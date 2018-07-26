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
#define NUM_OF_TESTS 10
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
	int randomTests = 10;

	// Print Test Header
	printTestHeader(CARD, TYPE);

	while(randomTests > 0){

		generateRandomGameState(game);

		int selectedPlayer = game.whoseTurn;
		int handPos = rand() % game.handCount[selectedPlayer];

		// Place Smithy card in hand
		game.hand[selectedPlayer][handPos] = smithy;

		// Copy a test instance
		memcpy(&test, &game, sizeof(struct gameState));

		// Call smithy function
		smithyCardEffect(&test, selectedPlayer, handPos);

		// Check the effects the Smithy card has on the game state for player.
		printf("\n* Testing Player %d Playing %s card...\n\n", selectedPlayer, CARD);

		testCurrentPlayerState(&game, &test, selectedPlayer, (CARDS_DRAWN - CARDS_PLAYED),
							   (-CARDS_DRAWN), CARDS_PLAYED, NO_CHANGE, NO_CHANGE,
							   NO_CHANGE, NO_CHANGE, NO_CHANGE, smithy, &passed, &tests);

		// Check if the card was actually played
		testCardPlayed(&game, &test, selectedPlayer, handPos, &passed, &tests);

		for(int i = 0; i < test.numPlayers; i++){

			if(i != selectedPlayer){

				// Check the effects the Smithy card has on the game state for a non current player
				printf("\n* Testing Player %d...\n\n", i);
				testOtherPlayerNoStateChange(&game, &test, i, &passed, &tests);
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
		//testKingdomCardPilesNoChange(&game, &test, actionCards, &passed, &tests);

		randomTests--;
	}

	// Print Test Summary
	printTestSummary(passed, tests);
}

