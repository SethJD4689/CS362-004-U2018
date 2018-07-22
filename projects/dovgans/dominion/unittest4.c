/*******************************************************************************
** Assignment: CS362 - Assignment 3
** Filename: unittest4.c
** Author: Seth Dovgan
** Date: 10 July 2017
**
** Description: Tests the fullDeckCount function.
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "tester.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FUNCTION "fullDeckCount"
#define TYPE "Function"
#define NO_CARD 0
#define SUPPLY_CARD_COUNT 17
#define CARD_IN_ALL 3

/*******************************************************************************
**  Function: testFullDeckCountForState
**  Description: tests for changes in the game state
*******************************************************************************/
void testFullDeckCountForState(struct gameState *game, struct gameState *test,
                               int actionCards[], int player, int *passed,
                               int *tests){

	printf("\n* Current Player Game State\n");
	testCurrentPlayerNoStateChange(game, test, player, passed, tests);

	printf("\n* Testing Other Player...\n\n");
	testOtherPlayerNoStateChange(game, test, OTHER_PLAYER, passed, tests);

	printf("\n* Testing Victory Card Piles...\n\n");
	testVictoryCardPilesNoChange(game, test, passed, tests);

	printf("\n* Testing Treasure Card Piles...\n\n");
	testTreasureCardPilesNoChange(game, test, passed, tests);

	printf("\n* Testing Kingdom Card Piles...\n\n");
	testKingdomCardPilesNoChange(game, test, actionCards, passed, tests);
}

/*******************************************************************************
**  Function: main
**  Description: tests the fullDeckCount function
*******************************************************************************/
int main() {

	struct gameState game, test;

	int actionCards[10] = {smithy, adventurer, salvager, steward, baron,
	                       village, minion, feast, embargo, outpost};

	int supplyCards[] = {curse, estate, duchy, province, copper, silver,
	                     gold, actionCards[0], actionCards[1], actionCards[2],
	                     actionCards[3], actionCards[4], actionCards[5],
	                     actionCards[6], actionCards[7], actionCards[8],
	                     actionCards[9]};

	int tests = 0;
	int passed = 0;

    // Initialize the game instance for the test
	initializeGame(NUM_PLAYERS, actionCards, SEED, &game);

    // Print Test Header
	printTestHeader(TYPE, FUNCTION);

	// Test all cards with no card in hand, deck or discards
	printf("\n# Testing %s function with no cards in hand, deck or discard...\n\n", TEST_FUNCTION);

	// Set test conditions
    game.handCount[CURRENT_PLAYER] = 0;
    game.handCount[OTHER_PLAYER] = 0;
    game.discardCount[CURRENT_PLAYER] = 0;
    game.discardCount[OTHER_PLAYER] = 0;
    game.deckCount[CURRENT_PLAYER] = 0;
    game.deckCount[OTHER_PLAYER] = 0;

    memcpy(&test, &game, sizeof(struct gameState));

    // Get the count of each card in the game for the player's
	for(int i = 0; i < SUPPLY_CARD_COUNT; i++){

		char title[100];

		char name[MAX_STRING_LENGTH];
		cardNumToName(supplyCards[i], name);

		snprintf(title, sizeof(title), "Count of %s card in player's deck", name);

		assertTrue(NO_CARD, fullDeckCount(CURRENT_PLAYER, supplyCards[i], &test),
		           title, &passed, &tests);

		snprintf(title, sizeof(title), "Count of %s card in other player's deck",
                 name);

		assertTrue(NO_CARD, fullDeckCount(OTHER_PLAYER, supplyCards[i], &test),
		           title, &passed, &tests);
	}

	// Test if the game state was unaltered
	testFullDeckCountForState(&game, &test, actionCards, CURRENT_PLAYER,
                              &passed, &tests);


	// Test all cards with no card in hand, deck or discards
	printf("\n# Testing %s function with card not in hand, deck or discard...\n\n", TEST_FUNCTION);

    // Set # of cards for the players
	game.handCount[CURRENT_PLAYER] = SUPPLY_CARD_COUNT;
	game.handCount[OTHER_PLAYER] = SUPPLY_CARD_COUNT;
	game.discardCount[CURRENT_PLAYER] = SUPPLY_CARD_COUNT;
	game.discardCount[OTHER_PLAYER] = SUPPLY_CARD_COUNT;
	game.deckCount[CURRENT_PLAYER] = SUPPLY_CARD_COUNT;
	game.deckCount[OTHER_PLAYER] = SUPPLY_CARD_COUNT;

	// Fill the player's hand with cards
	for(int i = 0; i < SUPPLY_CARD_COUNT; i++){

		game.hand[CURRENT_PLAYER][i] = supplyCards[i];
		game.hand[OTHER_PLAYER][i] = supplyCards[i];

		game.discard[CURRENT_PLAYER][i] = supplyCards[i];
		game.discard[OTHER_PLAYER][i] = supplyCards[i];

		game.deck[CURRENT_PLAYER][i] = supplyCards[i];
		game.deck[OTHER_PLAYER][i] = supplyCards[i];
	}

	// Check if the card doesn't exists in the deck
	for(int i = 0; i < SUPPLY_CARD_COUNT; i++){

		int tempHandPos = 0;
		int tempCard = 0;

		// Set card specific test condition by removing the card from the hand
		for(int j = 0; j < SUPPLY_CARD_COUNT; j++){

			if(game.hand[CURRENT_PLAYER][j] == game.hand[CURRENT_PLAYER][i]){

				tempHandPos = j;
				tempCard = game.hand[CURRENT_PLAYER][j];

                game.hand[CURRENT_PLAYER][j] = sea_hag;
                game.discard[CURRENT_PLAYER][j] = sea_hag;
                game.deck[CURRENT_PLAYER][j] = sea_hag;

                game.hand[OTHER_PLAYER][j] = sea_hag;
                game.discard[OTHER_PLAYER][j] = sea_hag;
                game.deck[OTHER_PLAYER][j] = sea_hag;
			}
		}

		char title[100];

		char name[MAX_STRING_LENGTH];
		cardNumToName(supplyCards[i], name);

		memcpy(&test, &game, sizeof(struct gameState));

		snprintf(title, sizeof(title), "Count of %s card in player's deck", name);

		assertTrue(NO_CARD, fullDeckCount(CURRENT_PLAYER, supplyCards[i], &test),
		           title, &passed, &tests);

		snprintf(title, sizeof(title), "Count of %s card in other player's deck",
                 name);

		assertTrue(NO_CARD, fullDeckCount(OTHER_PLAYER, supplyCards[i], &test),
		           title, &passed, &tests);

		// Put the removed card back into the player's hand before starting the next test
		game.hand[CURRENT_PLAYER][tempHandPos] = tempCard;
		game.discard[CURRENT_PLAYER][tempHandPos] = tempCard;
		game.deck[CURRENT_PLAYER][tempHandPos] = tempCard;

		game.hand[OTHER_PLAYER][tempHandPos] = tempCard;
		game.discard[OTHER_PLAYER][tempHandPos] = tempCard;
		game.deck[OTHER_PLAYER][tempHandPos] = tempCard;

        memcpy(&test, &game, sizeof(struct gameState));
	}

    // Test if the game state was unaltered
    testFullDeckCountForState(&game, &test, actionCards, CURRENT_PLAYER, &passed,
                              &tests);


    // Test all cards with card in hand, deck and discards
    printf("\n# Testing %s function with card in hand, deck and discard...\n\n", TEST_FUNCTION);

    // Test for each card in the deck
    for(int i = 0; i < SUPPLY_CARD_COUNT; i++){

        char title[100];

        char name[MAX_STRING_LENGTH];
        cardNumToName(supplyCards[i], name);

        snprintf(title, sizeof(title), "Count of %s card in player's deck", name);

        assertTrue(CARD_IN_ALL, fullDeckCount(CURRENT_PLAYER, supplyCards[i], &test),
                   title, &passed, &tests);

        snprintf(title, sizeof(title), "Count of %s card in other player's deck",
                 name);

        assertTrue(CARD_IN_ALL, fullDeckCount(OTHER_PLAYER, supplyCards[i], &test),
                   title, &passed, &tests);
    }

    // Test if the game state was unaltered
    testFullDeckCountForState(&game, &test, actionCards, CURRENT_PLAYER,
                              &passed, &tests);


    // Test all cards with multiple cards in hand, deck and discards
    printf("\n# Testing %s function with multiple cards in hand, deck and discard...\n\n", TEST_FUNCTION);

    // Set # of cards for the players
    game.handCount[CURRENT_PLAYER] = SUPPLY_CARD_COUNT * 2;
    game.handCount[OTHER_PLAYER] = SUPPLY_CARD_COUNT * 2;
    game.discardCount[CURRENT_PLAYER] = SUPPLY_CARD_COUNT * 2;
    game.discardCount[OTHER_PLAYER] = SUPPLY_CARD_COUNT * 2;
    game.deckCount[CURRENT_PLAYER] = SUPPLY_CARD_COUNT * 2;
    game.deckCount[OTHER_PLAYER] = SUPPLY_CARD_COUNT * 2;

    // Fill the player's decks with 2 cards each from the supply pile
    for(int i = 0; i < (SUPPLY_CARD_COUNT * 2); i++){

        if(i < SUPPLY_CARD_COUNT){

            game.hand[CURRENT_PLAYER][i] = supplyCards[i];
            game.hand[OTHER_PLAYER][i] = supplyCards[i];

            game.discard[CURRENT_PLAYER][i] = supplyCards[i];
            game.discard[OTHER_PLAYER][i] = supplyCards[i];

            game.deck[CURRENT_PLAYER][i] = supplyCards[i];
            game.deck[OTHER_PLAYER][i] = supplyCards[i];

        } else {

            game.hand[CURRENT_PLAYER][i] = supplyCards[i - SUPPLY_CARD_COUNT];
            game.hand[OTHER_PLAYER][i] = supplyCards[i - SUPPLY_CARD_COUNT];

            game.discard[CURRENT_PLAYER][i] = supplyCards[i - SUPPLY_CARD_COUNT];
            game.discard[OTHER_PLAYER][i] = supplyCards[i - SUPPLY_CARD_COUNT];

            game.deck[CURRENT_PLAYER][i] = supplyCards[i - SUPPLY_CARD_COUNT];
            game.deck[OTHER_PLAYER][i] = supplyCards[i - SUPPLY_CARD_COUNT];
        }
    }

    memcpy(&test, &game, sizeof(struct gameState));

    // Test for each card in the deck
    for(int i = 0; i < SUPPLY_CARD_COUNT; i++){

        char title[100];

        char name[MAX_STRING_LENGTH];
        cardNumToName(supplyCards[i], name);

        snprintf(title, sizeof(title), "Count of %s card in player's deck",
                 name);

        assertTrue(CARD_IN_ALL * 2, fullDeckCount(CURRENT_PLAYER, supplyCards[i], &test),
                   title, &passed, &tests);

        snprintf(title, sizeof(title), "Count of %s card in other player's deck",
                 name);

        assertTrue(CARD_IN_ALL * 2, fullDeckCount(OTHER_PLAYER, supplyCards[i], &test),
                   title, &passed, &tests);
    }

    // Test if the game state was unaltered
    testFullDeckCountForState(&game, &test, actionCards, CURRENT_PLAYER,
                              &passed, &tests);


	// Print the test summary
	printTestSummary(passed, tests);
}





















