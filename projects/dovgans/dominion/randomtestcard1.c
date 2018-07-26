/*******************************************************************************
** Assignment: CS362 - Assignment 4
** Filename: randomtestcard1.c
** Author: Seth Dovgan
** Date: 23 JUL 2018
**
** Description: Tests the Smithy card with random testing.
*******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "tester.h"


#define CARD "Smithy"
#define TYPE "Card"

/*******************************************************************************
**  Function: main
**  Description: Tests the Smithy card effect on the state of the game with
**  random testing.
*******************************************************************************/
int main() {

	srand(time(NULL));

	struct gameState game, test;

	int actionCards[NUM_K_CARDS] = {smithy, adventurer, salvager, steward, baron,
	                                village, minion, feast, embargo, outpost};

	int tests = 0;
	int passed = 0;

	generateRandomGameState();

	// Print Test Summary
	printTestSummary(passed, tests);


}

