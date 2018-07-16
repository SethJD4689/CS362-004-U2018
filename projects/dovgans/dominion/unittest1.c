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


    printf("\n-------------------- Testing Card: %s --------------------\n", TEST_FUNCTION);


    printf("\n# Testing %s function with full supply piles...\n\n", TEST_FUNCTION);

    // Test changes to the current players hand
    assertTrue(isGameOver(&game), GAME_IS_NOT_OVER, "Game Status", &passed, &tests);



    printf("\n# Testing %s function will full supply piles...\n\n", TEST_FUNCTION);

    // Test changes to the current players hand
    assertTrue(isGameOver(&game), GAME_IS_NOT_OVER, "Game Status", &passed, &tests);

    printf("\n# Testing %s function will full supply piles...\n\n", TEST_FUNCTION);

    // Test changes to the current players hand
    assertTrue(isGameOver(&game), GAME_IS_NOT_OVER, "Game Status", &passed, &tests);

    printf("\n# Testing %s function will full supply piles...\n\n", TEST_FUNCTION);

    // Test changes to the current players hand
    assertTrue(isGameOver(&game), GAME_IS_NOT_OVER, "Game Status", &passed, &tests);




    printf("\n# Summary\n\nTests Conducted = %d, PASSED = %d, FAILED = %d\n",
           tests, passed, (tests - passed));

    printf("\n--------------------------------------------------------------\n");

}




