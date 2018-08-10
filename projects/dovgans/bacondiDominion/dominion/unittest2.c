/*******************************************************************************
** Assignment: CS362 - Assignment 3
** Filename: unittest2.c
** Author: Seth Dovgan
** Date: 10 July 2017
**
** Description: Tests the updateCoins function.
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

#define FUNCTION "updateCoins"
#define TYPE "Function"
#define LOWER_LIMIT_BONUS 0
#define UPPER_LIMIT_BONUS 10

/*******************************************************************************
**  Function: main
**  Description: Tests the updateCoins function.
*******************************************************************************/
int main() {

	struct gameState game, test;

	int actionCards[10] = {smithy, adventurer, salvager, steward, baron,
	                       village, minion, feast, embargo, outpost};

	int tests = 0;
	int passed = 0;

	int coins = 0;

	// Initialize the game instance for the test
	initializeGame(NUM_PLAYERS, actionCards, SEED, &game);

	// Print Test Header
	printTestHeader(TYPE, FUNCTION);


	printf("\n# Testing %s function with no coins in hand...\n\n", FUNCTION);

	// Remove coins from hand
	for(int i = 0; i < game.handCount[CURRENT_PLAYER]; i++){
		game.hand[CURRENT_PLAYER][i] = smithy;
		game.hand[OTHER_PLAYER][i] = smithy;
	}

	// Remove coins from deck
	for(int i = 0; i < game.deckCount[CURRENT_PLAYER]; i++){
		game.deck[CURRENT_PLAYER][i] = smithy;
		game.deck[OTHER_PLAYER][i] = smithy;
	}

	game.coins = 0;	// Reset count

	memcpy(&test, &game, sizeof(struct gameState));

	printf("- Coin Update\n");
	updateCoins(CURRENT_PLAYER, &test, LOWER_LIMIT_BONUS);
	assertTrue(test.coins, game.coins, "Coins in Hand", &passed, &tests);

	printf("\n- Current Player Game State\n");
	testCurrentPlayerNoStateChange(&game, &test, CURRENT_PLAYER, &passed, &tests);

	printf("\n* Testing Other Player...\n\n");
	testOtherPlayerNoStateChange(&game, &test, OTHER_PLAYER, &passed, &tests);

	printf("\n* Testing Victory Card Piles...\n\n");
	testVictoryCardPilesNoChange(&game, &test, &passed, &tests);

	printf("\n* Testing Treasure Card Piles...\n\n");
	testTreasureCardPilesNoChange(&game, &test, &passed, &tests);

	printf("\n* Testing Kingdom Card Piles...\n\n");
	testKingdomCardPilesNoChange(&game, &test, actionCards, &passed, &tests);


	printf("\n# Testing %s function with no cards in hand...\n\n", FUNCTION);

    // Set cards in hand to 0
	game.handCount[CURRENT_PLAYER] = 0;
    game.handCount[OTHER_PLAYER] = 0;

	memcpy(&test, &game, sizeof(struct gameState));

	printf("- Coin Update\n");
    updateCoins(CURRENT_PLAYER, &test, LOWER_LIMIT_BONUS);
	assertTrue(test.coins, coins, "Coins in Hand", &passed, &tests);

    printf("\n- Current Player Game State\n");
    testCurrentPlayerNoStateChange(&game, &test, CURRENT_PLAYER, &passed, &tests);

    printf("\n* Testing Other Player...\n\n");
    testOtherPlayerNoStateChange(&game, &test, OTHER_PLAYER, &passed, &tests);

    printf("\n* Testing Victory Card Piles...\n\n");
    testVictoryCardPilesNoChange(&game, &test, &passed, &tests);

    printf("\n* Testing Treasure Card Piles...\n\n");
    testTreasureCardPilesNoChange(&game, &test, &passed, &tests);

    printf("\n* Testing Kingdom Card Piles...\n\n");
    testKingdomCardPilesNoChange(&game, &test, actionCards, &passed, &tests);


	printf("\n# Testing %s function with combination of coins in hand...\n\n", FUNCTION);

	game.coins = 8;
	game.handCount[CURRENT_PLAYER] = 5;
    game.handCount[OTHER_PLAYER] = 5;
	game.hand[CURRENT_PLAYER][0] = copper;
    game.hand[OTHER_PLAYER][0] = copper;
	game.hand[CURRENT_PLAYER][1] = silver;
    game.hand[OTHER_PLAYER][1] = silver;
	game.hand[CURRENT_PLAYER][2] = gold;
    game.hand[OTHER_PLAYER][2] = gold;
	game.hand[CURRENT_PLAYER][3] = copper;
    game.hand[OTHER_PLAYER][3] = copper;
	game.hand[CURRENT_PLAYER][4] = copper;
    game.hand[OTHER_PLAYER][4] = copper;

	memcpy(&test, &game, sizeof(struct gameState));

	printf("- Coin Update\n");
    updateCoins(CURRENT_PLAYER, &test, LOWER_LIMIT_BONUS);
	assertTrue(test.coins, game.coins, "Coins in Hand", &passed, &tests);

    printf("\n- Current Player Game State\n");
    testCurrentPlayerNoStateChange(&game, &test, CURRENT_PLAYER, &passed, &tests);

    printf("\n* Testing Other Player...\n\n");
    testOtherPlayerNoStateChange(&game, &test, OTHER_PLAYER, &passed, &tests);

    printf("\n* Testing Victory Card Piles...\n\n");
    testVictoryCardPilesNoChange(&game, &test, &passed, &tests);

    printf("\n* Testing Treasure Card Piles...\n\n");
    testTreasureCardPilesNoChange(&game, &test, &passed, &tests);

    printf("\n* Testing Kingdom Card Piles...\n\n");
    testKingdomCardPilesNoChange(&game, &test, actionCards, &passed, &tests);


	printf("\n# Testing %s function with all cards and bonus (%d) in hand...\n\n", FUNCTION, LOWER_LIMIT_BONUS);

	const int ALL_CARDS = 17;

	int supplyCards[] = {curse, estate, duchy, province, copper, silver,
					     gold, actionCards[0], actionCards[1], actionCards[2],
					     actionCards[3], actionCards[4], actionCards[5],
					     actionCards[6], actionCards[7], actionCards[8],
					     actionCards[9]};

	game.handCount[CURRENT_PLAYER] = ALL_CARDS;
	game.handCount[OTHER_PLAYER] = ALL_CARDS;
	game.coins = 6;

	for(int i = 0; i < ALL_CARDS; i++){

		game.hand[CURRENT_PLAYER][i] = supplyCards[i];
        game.hand[OTHER_PLAYER][i] = supplyCards[i];
	}

	memcpy(&test, &game, sizeof(struct gameState));

	printf("- Coin Update\n");
	updateCoins(CURRENT_PLAYER, &test, LOWER_LIMIT_BONUS);
	assertTrue(test.coins, game.coins + LOWER_LIMIT_BONUS, "Coins in Hand",
               &passed, &tests);

    printf("\n- Current Player Game State\n");
    testCurrentPlayerState(&game, &test, CURRENT_PLAYER, NO_CHANGE,
                           NO_CHANGE, NO_CHANGE, NO_CHANGE, LOWER_LIMIT_BONUS,
                           NO_CHANGE, NO_CHANGE, NO_CHANGE, smithy, &passed, &tests);

    printf("\n* Testing Other Player...\n\n");
    testOtherPlayerNoStateChange(&game, &test, OTHER_PLAYER, &passed, &tests);

    printf("\n* Testing Victory Card Piles...\n\n");
    testVictoryCardPilesNoChange(&game, &test, &passed, &tests);

    printf("\n* Testing Treasure Card Piles...\n\n");
    testTreasureCardPilesNoChange(&game, &test, &passed, &tests);

    printf("\n* Testing Kingdom Card Piles...\n\n");
    testKingdomCardPilesNoChange(&game, &test, actionCards, &passed, &tests);



	printf("\n# Testing %s function with all cards and bonus (%d) in hand...\n\n", FUNCTION, UPPER_LIMIT_BONUS);

	memcpy(&test, &game, sizeof(struct gameState));

    printf("- Coin Update\n");
    updateCoins(CURRENT_PLAYER, &test, UPPER_LIMIT_BONUS);
    assertTrue(test.coins, game.coins + UPPER_LIMIT_BONUS, "Coins in Hand",
               &passed, &tests);

    printf("\n- Current Player Game State\n");
    testCurrentPlayerState(&game, &test, CURRENT_PLAYER, NO_CHANGE,
                           NO_CHANGE, NO_CHANGE, NO_CHANGE, UPPER_LIMIT_BONUS,
                           NO_CHANGE, NO_CHANGE, NO_CHANGE, smithy, &passed, &tests);

    printf("\n* Testing Other Player...\n\n");
    testOtherPlayerNoStateChange(&game, &test, OTHER_PLAYER, &passed, &tests);

    printf("\n* Testing Victory Card Piles...\n\n");
    testVictoryCardPilesNoChange(&game, &test, &passed, &tests);

    printf("\n* Testing Treasure Card Piles...\n\n");
    testTreasureCardPilesNoChange(&game, &test, &passed, &tests);

    printf("\n* Testing Kingdom Card Piles...\n\n");
    testKingdomCardPilesNoChange(&game, &test, actionCards, &passed, &tests);


    // Print the test summary
	printTestSummary(passed, tests);
}







