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
#include "time.h"

#define TEST_FUNCTION "updateCoins"
#define NUM_PLAYERS 2
#define CURRENT_PLAYER 0
#define OTHER_PLAYER 1

#define MAX_STRING_LENGTH 32
#define TRUE 1
#define FALSE 0

#ifndef EQ
#define EQ(A, B) ((A) == (B))
#endif


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
**  Function:
**  Description:
**
**	pre:
**	post:
**	post:
*******************************************************************************/
int main() {

	struct gameState game, test;

	const int SEED = 100;
	int actionCards[10] = {smithy, adventurer, salvager, steward, baron,
	                       village, minion, feast, embargo, outpost};

	int tests = 0;
	int passed = 0;

	int coins = 0;
	int bonus = 0;

	// Initialize test game
	initializeGame(NUM_PLAYERS, actionCards, SEED, &game);
	memcpy(&test, &game, sizeof(struct gameState));


	printf("\n-------------------- Testing Card: %s --------------------\n", TEST_FUNCTION);


	printf("\n# Testing %s function with no coins in hand...\n\n", TEST_FUNCTION);

	for(int i = 0; i < test.handCount[CURRENT_PLAYER]; i++){

		test.hand[CURRENT_PLAYER][i] = estate;
	}

	updateCoins(CURRENT_PLAYER, &test, bonus);
	assertTrue(test.coins, coins, "Coins in Hand", &passed, &tests);


	printf("\n# Testing %s function with no cards in hand...\n\n", TEST_FUNCTION);

	memcpy(&test, &game, sizeof(struct gameState));

	test.handCount[CURRENT_PLAYER] = 0;
	updateCoins(CURRENT_PLAYER, &test, bonus);
	assertTrue(test.coins, coins, "Coins in Hand", &passed, &tests);


	printf("\n# Testing %s function with various coins in hand...\n\n", TEST_FUNCTION);

	const int NUM_TESTS = 25;

	for(int i = 0; i < NUM_TESTS; i++){

		memcpy(&test, &game, sizeof(struct gameState));

		int min = copper;
		int max = gold;

		int copperCoins = 0;
		int silverCoins = 0;
		int goldCoins = 0;

		int totalCoinValue = 0;

		for(int j = 0; j < test.handCount[CURRENT_PLAYER]; j++){

			srand((unsigned) time(NULL) + j + i);

			int randomNumber = rand() % ((max + 1) - min) + min;
			test.hand[CURRENT_PLAYER][j] = randomNumber;

			if(randomNumber == copper){

				totalCoinValue += 1;
				copperCoins ++;

			} else if (randomNumber == silver){

				totalCoinValue += 2;
				silverCoins++;

			} else if (randomNumber == gold){

				totalCoinValue += 3;
				goldCoins++;
			}
		}

		char title[200];

		snprintf(title, sizeof(title), "Coins in Hand (Copper - %d, Silver - %d, Gold - %d)", copperCoins, silverCoins, goldCoins);

		updateCoins(CURRENT_PLAYER, &test, bonus);
		assertTrue(test.coins, totalCoinValue, title, &passed, &tests);
	}


	printf("\n# Testing %s function with various cards in hand...\n\n", TEST_FUNCTION);

	int supplyCards[17] = {curse, estate, duchy, province, copper, silver,
	                       gold, actionCards[0], actionCards[1], actionCards[2],
	                       actionCards[3], actionCards[4], actionCards[5],
	                       actionCards[6], actionCards[7], actionCards[8],
	                       actionCards[9]};

	for(int i = 0; i < NUM_TESTS; i++){

		memcpy(&test, &game, sizeof(struct gameState));

		int minC = 0;
		int maxC = 16;

		int copperCoins = 0;
		int silverCoins = 0;
		int goldCoins = 0;

		int totalCoinValue = 0;

		char title[300];

		strcpy(title, "Cards in Hand (");

		for(int j = 0; j < test.handCount[CURRENT_PLAYER]; j++){

			srand((unsigned) time(NULL) + j + i);

			int randomNumber = rand() % ((maxC + 1) - minC) + minC;
			test.hand[CURRENT_PLAYER][j] = supplyCards[randomNumber];

			char card[MAX_STRING_LENGTH];
			cardNumToName(supplyCards[randomNumber], card);

			if(j != test.handCount[CURRENT_PLAYER] - 1){
				strcat(title, card);
				strcat(title, ", ");
			} else {
				strcat(title, card);
			}

			if(randomNumber == copper){

				totalCoinValue += 1;
				copperCoins ++;

			} else if (randomNumber == silver){

				totalCoinValue += 2;
				silverCoins++;

			} else if (randomNumber == gold){

				totalCoinValue += 3;
				goldCoins++;
			}
		}

		strcat(title, ")");

		int minB = 0;
		int maxB = 10;

		int randomBonus = rand() % ((maxB + 1) - minB) + minB;

		char bonusAppend[3];

		strcat(title, "(Bonus = ");
		sprintf(bonusAppend, "%d", randomBonus);
		strcat(title, bonusAppend);
		strcat(title, ")");

		totalCoinValue += randomBonus;

		updateCoins(CURRENT_PLAYER, &test, randomBonus);
		assertTrue(test.coins, totalCoinValue, title, &passed, &tests);
	}

	printf("\n# Summary\n\nTests Conducted = %d, PASSED = %d, FAILED = %d\n",
	       tests, passed, (tests - passed));

	printf("\n--------------------------------------------------------------\n");
}







