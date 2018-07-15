/*******************************************************************************
** Assignment: CS362 - Assignment 3
** Filename: cardtest1.c
** Author: Seth Dovgan
** Date: 10 July 2017
**
** Description: Tests the Smithy Card.
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TEST_CARD "Smithy"
#define NUM_PLAYERS 2
#define CURRENT_PLAYER 0
#define OTHER_PLAYER 1

#define MAX_STRING_LENGTH 32
#define TRUE 1
#define FALSE 0

#ifndef EQ
#define EQ(A, B) ((A) == (B))
#endif


void assertTrue(int expected, int actual, char *message, int *tracker) {

	if (EQ(expected, actual)) {

		printf("PASSED: %s = %d, expected = %d\n", message, actual, expected);
		tracker++;


	} else {

		printf("FAILED: %s = %d, expected = %d\n", message, actual, expected);
	}
}


int main() {

	struct gameState game, test;

	const int SEED = 100;
	int actionCards[10] = {smithy, adventurer, salvager, steward, baron,
						village, minion, feast, embargo, outpost};

	const int CHOICE = 0;
	const int HAND_POS = 0;
	const int CARDS_DRAWN = 3;
	const int CARDS_PLAYED = 1;

	int passedTest = 0;

	int bonus = 0;

	// Initialize test game
	initializeGame(NUM_PLAYERS, actionCards, SEED, &game);
	memcpy(&test, &game, sizeof(struct gameState));
	cardEffect(smithy, CHOICE, CHOICE, CHOICE, &test, HAND_POS, &bonus);

	printf("\n-------------------- Testing Card: %s --------------------\n", TEST_CARD);

	printf("\n# Testing Current Player Playing %s card...\n\n", TEST_CARD);

	// Test changes to the current players hand
	assertTrue(game.handCount[CURRENT_PLAYER] + CARDS_DRAWN - CARDS_PLAYED,
	           test.handCount[CURRENT_PLAYER], "Cards in Hand");

	// Test changes to the current players deck
	assertTrue(game.deckCount[CURRENT_PLAYER] - CARDS_DRAWN,
	           test.deckCount[CURRENT_PLAYER], "Cards in Deck");

	// Test changes to the cards played
	assertTrue(game.playedCardCount + CARDS_PLAYED,
	           test.playedCardCount, "Cards Played");

	// Test changes to the discard pile
	assertTrue(game.discardCount[CURRENT_PLAYER], test.discardCount[CURRENT_PLAYER], "Discard Pile");
	
	printf("Coins Remaining = %d, expected = %d\n", test.coins, game.coins);
	printf("Buys Remaining = %d, expected = %d\n", test.numBuys, game.numBuys);
	printf("Actions Remaining = %d, expected = %d\n", test.numActions, game.numActions);
	printf("Outpost played = %d, expected = %d\n", test.outpostPlayed, game.outpostPlayed);
	printf("Score = %d, expected = %d\n", scoreFor(CURRENT_PLAYER, &test), scoreFor(CURRENT_PLAYER, &game));

	printf("\n# Testing Other Player...\n\n");
	printf("Cards in Hand = %d, expected = %d\n",
	       test.handCount[OTHER_PLAYER], game.handCount[OTHER_PLAYER]);
	printf("Cards Remaining in Deck = %d, expected = %d\n",
	       test.deckCount[OTHER_PLAYER], game.deckCount[OTHER_PLAYER]);
	printf("Discard Pile = %d, expected = %d\n",
	       test.discardCount[OTHER_PLAYER], game.discardCount[OTHER_PLAYER]);
	printf("Score = %d, expected = %d\n", scoreFor(OTHER_PLAYER, &test), scoreFor(OTHER_PLAYER, &game));

	printf("\nVictory Card Piles\n");
	printf("Remaining Estate Cards = %d, expected = %d\n", supplyCount(estate, &test), supplyCount(estate, &game));
	printf("Remaining Duchy Cards = %d, expected = %d\n", supplyCount(duchy, &test), supplyCount(duchy, &game));
	printf("Remaining Province Cards = %d, expected = %d\n", supplyCount(province, &test), supplyCount(province, &game));

	printf("\nTreasure Card Piles\n");
	printf("Remaining Copper Cards = %d, expected = %d\n", supplyCount(copper, &test), supplyCount(copper, &game));
	printf("Remaining Silver Cards = %d, expected = %d\n", supplyCount(silver, &test), supplyCount(silver, &game));
	printf("Remaining Gold Cards = %d, expected = %d\n", supplyCount(gold, &test), supplyCount(gold, &game));

	printf("\nKingdom Card Piles\n");

	for(int i = 0; i < sizeof(actionCards) / sizeof(int); i++){

		char name[MAX_STRING_LENGTH];
		cardNumToName(actionCards[i], name);
		printf("Remaining %s cards = %d, expected = %d\n", name, supplyCount(actionCards[i], &test), supplyCount(actionCards[i], &game));
	}

	printf("\n--------------------------------------------------------------\n");

}


