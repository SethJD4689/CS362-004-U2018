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

#define TEST_FUNCTION "isGameOver"
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

    const int GAME_IS_OVER = 1;
    const int GAME_IS_NOT_OVER = 0;

    // Initialize test game
    initializeGame(NUM_PLAYERS, actionCards, SEED, &game);
    memcpy(&test, &game, sizeof(struct gameState));


    printf("\n-------------------- Testing Function: %s --------------------\n", TEST_FUNCTION);


    printf("\n# Testing %s function with full supply piles...\n\n", TEST_FUNCTION);
    assertTrue(isGameOver(&test), GAME_IS_NOT_OVER, "Game Status", &passed, &tests);

    test.supplyCount[province] = 0;

    printf("\n# Testing %s function with empty province pile...\n\n", TEST_FUNCTION);
    assertTrue(isGameOver(&test), GAME_IS_OVER, "Game Status", &passed, &tests);

	memcpy(&test, &game, sizeof(struct gameState));

	test.supplyCount[province] = 1;

	printf("\n# Testing %s function with 1 province card in pile...\n\n", TEST_FUNCTION);
	assertTrue(isGameOver(&test), GAME_IS_NOT_OVER, "Game Status", &passed, &tests);

	int supplyCards[17] = {curse, estate, duchy, province, copper, silver,
						gold, actionCards[0], actionCards[1], actionCards[2],
						   actionCards[3], actionCards[4], actionCards[5],
						   actionCards[6], actionCards[7], actionCards[8],
						actionCards[9]};

	printf("\n# Testing %s function with 3 empty cards in pile...\n\n", TEST_FUNCTION);

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
	}


    printf("\n# Summary\n\nTests Conducted = %d, PASSED = %d, FAILED = %d\n",
           tests, passed, (tests - passed));

    printf("\n--------------------------------------------------------------\n");
}






