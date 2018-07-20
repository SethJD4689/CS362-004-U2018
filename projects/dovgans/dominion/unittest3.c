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



/*
int scoreFor (int player, struct gameState *state) {

	int i;
	int score = 0;
	//score from hand
	for (i = 0; i < state->handCount[player]; i++)
	{
		if (state->hand[player][i] == curse) { score = score - 1; };
		if (state->hand[player][i] == estate) { score = score + 1; };
		if (state->hand[player][i] == duchy) { score = score + 3; };
		if (state->hand[player][i] == province) { score = score + 6; };
		if (state->hand[player][i] == great_hall) { score = score + 1; };
		if (state->hand[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
	}

	//score from discard
	for (i = 0; i < state->discardCount[player]; i++)
	{
		if (state->discard[player][i] == curse) { score = score - 1; };
		if (state->discard[player][i] == estate) { score = score + 1; };
		if (state->discard[player][i] == duchy) { score = score + 3; };
		if (state->discard[player][i] == province) { score = score + 6; };
		if (state->discard[player][i] == great_hall) { score = score + 1; };
		if (state->discard[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
	}

	//score from deck
	for (i = 0; i < state->deckCount[player]; i++)
	{
		if (state->deck[player][i] == curse) { score = score - 1; };
		if (state->deck[player][i] == estate) { score = score + 1; };
		if (state->deck[player][i] == duchy) { score = score + 3; };
		if (state->deck[player][i] == province) { score = score + 6; };
		if (state->deck[player][i] == great_hall) { score = score + 1; };
		if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
	}

	return score;
}*/

/*******************************************************************************
**  Function:
**  Description:
*******************************************************************************/
int main() {

	struct gameState game, test;

	const int SEED = 100;
	int actionCards[10] = {smithy, adventurer, salvager, steward, baron,
	                       village, minion, feast, embargo, outpost};

	int tests = 0;
	int passed = 0;

	const int NO_SCORE = 0;

	// Initialize test game
	initializeGame(NUM_PLAYERS, actionCards, SEED, &game);

	printTestHeader(TEST_TYPE, TEST_FUNCTION);


	printf("\n# Testing %s function with no hand, deck or discard...\n\n", TEST_FUNCTION);

	game.handCount[CURRENT_PLAYER] = 0;
	game.discardCount[CURRENT_PLAYER] = 0;
	game.deckCount[CURRENT_PLAYER] = 0;

	memcpy(&test, &game, sizeof(struct gameState));

	int score = 0;

	printf("- Score For\n");
	assertTrue(scoreFor(CURRENT_PLAYER, &test), score, "Player Score", &passed, &tests);

	printf("\n- Current Player Game State\n");
	testCurrentPlayerState(&game, &test, CURRENT_PLAYER, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, &passed, &tests);

	printf("\n- Other Player Game State\n");
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


	printf("\n# Testing %s function with score...\n\n", TEST_FUNCTION);

	game.handCount[CURRENT_PLAYER] = 0;
	game.discardCount[CURRENT_PLAYER] = 0;
	game.deckCount[CURRENT_PLAYER] = 0;

	memcpy(&test, &game, sizeof(struct gameState));

	printf("- Score For\n");
	assertTrue(scoreFor(CURRENT_PLAYER, &test), score, "Player Score", &passed, &tests);

	printf("\n- Current Player Game State\n");
	testCurrentPlayerState(&game, &test, CURRENT_PLAYER, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, &passed, &tests);

	printf("\n- Other Player Game State\n");
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

	testKingdomCardPiles(&game, &test, actionCards, cardChanges, &passed, &tests);

	/*
	printf("\n# Testing %s function with empty province pile...\n\n", TEST_FUNCTION);

	test.supplyCount[province] = 0;

	printf("- Game Status\n");
	assertTrue(isGameOver(&test), GAME_IS_OVER, "Game Status", &passed, &tests);

	printf("\n- Current Player Game State\n");
	testCurrentPlayerState(&game, &test, CURRENT_PLAYER, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, &passed, &tests);

	printf("\n- Other Player Game State\n");
	testOtherPlayerState(&game, &test, OTHER_PLAYER, NO_CHANGE, NO_CHANGE,
	                     NO_CHANGE, NO_CHANGE, &passed, &tests);


	printf("\n# Testing %s function with 1 province card in pile...\n\n", TEST_FUNCTION);

	test.supplyCount[province] = 1;

	printf("- Game Status\n");
	assertTrue(isGameOver(&test), GAME_IS_NOT_OVER, "Game Status", &passed, &tests);

	printf("\n- Current Player Game State\n");
	testCurrentPlayerState(&game, &test, CURRENT_PLAYER, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, &passed, &tests);

	printf("\n- Other Player Game State\n");
	testOtherPlayerState(&game, &test, OTHER_PLAYER, NO_CHANGE, NO_CHANGE,
	                     NO_CHANGE, NO_CHANGE, &passed, &tests);


	printf("\n# Testing %s function with every option of 3 empty piles of cards...\n\n", TEST_FUNCTION);

	int supplyCards[] = {curse, estate, duchy, province, copper, silver,
	                     gold, actionCards[0], actionCards[1], actionCards[2],
	                     actionCards[3], actionCards[4], actionCards[5],
	                     actionCards[6], actionCards[7], actionCards[8],
	                     actionCards[9]};

	for(int i = 0; i < sizeof(supplyCards) / sizeof(int); i++){

		for(int j = i + 1; j < sizeof(supplyCards) / sizeof(int); j++){

			for(int k = j + 1; k < sizeof(supplyCards) / sizeof(int); k++){

				memcpy(&test, &game, sizeof(struct gameState));

				test.supplyCount[supplyCards[i]] = 0;
				test.supplyCount[supplyCards[j]] = 0;
				test.supplyCount[supplyCards[k]] = 0;

				char cards[200];

				char card1[MAX_STRING_LENGTH];
				cardNumToName(supplyCards[i], card1);

				char card2[MAX_STRING_LENGTH];
				cardNumToName(supplyCards[j], card2);

				char card3[MAX_STRING_LENGTH];
				cardNumToName(supplyCards[k], card3);

				snprintf(cards, sizeof(cards), "Card Piles - %s, %s, %s are Empty", card1, card2, card3);

				assertTrue(isGameOver(&test), GAME_IS_OVER, cards, &passed, &tests);
			}
		}
	}*/

	printTestSummary(passed, tests);
}









