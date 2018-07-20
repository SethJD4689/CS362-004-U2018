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
#include "interface.h"
#include "tester.h"
#include <string.h>
#include <stdio.h>

#define CARD "Adventurer"
#define TYPE "Card"
#define HAND_POS 0 		// Position the Adventurer card is in the players hand
#define CARDS_DRAWN 2 	// Number of cards drawn by the Adventurer card
#define CARDS_PLAYED 1 	// Adventurer card played

/*******************************************************************************
**  Function: main
**  Description: Tests the Adventurer card effect on the state of the game.
*******************************************************************************/
int main() {

    struct gameState game, test;

    int actionCards[NUM_K_CARDS] = {smithy, adventurer, salvager, steward, baron,
                                    village, minion, feast, embargo, outpost};

    int tests = 0;
    int passed = 0;

    // Initialize the game instance for the test
    initializeGame(NUM_PLAYERS, actionCards, SEED, &game);

    // Place Adventurer card in hand
    game.hand[CURRENT_PLAYER][HAND_POS] = adventurer;

    // Copy a test instance
    memcpy(&test, &game, sizeof(struct gameState));

    // Call Adventurer function
    adventurerCardEffect(&test, CURRENT_PLAYER);

    // Print Test Header
    printTestHeader(TYPE, CARD);

    // Check the effects the Adventurer card has on the game state for the current player.
    printf("\n* Testing Current Player Playing %s card...\n\n", CARD);
    testCurrentPlayerState(&game, &test, CURRENT_PLAYER,
                           (CARDS_DRAWN - CARDS_PLAYED),
                           (-CARDS_DRAWN), CARDS_PLAYED, NO_CHANGE, NO_CHANGE,
                           NO_CHANGE, NO_CHANGE, NO_CHANGE, adventurer, &passed, &tests);

    // Check if the card was actually played
    testCardPlayed(&game, &test, CURRENT_PLAYER, HAND_POS, &passed, &tests);

    // Check the effects the Adventurer card has on the game state for the other player.
    printf("\n* Testing Other Player...\n\n");
    testOtherPlayerNoStateChange(&game, &test, OTHER_PLAYER, &passed, &tests);

    // Verify no victory card piles were effected.
    printf("\n* Testing Victory Card Piles...\n\n");
    testVictoryCardPilesNoChange(&game, &test, &passed, &tests);

    // Verify no treasure card piles were affected
    printf("\n* Testing Treasure Card Piles...\n\n");
    testTreasureCardPilesNoChange(&game, &test, &passed, &tests);

    // Verify no kingdom card piles were affected
    printf("\n* Testing Kingdom Card Piles...\n\n");
    testKingdomCardPilesNoChange(&game, &test, actionCards, &passed, &tests);

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
	printf("\n* Testing Current Player Playing %s card with NO treasure cards...\n\n", CARD);

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

    // Call Adventurer function
    adventurerCardEffect(&game, CURRENT_PLAYER);

	const int DISCARD_PILE = 5;

	testCurrentPlayerState(&game, &test, CURRENT_PLAYER, (-CARDS_PLAYED),
	                       (-DISCARD_PILE), CARDS_PLAYED, DISCARD_PILE,
	                       NO_CHANGE, NO_CHANGE, NO_CHANGE, (- deckScore), adventurer,
	                       &passed, &tests);

    // Print Summary and Footer
    printTestSummary(passed, tests);
}




