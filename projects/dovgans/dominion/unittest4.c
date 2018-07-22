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

#define NO_CARD 0
#define SUPPLY_CARD_COUNT 17

/*
int fullDeckCount(int player, int card, struct gameState *state) {
	int i;
	int count = 0;

	for (i = 0; i < state->deckCount[player]; i++)
	{
		if (state->deck[player][i] == card) count++;
	}

	for (i = 0; i < state->handCount[player]; i++)
	{
		if (state->hand[player][i] == card) count++;
	}

	for (i = 0; i < state->discardCount[player]; i++)
	{
		if (state->discard[player][i] == card) count++;
	}

	return count;
}*/

/*******************************************************************************
**  Function:
**  Description:
*******************************************************************************/
void testFullDeckCountForState(struct gameState *game, struct gameState *test,
                               int actionCards[], int player, int *passed,
                               int *tests){

	//printf("* Card Deck Count\n");
	//assertTrue(fullDeckCount(player, card, test), deckCount, "Count of Card in Player's Deck:", passed, tests);

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

int removeCardFromHand(){
	
}

int removeCardFromDeck(){

}

int removeCardFromDiscard(){

}

/*******************************************************************************
**  Function:
**  Description:
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
	int score;

	// Initialize test game
	initializeGame(NUM_PLAYERS, actionCards, SEED, &game);

	printTestHeader(TEST_TYPE, TEST_FUNCTION);

	game.handCount[CURRENT_PLAYER] = 0;
	game.handCount[OTHER_PLAYER] = 0;
	game.discardCount[CURRENT_PLAYER] = 0;
	game.discardCount[OTHER_PLAYER] = 0;
	game.deckCount[CURRENT_PLAYER] = 0;
	game.deckCount[OTHER_PLAYER] = 0;


	memcpy(&test, &game, sizeof(struct gameState));

	// Test all cards with no card in hand, deck or discards
	printf("\n# Testing %s function with no cards in hand, deck or discard...\n\n", TEST_FUNCTION);

	for(int i = 0; i < SUPPLY_CARD_COUNT; i++){

		char title[100];

		char name[MAX_STRING_LENGTH];
		cardNumToName(supplyCards[i], name);

		snprintf(title, sizeof(title), "Count of %s card in player's deck", name);

		assertTrue(fullDeckCount(CURRENT_PLAYER, supplyCards[i], &test), NO_CARD,
		           title, &passed, &tests);

		snprintf(title, sizeof(title), "Count of %s card in other player's deck", name);

		assertTrue(fullDeckCount(OTHER_PLAYER, supplyCards[i], &test), NO_CARD,
		           title, &passed, &tests);
	}

	testFullDeckCountForState(&game, &test, actionCards, CURRENT_PLAYER, &passed, &tests);

	// Test all cards with no card in hand, deck or discards
	printf("\n# Testing %s function with card not in hand, deck or discard...\n\n", TEST_FUNCTION);


	game.handCount[CURRENT_PLAYER] = SUPPLY_CARD_COUNT;
	game.handCount[OTHER_PLAYER] = SUPPLY_CARD_COUNT;
	game.discardCount[CURRENT_PLAYER] = SUPPLY_CARD_COUNT;
	game.discardCount[OTHER_PLAYER] = SUPPLY_CARD_COUNT;
	game.deckCount[CURRENT_PLAYER] = SUPPLY_CARD_COUNT;
	game.deckCount[OTHER_PLAYER] = SUPPLY_CARD_COUNT;

	for(int i = 0; i < SUPPLY_CARD_COUNT; i++){

		game.hand[CURRENT_PLAYER][i] = supplyCards[i];
		game.hand[OTHER_PLAYER][i] = supplyCards[i];

		game.discard[CURRENT_PLAYER][i] = supplyCards[i];
		game.discard[OTHER_PLAYER][i] = supplyCards[i];

		game.deck[CURRENT_PLAYER][i] = supplyCards[i];
		game.deck[OTHER_PLAYER][i] = supplyCards[i];
	}

	printHand(CURRENT_PLAYER, &game);

	for(int i = 0; i < SUPPLY_CARD_COUNT; i++){

		int tempHandPos = 0;
		int tempCard = 0;

		for(int j = 0; j < SUPPLY_CARD_COUNT; j++){

			if(game.hand[CURRENT_PLAYER][j] == game.hand[CURRENT_PLAYER][i]){

				tempHandPos = j;
				tempCard = game.hand[CURRENT_PLAYER][j];

				if(j == SUPPLY_CARD_COUNT - 1){

					game.hand[CURRENT_PLAYER][j] = game.hand[CURRENT_PLAYER][j - 1];
					game.discard[CURRENT_PLAYER][j] = game.discard[CURRENT_PLAYER][j - 1];
					game.deck[CURRENT_PLAYER][j] = game.deck[CURRENT_PLAYER][j - 1];

					game.hand[OTHER_PLAYER][j] = game.hand[OTHER_PLAYER][j - 1];
					game.discard[OTHER_PLAYER][j] = game.discard[OTHER_PLAYER][j - 1];
					game.deck[OTHER_PLAYER][j] = game.deck[OTHER_PLAYER][j - 1];

					printf("If - %d\n", j);

				} else {

					game.hand[CURRENT_PLAYER][j] = game.hand[CURRENT_PLAYER][j + 1];
					game.discard[CURRENT_PLAYER][j] = game.discard[CURRENT_PLAYER][j + 1];
					game.deck[CURRENT_PLAYER][j] = game.deck[CURRENT_PLAYER][j + 1];

					game.hand[OTHER_PLAYER][j] = game.hand[OTHER_PLAYER][j + 1];
					game.discard[OTHER_PLAYER][j] = game.discard[OTHER_PLAYER][j + 1];
					game.deck[OTHER_PLAYER][j] = game.deck[OTHER_PLAYER][j + 1];

					printf("Else - %d\n", j);
				}
			}
		}

		char title[100];

		char name[MAX_STRING_LENGTH];
		cardNumToName(supplyCards[i], name);

		printHand(CURRENT_PLAYER, &game);

		memcpy(&test, &game, sizeof(struct gameState));

		snprintf(title, sizeof(title), "Count of %s card in player's deck", name);

		assertTrue(NO_CARD, fullDeckCount(CURRENT_PLAYER, supplyCards[i], &test),
		           title, &passed, &tests);

		snprintf(title, sizeof(title), "Count of %s card in other player's deck", name);

		assertTrue(NO_CARD, fullDeckCount(OTHER_PLAYER, supplyCards[i], &test),
		           title, &passed, &tests);

		game.hand[CURRENT_PLAYER][tempHandPos] = tempCard;
		game.discard[CURRENT_PLAYER][tempHandPos] = tempCard;
		game.deck[CURRENT_PLAYER][tempHandPos] = tempCard;

		game.hand[OTHER_PLAYER][tempHandPos] = tempCard;
		game.discard[OTHER_PLAYER][tempHandPos] = tempCard;
		game.deck[OTHER_PLAYER][tempHandPos] = tempCard;
	}


	/*
	 * No card in hand, deck or discard
	 * Card not in hand;
	 * Card in only in hand
	 * Card in only in deck
	 * Card in only in discard
	 * Card in hand, deck and discard
	 * Multiple cards in hand, deck and discard
	 */




	/*
	printf("\n# Testing %s function with score in deck, hand and discard...\n\n", TEST_FUNCTION);

	score = 0;

	game.handCount[CURRENT_PLAYER] = 6;
	game.hand[CURRENT_PLAYER][0] = curse;
	game.hand[CURRENT_PLAYER][1] = estate;
	game.hand[CURRENT_PLAYER][2] = duchy;
	game.hand[CURRENT_PLAYER][3] = province;
	game.hand[CURRENT_PLAYER][4] = great_hall;
	game.hand[CURRENT_PLAYER][5] = gardens;

	score += CURSE + ESTATE + DUCHY + PROVINCE + GREAT_HALL
	         + fullDeckCount(CURRENT_PLAYER, 0, &game) / 10;

	game.discardCount[CURRENT_PLAYER] = 1;
	game.discard[CURRENT_PLAYER][0] = estate;

	score += ESTATE;

	game.deckCount[CURRENT_PLAYER] = 6;
	game.deck[CURRENT_PLAYER][0] = curse;
	game.deck[CURRENT_PLAYER][1] = estate;
	game.deck[CURRENT_PLAYER][2] = duchy;
	game.deck[CURRENT_PLAYER][3] = province;
	game.deck[CURRENT_PLAYER][4] = great_hall;
	game.deck[CURRENT_PLAYER][5] = gardens;

	score += CURSE + ESTATE + DUCHY + PROVINCE + GREAT_HALL
	         + fullDeckCount(CURRENT_PLAYER, 0, &game) / 10;

	memcpy(&test, &game, sizeof(struct gameState));

	testScoreForState(&game, &test, actionCards, CURRENT_PLAYER, score, &passed,
	                  &tests);

	printf("\n# Testing %s function with score cards in hand only...\n\n", TEST_FUNCTION);

	score = 0;

	game.handCount[CURRENT_PLAYER] = 6;
	game.hand[CURRENT_PLAYER][0] = curse;
	game.hand[CURRENT_PLAYER][1] = estate;
	game.hand[CURRENT_PLAYER][2] = duchy;
	game.hand[CURRENT_PLAYER][3] = province;
	game.hand[CURRENT_PLAYER][4] = great_hall;
	game.hand[CURRENT_PLAYER][5] = gardens;

	score += CURSE + ESTATE + DUCHY + PROVINCE + GREAT_HALL
	         + fullDeckCount(CURRENT_PLAYER, 0, &game) / 10;

	game.discardCount[CURRENT_PLAYER] = 1;
	game.discard[CURRENT_PLAYER][0] = smithy;

	game.deckCount[CURRENT_PLAYER] = 6;
	game.deck[CURRENT_PLAYER][0] = adventurer;
	game.deck[CURRENT_PLAYER][1] = minion;
	game.deck[CURRENT_PLAYER][2] = feast;
	game.deck[CURRENT_PLAYER][3] = embargo;
	game.deck[CURRENT_PLAYER][4] = outpost;
	game.deck[CURRENT_PLAYER][5] = village;

	memcpy(&test, &game, sizeof(struct gameState));

	testScoreForState(&game, &test, actionCards, CURRENT_PLAYER, score, &passed,
	                  &tests);

	printf("\n# Testing %s function with score cards in deck only...\n\n", TEST_FUNCTION);

	score = 0;

	game.handCount[CURRENT_PLAYER] = 6;
	game.hand[CURRENT_PLAYER][0] = adventurer;
	game.hand[CURRENT_PLAYER][1] = minion;
	game.hand[CURRENT_PLAYER][2] = feast;
	game.hand[CURRENT_PLAYER][3] = embargo;
	game.hand[CURRENT_PLAYER][4] = outpost;
	game.hand[CURRENT_PLAYER][5] = village;

	game.discardCount[CURRENT_PLAYER] = 1;
	game.discard[CURRENT_PLAYER][0] = smithy;

	game.deckCount[CURRENT_PLAYER] = 6;
	game.deck[CURRENT_PLAYER][0] = curse;
	game.deck[CURRENT_PLAYER][1] = estate;
	game.deck[CURRENT_PLAYER][2] = duchy;
	game.deck[CURRENT_PLAYER][3] = province;
	game.deck[CURRENT_PLAYER][4] = great_hall;
	game.deck[CURRENT_PLAYER][5] = gardens;

	score += CURSE + ESTATE + DUCHY + PROVINCE + GREAT_HALL
	         + fullDeckCount(CURRENT_PLAYER, 0, &game) / 10;

	memcpy(&test, &game, sizeof(struct gameState));

	testScoreForState(&game, &test, actionCards, CURRENT_PLAYER, score, &passed,
	                  &tests);

	printf("\n# Testing %s function with score cards in discard only...\n\n", TEST_FUNCTION);

	score = 0;

	game.handCount[CURRENT_PLAYER] = 6;
	game.hand[CURRENT_PLAYER][0] = minion;
	game.hand[CURRENT_PLAYER][1] = minion;
	game.hand[CURRENT_PLAYER][2] = feast;
	game.hand[CURRENT_PLAYER][3] = embargo;
	game.hand[CURRENT_PLAYER][4] = outpost;
	game.hand[CURRENT_PLAYER][5] = village;

	game.discardCount[CURRENT_PLAYER] = 1;
	game.discard[CURRENT_PLAYER][0] = province;

	game.deckCount[CURRENT_PLAYER] = 6;
	game.deck[CURRENT_PLAYER][0] = smithy;
	game.deck[CURRENT_PLAYER][1] = adventurer;
	game.deck[CURRENT_PLAYER][2] = smithy;
	game.deck[CURRENT_PLAYER][3] = village;
	game.deck[CURRENT_PLAYER][4] = outpost;
	game.deck[CURRENT_PLAYER][5] = feast;

	score += PROVINCE;

	memcpy(&test, &game, sizeof(struct gameState));

	testScoreForState(&game, &test, actionCards, CURRENT_PLAYER, score, &passed,
	                  &tests);

	*/

	// Print the test summary
	printTestSummary(passed, tests);

}





















