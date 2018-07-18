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

#define TEST_CARD "Smithy"
#define TEST_TYPE "Card"
#define NUM_PLAYERS 2
#define CURRENT_PLAYER 0
#define OTHER_PLAYER 1
#define NUM_K_CARDS 10

/*******************************************************************************
**  Function: main
**  Description: Tests the Smithy card effect on the state of the game.
*******************************************************************************/
int main() {

	struct gameState game, test;

	const int SEED = 100;
	int actionCards[NUM_K_CARDS] = {smithy, adventurer, salvager, steward, baron,
									village, minion, feast, embargo, outpost};

	const int CHOICE = 0;
	const int HAND_POS = 0;
	const int CARDS_DRAWN = 3;
	const int CARDS_PLAYED = 1;
	const int NO_CHANGE = 0;

    int bonus = 0;
	int tests = 0;
	int passed = 0;

	// Initialize the game to test
	initializeGame(NUM_PLAYERS, actionCards, SEED, &game);

	// Copy test instance
	memcpy(&test, &game, sizeof(struct gameState));

	cardEffect(smithy, CHOICE, CHOICE, CHOICE, &test, HAND_POS, &bonus);

	printTestHeader(TEST_TYPE, TEST_CARD);

	// Check the effects the Smithy card has on the game state for the current player.
	printf("\n* Testing Current Player Playing %s card...\n\n", TEST_CARD);
	testCurrentPlayerState(&game, &test, CURRENT_PLAYER,
	                       (CARDS_DRAWN - CARDS_PLAYED),
	                       (-CARDS_DRAWN), CARDS_PLAYED, NO_CHANGE, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, NO_CHANGE, &passed, &tests);

	// Check the effects the Smithy card has on the game state for the other player.
	printf("\n* Testing Other Player...\n\n");
	testOtherPlayerState(&game, &test, OTHER_PLAYER, NO_CHANGE, NO_CHANGE,
	                     NO_CHANGE, NO_CHANGE, &passed, &tests);

	// Verify no victory card piles were effected.
    printf("\n* Testing Victory Card Piles...\n\n");
    testVictoryCardPiles(&game, &test, NO_CHANGE, NO_CHANGE, NO_CHANGE,
                         &passed, &tests);

    // Verify no treasure card piles were affected
    printf("\n* Testing Treasure Card Piles...\n\n");
	testTreasureCardPiles(&game, &test, NO_CHANGE, NO_CHANGE, NO_CHANGE,
	                      &passed, &tests);

	// Verify no kingdom card piles were affected
    printf("\n* Testing Kingdom Card Piles...\n\n");

    int cardChanges[NUM_K_CARDS];

	for(int i = 0; i < NUM_K_CARDS; i++){
		cardChanges[i] = NO_CHANGE;
	}

	testKingdomCardPiles(&game, &test, actionCards, cardChanges, &passed, &tests);

	// Print Summary and Footer
	printTestSummary(passed, tests);
}


