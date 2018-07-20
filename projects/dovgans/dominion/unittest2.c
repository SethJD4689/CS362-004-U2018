/*******************************************************************************
** Assignment: CS362 - Assignment 3
** Filename: unittest2.c
** Author: Seth Dovgan
** Date: 10 July 2017
**
** Description: Tests the .
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "tester.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "time.h"

#define TEST_FUNCTION "updateCoins"
#define TEST_TYPE "Function"
#define NUM_PLAYERS 2
#define CURRENT_PLAYER 0
#define OTHER_PLAYER 1

/*******************************************************************************
**  Function:
**  Description:
*******************************************************************************/
int main() {

	struct gameState game, test;

	const int SEED = 100;
	int actionCards[10] = {smithy, adventurer, salvager, steward, baron,
	                       village, minion, feast, embargo, outpost};

	const int BONUS = 0;
	const int BONUS_2 = 10;
	int tests = 0;
	int passed = 0;

	int coins = 0;

	// Initialize test game
	initializeGame(NUM_PLAYERS, actionCards, SEED, &game);

	printTestHeader(TEST_TYPE, TEST_FUNCTION);


	printf("\n# Testing %s function with no coins in hand...\n\n", TEST_FUNCTION);

	for(int i = 0; i < game.handCount[CURRENT_PLAYER]; i++){
		game.hand[CURRENT_PLAYER][i] = smithy;
	}

	for(int i = 0; i < game.deckCount[CURRENT_PLAYER]; i++){
		game.deck[CURRENT_PLAYER][i] = smithy;
	}

	game.coins = 0;

	memcpy(&test, &game, sizeof(struct gameState));

	printf("- Coin Update\n");
	updateCoins(CURRENT_PLAYER, &test, BONUS);
	assertTrue(test.coins, game.coins, "Coins in Hand", &passed, &tests);

	printf("\n- Current Player Game State\n");
	testCurrentPlayerState(&game, &test, CURRENT_PLAYER, NO_CHANGE, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, &passed, &tests);

	printf("\n- Other Player Game State\n");
	testOtherPlayerState(&game, &test, OTHER_PLAYER, NO_CHANGE, NO_CHANGE,
	                     NO_CHANGE, NO_CHANGE, &passed, &tests);


	printf("\n# Testing %s function with no cards in hand...\n\n", TEST_FUNCTION);

	game.handCount[CURRENT_PLAYER] = 0;
	memcpy(&test, &game, sizeof(struct gameState));

	updateCoins(CURRENT_PLAYER, &test, BONUS);

	printf("- Coin Update\n");
	assertTrue(test.coins, coins, "Coins in Hand", &passed, &tests);

	printf("\n- Current Player Game State\n");
	testCurrentPlayerState(&game, &test, CURRENT_PLAYER, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, &passed, &tests);

	printf("\n- Other Player Game State\n");
	testOtherPlayerState(&game, &test, OTHER_PLAYER, NO_CHANGE, NO_CHANGE,
	                     NO_CHANGE, NO_CHANGE, &passed, &tests);


	printf("\n# Testing %s function with combination of coins in hand...\n\n", TEST_FUNCTION);

	game.coins = 8;
	game.handCount[CURRENT_PLAYER] = 5;
	game.hand[CURRENT_PLAYER][0] = copper;
	game.hand[CURRENT_PLAYER][1] = silver;
	game.hand[CURRENT_PLAYER][2] = gold;
	game.hand[CURRENT_PLAYER][3] = copper;
	game.hand[CURRENT_PLAYER][4] = copper;

	memcpy(&test, &game, sizeof(struct gameState));

	updateCoins(CURRENT_PLAYER, &test, BONUS);

	printf("- Coin Update\n");
	assertTrue(test.coins, game.coins, "Coins in Hand", &passed, &tests);

	printf("\n- Current Player Game State\n");
	testCurrentPlayerState(&game, &test, CURRENT_PLAYER, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, &passed, &tests);

	printf("\n- Other Player Game State\n");
	testOtherPlayerState(&game, &test, OTHER_PLAYER, NO_CHANGE, NO_CHANGE,
	                     NO_CHANGE, NO_CHANGE, &passed, &tests);


	printf("\n# Testing %s function with all cards and bonus (%d) in hand...\n\n", TEST_FUNCTION, BONUS);

	const int ALL_CARDS = 17;

	int supplyCards[] = {curse, estate, duchy, province, copper, silver,
					     gold, actionCards[0], actionCards[1], actionCards[2],
					     actionCards[3], actionCards[4], actionCards[5],
					     actionCards[6], actionCards[7], actionCards[8],
					     actionCards[9]};

	game.handCount[CURRENT_PLAYER] = ALL_CARDS;
	game.coins = 6;

	for(int i = 0; i < ALL_CARDS; i++){

		game.hand[CURRENT_PLAYER][i] = supplyCards[i];
	}

	memcpy(&test, &game, sizeof(struct gameState));

	printf("- Coin Update\n");

	updateCoins(CURRENT_PLAYER, &test, BONUS);
	assertTrue(test.coins, game.coins + BONUS, "Coins in Hand", &passed, &tests);

	printf("\n- Current Player Game State\n");
	testCurrentPlayerState(&game, &test, CURRENT_PLAYER, NO_CHANGE, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, &passed, &tests);

	printf("\n- Other Player Game State\n");
	testOtherPlayerState(&game, &test, OTHER_PLAYER, NO_CHANGE, NO_CHANGE,
	                     NO_CHANGE, NO_CHANGE, &passed, &tests);


	printf("\n# Testing %s function with all cards and bonus (%d) in hand...\n\n", TEST_FUNCTION, BONUS_2);

	memcpy(&test, &game, sizeof(struct gameState));

	printf("- Coin Update\n");

	updateCoins(CURRENT_PLAYER, &test, BONUS_2);
	assertTrue(test.coins, game.coins + BONUS_2, "Coins in Hand", &passed, &tests);

	printf("\n- Current Player Game State\n");
	game.coins += BONUS_2;
	testCurrentPlayerState(&game, &test, CURRENT_PLAYER, NO_CHANGE, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, &passed, &tests);

	printf("\n- Other Player Game State\n");
	testOtherPlayerState(&game, &test, OTHER_PLAYER, NO_CHANGE, NO_CHANGE,
	                     NO_CHANGE, NO_CHANGE, &passed, &tests);

	printTestSummary(passed, tests);
}







