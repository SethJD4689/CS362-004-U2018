/*******************************************************************************
** Assignment: CS362 - Assignment 3
** Filename: cardtest2.c
** Author: Seth Dovgan
** Date: 10 July 2017
**
** Description: Tests the Adventurer Card.
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "tester.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>

#define TEST_CARD "Adventurer"
#define TEST_TYPE "Card"
#define NUM_PLAYERS 2
#define CURRENT_PLAYER 0
#define OTHER_PLAYER 1
#define NUM_K_CARDS 10
#define TRUE 1
#define MAX_STRING_LENGTH 32


/*******************************************************************************
**  Function: main
**  Description: Tests the Adventurer card effect on the state of the game.
*******************************************************************************/
int main() {

    struct gameState game, test;

    const int SEED = 100;
    int actionCards[NUM_K_CARDS] = {smithy, adventurer, salvager, steward, baron,
                                    village, minion, feast, embargo, outpost};

    const int CHOICE = 0;
    const int HAND_POS = 0;
    const int CARDS_DRAWN = 2;
    const int CARDS_PLAYED = 1;

    int bonus = 0;
    int tests = 0;
    int passed = 0;

    // Initialize the game to test
    initializeGame(NUM_PLAYERS, actionCards, SEED, &game);

    // Copy test instance
    memcpy(&test, &game, sizeof(struct gameState));

    cardEffect(adventurer, CHOICE, CHOICE, CHOICE, &test, HAND_POS, &bonus);

    printTestHeader(TEST_TYPE, TEST_CARD);

    // Check the effects the Adventurer card has on the game state for the current player.
    printf("\n* Testing Current Player Playing %s card...\n\n", TEST_CARD);
    testCurrentPlayerState(&game, &test, CURRENT_PLAYER,
                           (CARDS_DRAWN - CARDS_PLAYED),
                           (-CARDS_DRAWN), CARDS_PLAYED, NO_CHANGE, NO_CHANGE,
                           NO_CHANGE, NO_CHANGE, NO_CHANGE, &passed, &tests);

    // Check the effects the Adventurer card has on the game state for the other player.
    printf("\n* Testing Other Player...\n\n");
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

    // Verify both drawn cards where treasure cards.
    printf("\n* Testing Both cards drawn where treasure cards...\n\n");

    int i = 0;
    int j = test.handCount[CURRENT_PLAYER] - 3;

    while(i < 2 && j >= 0){

        char name[MAX_STRING_LENGTH];
        cardNumToName(test.hand[CURRENT_PLAYER][j + i], name);

        strcat(name, " Card Drawn");

        assertTrue(TRUE, (test.hand[CURRENT_PLAYER][j + i] == copper
                          || test.hand[CURRENT_PLAYER][j + i] == silver
                          || test.hand[CURRENT_PLAYER][j + i] == gold),
                name, &passed, &tests);
        i++;
    }

	// Check the effects the Adventurer card has on the game state for the
	// current player with no treasure cards to draw.
	printf("\n* Testing Current Player Playing %s card with NO treasure cards...\n\n", TEST_CARD);

	memcpy(&test, &game, sizeof(struct gameState));

	int deckScore = 0;

	// Get the deck score since values will be erased
	for (i = 0; i < test.deckCount[CURRENT_PLAYER]; i++) {

		if (test.deck[CURRENT_PLAYER][i] == curse) {
			deckScore = deckScore - 1;
		} else if (test.deck[CURRENT_PLAYER][i] == estate) {
			deckScore = deckScore + 1;
		} else if (test.deck[CURRENT_PLAYER][i] == duchy) {
			deckScore = deckScore + 3;
		} else if (test.deck[CURRENT_PLAYER][i] == province) {
			deckScore = deckScore + 6;
		} else if (test.deck[CURRENT_PLAYER][i] == great_hall) {
			deckScore = deckScore + 1;
		} else if (test.deck[CURRENT_PLAYER][i] == gardens) {
			deckScore = deckScore + ( fullDeckCount(CURRENT_PLAYER, 0, &test) / 10 );
		};
	}

	// Modify the players deck to remove any treasure cards.
	for(int i = 0; i < test.deckCount[CURRENT_PLAYER]; i++){
		test.deck[CURRENT_PLAYER][i] = smithy;
	}

	cardEffect(adventurer, CHOICE, CHOICE, CHOICE, &test, HAND_POS, &bonus);

	const int DISCARD_PILE = 5;

	testCurrentPlayerState(&game, &test, CURRENT_PLAYER, (-CARDS_PLAYED),
	                       (-DISCARD_PILE), CARDS_PLAYED, DISCARD_PILE,
	                       NO_CHANGE, NO_CHANGE, NO_CHANGE, (- deckScore),
	                       &passed, &tests);

    // Print Summary and Footer
    printTestSummary(passed, tests);
}




