/*******************************************************************************
** Assignment: CS362 - Assignment 3
** Filename: unittest3.c
** Author: Seth Dovgan
** Date: 10 July 2017
**
** Description: Tests the scoreFor function.
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "tester.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FUNCTION "scoreFor"
#define TYPE "Function"
#define NO_SCORE 0
#define CURSE (-1)
#define ESTATE 1
#define DUCHY 3
#define PROVINCE 6
#define GREAT_HALL 1

/*******************************************************************************
**  Function: testScoreForState
**  Description: tests the player's score and for changes in the game state
*******************************************************************************/
void testScoreForState(struct gameState *game, struct gameState *test,
					   int actionCards[], int player, int score, int *passed,
					   int *tests){

	printf("* Score For\n");
	assertTrue(scoreFor(player, test), score, "Player Score", passed, tests);

	printf("\n* Current Player Game State\n");
	testCurrentPlayerNoStateChange(game, test, player, passed, tests);

	printf("\n* Testing Other Player...\n\n");
	testOtherPlayerNoStateChange(game, test, OTHER_PLAYER, passed, tests);

	printf("\n* Testing Victory Card Piles...\n\n");
	testVictoryCardPilesNoChange(game, test, passed, tests);

	printf("\n* Testing Treasure Card Piles...\n\n");
	testTreasureCardPilesNoChange(game, test, passed, tests);

	printf("\n* Testing Kingdom Card Piles...\n\n");
	testKingdomCardPilesNoChange(game, test, actionCards, passed, tests);
}

/*******************************************************************************
**  Function: main
**  Description: tests the scoreFor function
*******************************************************************************/
int main() {

	struct gameState game, test;

	int actionCards[10] = {smithy, adventurer, salvager, steward, baron,
	                       village, minion, feast, embargo, outpost};

	int tests = 0;
	int passed = 0;
	int score;

    // Initialize the game instance for the test
	initializeGame(NUM_PLAYERS, actionCards, SEED, &game);

    // Print Test Header
	printTestHeader(TYPE, FUNCTION);

	printf("\n# Testing %s function with no hand, deck or discard...\n\n", TEST_FUNCTION);

	// Set test conditions
	game.handCount[CURRENT_PLAYER] = 0;
	game.discardCount[CURRENT_PLAYER] = 0;
	game.deckCount[CURRENT_PLAYER] = 0;

	memcpy(&test, &game, sizeof(struct gameState));

	testScoreForState(&game, &test, actionCards, CURRENT_PLAYER, NO_SCORE, &passed,
	&tests);


	printf("\n# Testing %s function with score in deck, hand and discard...\n\n", TEST_FUNCTION);

	score = 0; // reset the player's test score

	// Add test values in player's hand
	game.handCount[CURRENT_PLAYER] = 6;
	game.hand[CURRENT_PLAYER][0] = curse;
	game.hand[CURRENT_PLAYER][1] = estate;
	game.hand[CURRENT_PLAYER][2] = duchy;
	game.hand[CURRENT_PLAYER][3] = province;
	game.hand[CURRENT_PLAYER][4] = great_hall;
	game.hand[CURRENT_PLAYER][5] = gardens;

	score += CURSE + ESTATE + DUCHY + PROVINCE + GREAT_HALL
			+ fullDeckCount(CURRENT_PLAYER, 0, &game) / 10;

    // Add test values in player's discard
	game.discardCount[CURRENT_PLAYER] = 1;
	game.discard[CURRENT_PLAYER][0] = estate;

	score += ESTATE;

    // Add test values in player's deck
	game.deckCount[CURRENT_PLAYER] = 6;
	game.deck[CURRENT_PLAYER][0] = curse;
	game.deck[CURRENT_PLAYER][1] = estate;
	game.deck[CURRENT_PLAYER][2] = duchy;
	game.deck[CURRENT_PLAYER][3] = province;
	game.deck[CURRENT_PLAYER][4] = great_hall;
	game.deck[CURRENT_PLAYER][5] = gardens;

	score += CURSE + ESTATE + DUCHY + PROVINCE + GREAT_HALL
	         + fullDeckCount(CURRENT_PLAYER, 0, &game) / 10;

	memcpy(&test, &game, sizeof(struct gameState));

	// Test the score and the game state change
	testScoreForState(&game, &test, actionCards, CURRENT_PLAYER, score, &passed,
	                  &tests);

	printf("\n# Testing %s function with score cards in hand only...\n\n", TEST_FUNCTION);

	score = 0; // reset the player's test score

    // Add test values in player's hand
	game.handCount[CURRENT_PLAYER] = 6;
	game.hand[CURRENT_PLAYER][0] = curse;
	game.hand[CURRENT_PLAYER][1] = estate;
	game.hand[CURRENT_PLAYER][2] = duchy;
	game.hand[CURRENT_PLAYER][3] = province;
	game.hand[CURRENT_PLAYER][4] = great_hall;
	game.hand[CURRENT_PLAYER][5] = gardens;

	score += CURSE + ESTATE + DUCHY + PROVINCE + GREAT_HALL
	         + fullDeckCount(CURRENT_PLAYER, 0, &game) / 10;

	// Set non-score cards in discard
	game.discardCount[CURRENT_PLAYER] = 1;
	game.discard[CURRENT_PLAYER][0] = smithy;

    // Set non-score cards in deck
	game.deckCount[CURRENT_PLAYER] = 6;
	game.deck[CURRENT_PLAYER][0] = adventurer;
	game.deck[CURRENT_PLAYER][1] = minion;
	game.deck[CURRENT_PLAYER][2] = feast;
	game.deck[CURRENT_PLAYER][3] = embargo;
	game.deck[CURRENT_PLAYER][4] = outpost;
	game.deck[CURRENT_PLAYER][5] = village;

	memcpy(&test, &game, sizeof(struct gameState));

    // Test the score and the game state change
	testScoreForState(&game, &test, actionCards, CURRENT_PLAYER, score, &passed,
	                  &tests);

	printf("\n# Testing %s function with score cards in deck only...\n\n", TEST_FUNCTION);

	score = 0; // reset the player's test score

    // Set non-score cards in hand
	game.handCount[CURRENT_PLAYER] = 6;
	game.hand[CURRENT_PLAYER][0] = adventurer;
	game.hand[CURRENT_PLAYER][1] = minion;
	game.hand[CURRENT_PLAYER][2] = feast;
	game.hand[CURRENT_PLAYER][3] = embargo;
	game.hand[CURRENT_PLAYER][4] = outpost;
	game.hand[CURRENT_PLAYER][5] = village;

    // Set non-score cards in discard
	game.discardCount[CURRENT_PLAYER] = 1;
	game.discard[CURRENT_PLAYER][0] = smithy;

    // Set score cards in deck
	game.deckCount[CURRENT_PLAYER] = 6;
	game.deck[CURRENT_PLAYER][0] = curse;
	game.deck[CURRENT_PLAYER][1] = estate;
	game.deck[CURRENT_PLAYER][2] = duchy;
	game.deck[CURRENT_PLAYER][3] = province;
	game.deck[CURRENT_PLAYER][4] = great_hall;
	game.deck[CURRENT_PLAYER][5] = gardens;

	score += CURSE + ESTATE + DUCHY + PROVINCE + GREAT_HALL
	         + fullDeckCount(CURRENT_PLAYER, 0, &game) / 10;

	memcpy(&test, &game, sizeof(struct gameState));

    // Test the score and the game state change
	testScoreForState(&game, &test, actionCards, CURRENT_PLAYER, score, &passed,
	                  &tests);

	printf("\n# Testing %s function with score cards in discard only...\n\n", TEST_FUNCTION);

	score = 0; // reset the player's test score

    // Set non-score cards in hand
	game.handCount[CURRENT_PLAYER] = 6;
	game.hand[CURRENT_PLAYER][0] = minion;
	game.hand[CURRENT_PLAYER][1] = minion;
	game.hand[CURRENT_PLAYER][2] = feast;
	game.hand[CURRENT_PLAYER][3] = embargo;
	game.hand[CURRENT_PLAYER][4] = outpost;
	game.hand[CURRENT_PLAYER][5] = village;

    // Set score cards in discard
	game.discardCount[CURRENT_PLAYER] = 1;
	game.discard[CURRENT_PLAYER][0] = province;

    score += PROVINCE;

    // Set non-score cards in deck
	game.deckCount[CURRENT_PLAYER] = 6;
	game.deck[CURRENT_PLAYER][0] = smithy;
	game.deck[CURRENT_PLAYER][1] = adventurer;
	game.deck[CURRENT_PLAYER][2] = smithy;
	game.deck[CURRENT_PLAYER][3] = village;
	game.deck[CURRENT_PLAYER][4] = outpost;
	game.deck[CURRENT_PLAYER][5] = feast;

	memcpy(&test, &game, sizeof(struct gameState));

    // Test the score and the game state change
	testScoreForState(&game, &test, actionCards, CURRENT_PLAYER, score, &passed,
	                  &tests);


	// Print the test summary
	printTestSummary(passed, tests);
}









