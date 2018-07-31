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
#include "interface.h"
#include "tester.h"
#include <string.h>
#include <stdio.h>

#define CARD "Smithy"
#define TYPE "Card"
#define HAND_POS 4 		// Position the Smithy card is in the players hand
#define CARDS_DRAWN 3 	// Number of cards drawn by the Smithy card
#define CARDS_PLAYED 1 	// Smithy card played
#define EMPTY_DECK 0

/*******************************************************************************
**  Function: main
**  Description: Tests the Smithy card effect on the state of the game.
*******************************************************************************/
int main() {

	struct gameState game, test;

	int actionCards[NUM_K_CARDS] = {smithy, adventurer, salvager, steward, baron,
									village, minion, feast, embargo, outpost};

	int tests = 0;
	int passed = 0;

	// Initialize the game instance for the test
	initializeGame(NUM_PLAYERS, actionCards, SEED, &game);

	// Place Smithy card in hand
	game.hand[CURRENT_PLAYER][HAND_POS] = smithy;

	// Copy a test instance
	memcpy(&test, &game, sizeof(struct gameState));

	// Call smithy function
	smithyCardEffect(&test, CURRENT_PLAYER, HAND_POS);

	// Print Test Header
	printTestHeader(CARD, TYPE);

	// Check the effects the Smithy card has on the game state for the current player.
	printf("\n* Testing Current Player Playing %s card...\n\n", CARD);

	testCurrentPlayerState(&game, &test, CURRENT_PLAYER, (CARDS_DRAWN - CARDS_PLAYED),
						   (-CARDS_DRAWN), CARDS_PLAYED, NO_CHANGE, NO_CHANGE,
						   NO_CHANGE, NO_CHANGE, NO_CHANGE, &passed, &tests);

	// Check if the card was actually played
	testCardPlayed(&game, &test, CURRENT_PLAYER, HAND_POS, &passed, &tests);

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


    // Check the effects the Smithy card has on the game state for the current player with no cards to draw.
    printf("\n* Testing Current Player Playing %s card with no cards to draw...\n\n", CARD);

    // Set Test Conditions
	game.deckCount[CURRENT_PLAYER] = 0;
	game.discardCount[CURRENT_PLAYER] = 0;

    // Copy a test instance
    memcpy(&test, &game, sizeof(struct gameState));

    // Call smithy function
    smithyCardEffect(&test, CURRENT_PLAYER, HAND_POS);

    testCurrentPlayerState(&game, &test, CURRENT_PLAYER, (- CARDS_PLAYED),
                           EMPTY_DECK, CARDS_PLAYED, NO_CHANGE, NO_CHANGE,
                           NO_CHANGE, NO_CHANGE, NO_CHANGE, &passed, &tests);

    // Check if the card was actually played
    testCardPlayed(&game, &test, CURRENT_PLAYER, HAND_POS, &passed, &tests);

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


