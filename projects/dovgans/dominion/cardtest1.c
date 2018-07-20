/*******************************************************************************
** Assignment: CS362 - Assignment 3
** Filename: cardtest1.c
** Author: Seth Dovgan
** Date: 10 July 2017
**
** Description: Tests the Smithy Card Effect.
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "tester.h"
#include <string.h>
#include <stdio.h>

#define CARD "Smithy"
#define TYPE "Card"

/*******************************************************************************
**  Function: main
**  Description: Tests the Smithy card effect on the state of the game.
*******************************************************************************/
int main() {

	struct gameState game, test;

	const int SEED = 100;
	int actionCards[NUM_K_CARDS] = {smithy, adventurer, salvager, steward, baron,
									village, minion, feast, embargo, outpost};

	const int CHOICE = 0;       // Action choice - not used
	const int HAND_POS = 0;     // Position the Smithy card is in the players hand
	const int CARDS_DRAWN = 3;  // Number of cards drawn by the Smithy cards
	const int CARDS_PLAYED = 1; // Smithy card played

    int bonus = 0;
	int tests = 0;
	int passed = 0;

	// Initialize the game instance for the test
	initializeGame(NUM_PLAYERS, actionCards, SEED, &game);

	// Copy a test instance
	memcpy(&test, &game, sizeof(struct gameState));

	// Call
	cardEffect(smithy, CHOICE, CHOICE, CHOICE, &test, HAND_POS, &bonus);

	// Print Test Header
	printTestHeader(CARD, TYPE);

	// Check the effects the Smithy card has on the game state for the current player.
	printf("\n* Testing Current Player Playing %s card...\n\n", CARD);
	testCurrentPlayerState(&game, &test, CURRENT_PLAYER, (CARDS_DRAWN - CARDS_PLAYED),
	                       (-CARDS_DRAWN), CARDS_PLAYED, NO_CHANGE, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, NO_CHANGE, &passed, &tests);

	// Check the effects the Smithy card has on the game state for the other player.
	printf("\n* Testing Other Player...\n\n");
	testOtherPlayerNoStateChange(&game, &test, OTHER_PLAYER, &passed, &tests);

	// Verify no victory card piles were effected.
    printf("\n* Testing Victory Card Piles...\n\n");
	testVictoryCardPilesNoChange(&game, &test, &passed, &tests);

    // Verify no treasure card piles were affected
    printf("\n* Testing Treasure Card Piles...\n\n");
	testTreasureCardPilesNoChange(&game, &test, &passed, &tests);

	// Verify no kingdom card piles were affected
    printf("\n* Testing Kingdom Card Piles...\n\n");
	testKingdomCardPilesNoChange(&game, &test, actionCards, &passed, &tests);

	// Print Test Summary
	printTestSummary(passed, tests);
}


