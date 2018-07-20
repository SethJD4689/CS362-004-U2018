/*******************************************************************************
** Assignment: CS362 - Assignment 3
** Filename: cardtest3.c
** Author: Seth Dovgan
** Date: 10 July 2017
**
** Description: Tests the Salvager Card.
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "tester.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_CARD "Salvager"
#define TEST_TYPE "Card"
#define NUM_PLAYERS 2
#define CURRENT_PLAYER 0
#define OTHER_PLAYER 1

#define MAX_STRING_LENGTH 32

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

    const int CHOICE = 0;
    const int CHOICE_1 = 1;
    const int CHOICE_2 = 0;
    const int HAND_POS = 0;
    const int CARDS_PLAYED = 1;
    const int CARDS_TRASHED = 1;
    const int EXTRA_BUY = 1;

    int bonus = 0;
    int tests = 0;
    int passed = 0;
    int cardValue = 0;

    // Initialize test game
    initializeGame(NUM_PLAYERS, actionCards, SEED, &game);
    memcpy(&test, &game, sizeof(struct gameState));
    cardEffect(salvager, CHOICE_1, CHOICE, CHOICE, &test, HAND_POS, &bonus);

    printTestHeader(TEST_TYPE, TEST_CARD);

    // Check the effects the Salvager card has on the game state for the current player.
    printf("\n* Testing Current Player Playing %s card using trash option...\n\n", TEST_CARD);

	// Calculate changes to the player's score after trashed card
	if (game.hand[CURRENT_PLAYER][CHOICE_1] == curse) {
		cardValue = cardValue - 1;
	} else if (game.hand[CURRENT_PLAYER][CHOICE_1] == estate) {
		cardValue = cardValue + 1;
	} else if (game.hand[CURRENT_PLAYER][CHOICE_1] == duchy) {
		cardValue = cardValue + 3;
	} else if (game.hand[CURRENT_PLAYER][CHOICE_1] == province) {
		cardValue = cardValue + 6;
	} else if (game.hand[CURRENT_PLAYER][CHOICE_1] == great_hall) {
		cardValue = cardValue + 1;
	} else if (game.hand[CURRENT_PLAYER][CHOICE_1] == gardens) {
		cardValue = cardValue + (fullDeckCount(CURRENT_PLAYER, 0, &game) / 10);
	};

    testCurrentPlayerState(&game, &test, CURRENT_PLAYER,
                           (- CARDS_PLAYED - CARDS_TRASHED), NO_CHANGE,
                           CARDS_PLAYED, NO_CHANGE,
                           getCost(handCard(CHOICE_1, &game)), EXTRA_BUY,
                           NO_CHANGE, (- cardValue), &passed, &tests);

	// Check the effects the Salvager card has on the game state for the other player.
	printf("\n* Testing Other Player with Current Player using Trash Option...\n\n");
	testOtherPlayerState(&game, &test, OTHER_PLAYER, NO_CHANGE, NO_CHANGE,
	                     NO_CHANGE, NO_CHANGE, &passed, &tests);

	// Verify no victory card piles were effected.
	printf("\n* Testing Victory Card Piles with Current Player using Trash Option......\n\n");
	testVictoryCardPiles(&game, &test, NO_CHANGE, NO_CHANGE, NO_CHANGE,
	                     &passed, &tests);

	// Verify no treasure card piles were effected
	printf("\n* Testing Treasure Card Piles with Current Player using Trash Option......\n\n");
	testTreasureCardPiles(&game, &test, NO_CHANGE, NO_CHANGE, NO_CHANGE,
	                      &passed, &tests);

	// Verify no kingdom card piles were effected
	printf("\n* Testing Kingdom Card Piles with Current Player using Trash Option......\n\n");

	int cardChanges[NUM_K_CARDS];

	for(int i = 0; i < NUM_K_CARDS; i++){
		cardChanges[i] = NO_CHANGE;
	}

	testKingdomCardPiles(&game, &test, actionCards, cardChanges, &passed, &tests);


    memcpy(&test, &game, sizeof(struct gameState));
    cardEffect(salvager, CHOICE_2, CHOICE, CHOICE, &test, HAND_POS, &bonus);


    printf("\n* Testing Current Player Playing %s card NOT using trash option...\n\n", TEST_CARD);

	testCurrentPlayerState(&game, &test, CURRENT_PLAYER,
	                       (- CARDS_PLAYED), NO_CHANGE,
	                       CARDS_PLAYED, NO_CHANGE, NO_CHANGE, EXTRA_BUY,
	                       NO_CHANGE, NO_CHANGE, &passed, &tests);

	// Check the effects the Salvager card has on the game state for the other player.
	printf("\n* Testing Other Player with Current Player NOT using Trash Option...\n\n");
	testOtherPlayerState(&game, &test, OTHER_PLAYER, NO_CHANGE, NO_CHANGE,
	                     NO_CHANGE, NO_CHANGE, &passed, &tests);

	// Verify no victory card piles were effected.
	printf("\n* Testing Victory Card Piles with Current Player NOT using Trash Option......\n\n");
	testVictoryCardPiles(&game, &test, NO_CHANGE, NO_CHANGE, NO_CHANGE,
	                     &passed, &tests);

	// Verify no treasure card piles were effected
	printf("\n* Testing Treasure Card Piles with Current Player NOT using Trash Option......\n\n");
	testTreasureCardPiles(&game, &test, NO_CHANGE, NO_CHANGE, NO_CHANGE,
	                      &passed, &tests);

	// Verify no kingdom card piles were effected
	printf("\n* Testing Kingdom Card Piles with Current Player NOT using Trash Option......\n\n");
	testKingdomCardPiles(&game, &test, actionCards, cardChanges, &passed, &tests);

    printTestSummary(passed, tests);
}




