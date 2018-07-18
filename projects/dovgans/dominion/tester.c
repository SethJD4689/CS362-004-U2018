//
// Created by Seth Dovgan on 7/17/18.
//

#include <string.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"

#define EQ(A, B) ((A) == (B))
#define NEQ(A, B) ((A) != (B))


/*******************************************************************************
**  Function: assertTrue
**  Description:
**
**  param:
**	param:
**
**	pre:
**	post:
**	post:
*******************************************************************************/
void assertTrue(int expected, int actual, char *message, int *passed, int *tests) {

	(*tests)++;

	if (EQ(expected, actual)) {

		printf("PASSED: %s = %d, expected = %d\n", message, actual, expected);
		(*passed)++;

	} else {

		printf("FAILED: %s = %d, expected = %d\n", message, actual, expected);
	}
}

/*******************************************************************************
**  Function: assertTrue
**  Description:
**
**  param:
**	param:
**
**	pre:
**	post:
**	post:
*******************************************************************************/
void assertFalse(int expected, int actual, char *message, int *passed, int *tests) {

	(*tests)++;

	if (NEQ(expected, actual)) {

		printf("PASSED: %s = %d, expected = %d\n", message, actual, expected);
		(*passed)++;

	} else {

		printf("FAILED: %s = %d, expected = %d\n", message, actual, expected);
	}
}

/*******************************************************************************
**  Function: assertGameStateChanges
**  Description: Tests the game state
**
**  param:
**	param:
**
**	pre:
**	post:
**	post:
*******************************************************************************/
void testCurrentPlayerState(struct gameState *game, struct gameState *test,
                            int player, int hand, int deck, int played,
                            int discard, int coins, int buys, int actions,
                            int score, int *passed, int *tests) {

	// Test changes to the player's hand
	assertTrue(game->handCount[player] + hand,
	           test->handCount[player],
	           "Cards in Hand", passed, tests);

	// Test changes to the player's deck
	assertTrue(game->deckCount[player] + deck,
	           test->deckCount[player],
	           "Cards in Deck", passed, tests);

	// Test changes to the cards played
	assertTrue(game->playedCardCount + played,
	           test->playedCardCount,
	           "Cards Played", passed, tests);

	// Test changes to the discard pile
	assertTrue(game->discardCount[player] + discard,
	           test->discardCount[player],
	           "Discard Pile", passed, tests);

	// Test changes to the coins remaining
	assertTrue(game->coins + coins, test->coins,
	           "Coins Remaining", passed, tests);

	// Test changes to the remaining buys
	assertTrue(game->numBuys + buys, test->numBuys,
	           "Buys Remaining", passed, tests);

	// Test changes to the remaining action cards
	assertTrue(game->numActions + actions, test->numActions,
	           "Actions Remaining", passed, tests);

	// Test is outpost was played
	assertTrue(game->outpostPlayed, test->outpostPlayed,
	           "Outpost Played", passed, tests);

	// Test changes to the score
	assertTrue(scoreFor(player, game) + score,
	           scoreFor(player, test),
	           "Player Score", passed, tests);
}

/*******************************************************************************
**  Function: assertGameStateChanges
**  Description: Tests the game state
**
**  param:
**	param:
**
**	pre:
**	post:
**	post:
*******************************************************************************/
void testOtherPlayerState(struct gameState *game, struct gameState *test,
		                  int player, int hand, int deck, int discard,
		                  int score, int *passed, int *tests) {

	// Test changes to the player's hand
	assertTrue(game->handCount[player] + hand,
	           test->handCount[player],
	           "Cards in Hand", passed, tests);

	// Test changes to the player's deck
	assertTrue(game->deckCount[player] + deck,
	           test->deckCount[player],
	           "Cards in Deck", passed, tests);

	// Test changes to the discard pile
	assertTrue(game->discardCount[player] + discard,
	           test->discardCount[player],
	           "Discard Pile", passed, tests);

	// Test changes to the score
	assertTrue(scoreFor(player, game) + score,
	           scoreFor(player, test),
	           "Player Score", passed, tests);
}

/*******************************************************************************
**  Function: assertGameStateChanges
**  Description: Tests the game state
**
**  param:
**	param:
**
**	pre:
**	post:
**	post:
*******************************************************************************/
void testKingdomCardPiles(struct gameState *game, struct gameState *test,
		int actionCards[], int cardChanges[], int *passed, int *tests){

	for(int i = 0; i < NUM_K_CARDS; i++){

		char name[MAX_STRING_LENGTH];
		cardNumToName(actionCards[i], name);

		strcat(name, " Cards Remaining");

		assertTrue(supplyCount(actionCards[i], game) + cardChanges[i],
		           supplyCount(actionCards[i], test),
		           name, passed, tests);
	}
}

/*******************************************************************************
**  Function: assertGameStateChanges
**  Description: Tests the game state
**
**  param:
**	param:
**
**	pre:
**	post:
**	post:
*******************************************************************************/
void testVictoryCardPiles(struct gameState *game, struct gameState *test,
                          int estateChange, int duchyChange, int provinceChange,
                          int *passed, int *tests){

	assertTrue(supplyCount(estate, game) + estateChange,
	           supplyCount(estate, test),
	           "Estate Cards Remaining", passed, tests);

	assertTrue(supplyCount(duchy, game) + duchyChange,
	           supplyCount(duchy, test),
	           "Duchy Cards Remaining", passed, tests);

	assertTrue(supplyCount(province, game) + provinceChange,
	           supplyCount(province, test),
	           "Province Cards Remaining", passed, tests);
}

/*******************************************************************************
**  Function: assertGameStateChanges
**  Description: Tests the game state
**
**  param:
**	param:
**
**	pre:
**	post:
**	post:
*******************************************************************************/
void testTreasureCardPiles(struct gameState *game, struct gameState *test,
		                   int copperChange, int silverChange, int goldChange,
		                   int *passed, int *tests){

	assertTrue(supplyCount(copper, game) + copperChange,
	           supplyCount(copper, test),
	           "Copper Cards Remaining", passed, tests);

	assertTrue(supplyCount(silver, game) + silverChange,
	           supplyCount(silver, test),
	           "Silver Cards Remaining", passed, tests);

	assertTrue(supplyCount(gold, game) + goldChange,
	           supplyCount(gold, test),
	           "Gold Cards Remaining", passed, tests);
}

void printTestHeader(char type[], char name[]){

	printf("\n>>> Testing %s: %s >>>\n", type, name);
}

void printTestSummary(int passed, int tests){

	printf("\n>>> Summary >>>\n\nTests Conducted = %d, PASSED = %d, FAILED = %d\n",
	       tests, passed, (tests - passed));
}
