/*******************************************************************************
** Assignment: CS362 - Assignment 3
** Filename: tester.c
** Author: Seth Dovgan
** Date: 16 July 2017
**
** Description: Testing helper functions
*******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"

#define EQ(A, B) ((A) == (B))
#define NO_CHANGE 0
#define NUM_PLAYERS 2
#define MAX_PLAYERS 4
#define MIN_PLAYERS 2
#define SEED 100
#define NUM_A_CARDS 20

/*******************************************************************************
**  Function: assertTrue
**  Description: compares to values for equality and prints a PASS or FAIL
** 	message to the console.
**
**  param: int expected - expected value to compare against
**	param: int actual - actual value compared with
**	param: char *message - message to display in test results
**  param: int *passed - tracks passed tests
**	param: int *tests - tracks tests conducted
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
**  Function: compareCards
**  Description: compares each card in a hand, deck or discard for changes.
**
**  param: int game[][MAX_DECK] - deck, hand or discard to compare against
**	param: int gameCount - number of cards in the deck hand or discard
**	param: int test[][MAX_DECK] - deck, hand or discard to compare with
**  param: int testCount - number of cards in the deck hand or discard
**	param: int player - for the deck hand or discard
**	param: char name[] - deck, hand or discard
**  param: int *passed - tracks passed tests
**	param: int *tests - tracks tests conducted
*******************************************************************************/
void compareCards(int game[][MAX_DECK], int gameCount, int test[][MAX_DECK],
				  int testCount, int player, char name[], int *passed,
				  int *tests) {

	for(int i = 0; i < gameCount && i < testCount; i++){

		char card1[MAX_STRING_LENGTH];
		cardNumToName(game[player][i], card1);

		char card2[MAX_STRING_LENGTH];
		cardNumToName(test[player][i], card2);

		if (EQ(game[player][i], test[player][i])) {

			printf("- PASSED: %s Card %d - %s, expected = %s\n", name, i,
				   card2, card1);

			(*passed)++;

		} else {

			printf("- FAILED: %s Card %d - %s, expected = %s\n", name, i,
				   card2, card1);
		}

		(*tests)++;
	}
}

/*******************************************************************************
**  Function: testCurrentPlayerState
**  Description: tests the game state changes occurred with the current player
** 	in the game.
**
**  param: struct gameState *game - game state to compare against
**	param: struct gameState *test - game state to compare with
**	param: int player - player used in testing
**	param: int hand - changes to the player's hand count
**	param: int deck - changes to the player's deck count
**	param: int played - changes to the player's played card count
**	param: int discard - changes to the player's discard count
**	param: int coins - changes to the player's coins
**	param: int buys - changes to the player's number of buys
**	param: int actions - changes to the player's number of actions
**	param: int score - changes to the players score
**  param: int *passed - tracks passed tests
**	param: int *tests - tracks tests conducted
*******************************************************************************/
void testCurrentPlayerState(struct gameState *game, struct gameState *test,
                            int player, int hand, int deck, int played,
                            int discard, int coins, int buys, int actions,
                            int score, int card, int *passed, int *tests) {

	// Test changes to the player's hand
	assertTrue(game->handCount[player] + hand,
	           test->handCount[player],
	           "Cards in Hand", passed, tests);


	// Test changes to the player's deck
	assertTrue(game->deckCount[player] + deck,
	           test->deckCount[player],
	           "Cards in Deck", passed, tests);

	// Test changes to the cards played
	assertTrue(game->playedCardCount + played,
	           test->playedCardCount,
	           "Cards Played", passed, tests);

	// Test changes to the discard pile
	assertTrue(game->discardCount[player] + discard,
	           test->discardCount[player],
	           "Discard Pile", passed, tests);

	// Test changes to the coins remaining
	assertTrue(game->coins + coins, test->coins,
	           "Coins Remaining", passed, tests);

	// Test changes to the remaining buys
	assertTrue(game->numBuys + buys, test->numBuys,
	           "Buys Remaining", passed, tests);

	// Test changes to the remaining action cards
	assertTrue(game->numActions + actions, test->numActions,
	           "Actions Remaining", passed, tests);

	// Test is outpost was played
	assertTrue(game->outpostPlayed, test->outpostPlayed,
	           "Outpost Played", passed, tests);

	// Test changes to the score
	assertTrue(scoreFor(player, game) + score,
	           scoreFor(player, test),
	           "Player Score", passed, tests);
}

/*******************************************************************************
**  Function: testCardPlayed
**  Description: Tests if the played card was actually played and placed in the
**  played pile.
**
**  param: struct gameState *game - game state to compare against
**	param: struct gameState *test - game state to compare with
**	param: int player - player used in testing
**	param: int card - card played
**	param: int handPos - position the card was in before being played
**  param: int *passed - tracks passed tests
**	param: int *tests - tracks tests conducted
*******************************************************************************/
void testCardPlayed(struct gameState *game, struct gameState *test, int player,
					int handPos, int *passed, int *tests){

	char eName[MAX_STRING_LENGTH];
	cardNumToName(game->hand[player][handPos], eName);

	if(test->playedCardCount > 0){

		char aName[MAX_STRING_LENGTH];
        cardNumToName(test->playedCards[test->playedCardCount - 1], aName);

		if (game->hand[player][handPos]
			== test->playedCards[test->playedCardCount - 1]) {

			printf("PASSED: Card Played = %s, expected = %s\n", aName, eName);

			(*passed)++;

		} else {

			printf("FAILED: Card Played = %s, expected = %s\n", aName, eName);
		}

		(*tests)++;

	} else {

		printf("FAILED: Card Played = none, expected = %s\n", eName);
		(*tests)++;
	}
}

/*******************************************************************************
**  Function: testCurrentPlayerNoStateChange
**  Description: tests if no game state changes occurred with the current player
** 	in the game.
**
**  param: struct gameState *game - game state to compare against
**	param: struct gameState *test - game state to compare with
**	param: int player - player used in testing
**  param: int *passed - tracks passed tests
**	param: int *tests - tracks tests conducted
*******************************************************************************/
void testCurrentPlayerNoStateChange(struct gameState *game, struct gameState *test,
                                    int player, int *passed, int *tests){

	// Test changes to the player's hand
	assertTrue(game->handCount[player], test->handCount[player],
			   "Cards in Hand", passed, tests);

	// Compare each card in player's hand
	compareCards(game->hand, game->handCount[player], test->hand,
				 test->handCount[player], player, "Hand", passed, tests);

	// Test changes to the player's deck
	assertTrue(game->deckCount[player], test->deckCount[player],
			   "Cards in Deck", passed, tests);

	// Compare each card in player's deck
	compareCards(game->deck, game->deckCount[player], test->deck,
				 test->deckCount[player], player, "Deck", passed, tests);

	// Test changes to the cards played
	assertTrue(game->playedCardCount, test->playedCardCount,
			   "Cards Played", passed, tests);

	// Test changes to the discard pile
	assertTrue(game->discardCount[player], test->discardCount[player],
			   "Discard Pile", passed, tests);

	// Compare each card in player's discard
	compareCards(game->discard, game->discardCount[player], test->discard,
				 test->discardCount[player], player, "Discard", passed, tests);

	// Test changes to the coins remaining
	assertTrue(game->coins, test->coins, "Coins Remaining", passed, tests);

	// Test changes to the remaining buys
	assertTrue(game->numBuys, test->numBuys, "Buys Remaining", passed, tests);

	// Test changes to the remaining action cards
	assertTrue(game->numActions, test->numActions, "Actions Remaining",
			   passed, tests);

	// Test is outpost was played
	assertTrue(game->outpostPlayed, test->outpostPlayed,
			   "Outpost Played", passed, tests);

	// Test changes to the score
	assertTrue(scoreFor(player, game), scoreFor(player, test), "Player Score",
			   passed, tests);
}

/*******************************************************************************
**  Function: testOtherPlayerState
**  Description: tests the game state changes occurred with an other player in
** 	the game.
**
**  param: struct gameState *game - game state to compare against
**	param: struct gameState *test - game state to compare with
**	param: int player - player used in testing
**	param: int hand - changes to the hand count
**	param: int deck - changes to the deck count
**	param: int discard - changes to the discard count
**	param: int score - changes to the player score
**  param: int *passed - tracks passed tests
**	param: int *tests - tracks tests conducted
*******************************************************************************/
void testOtherPlayerState(struct gameState *game, struct gameState *test,
		                  int player, int hand, int deck, int discard,
		                  int score, int *passed, int *tests) {

	// Test changes to the player's hand
	assertTrue(game->handCount[player] + hand,
	           test->handCount[player],
	           "Cards in Hand", passed, tests);

	// Compare each card in player's hand
	compareCards(game->hand, game->handCount[player], test->hand,
				 test->handCount[player], player, "Hand", passed, tests);

	// Test changes to the player's deck
	assertTrue(game->deckCount[player] + deck,
	           test->deckCount[player],
	           "Cards in Deck", passed, tests);

	// Compare each card in player's deck
	compareCards(game->deck, game->deckCount[player], test->deck,
				 test->deckCount[player], player, "Deck", passed, tests);

	// Test changes to the discard pile
	assertTrue(game->discardCount[player] + discard,
	           test->discardCount[player],
	           "Discard Pile", passed, tests);

	// Compare each card in player's discard
	compareCards(game->discard, game->discardCount[player], test->discard,
				 test->discardCount[player], player, "Discard", passed, tests);

	// Test changes to the score
	assertTrue(scoreFor(player, game) + score,
	           scoreFor(player, test),
	           "Player Score", passed, tests);
}

/*******************************************************************************
**  Function: testOtherPlayerNoStateChange
**  Description: tests if no game state changes occurred with an other player in
** 	the game.
**
**  param: struct gameState *game - game state to compare against
**	param: struct gameState *test - game state to compare with
**	param: int player - player used in testing
**  param: int *passed - tracks passed tests
**	param: int *tests - tracks tests conducted
*******************************************************************************/
void testOtherPlayerNoStateChange(struct gameState *game, struct gameState *test,
                                  int player, int *passed, int *tests) {

	testOtherPlayerState(game, test, player, NO_CHANGE, NO_CHANGE, NO_CHANGE,
						 NO_CHANGE, passed, tests);
}

/*******************************************************************************
**  Function: testKingdomCardPiles
**  Description: Checks the kingdom pile modifications, prints the
**  results to the console and updates the test trackers
**
**  param: struct gameState *game - game state to compare against
**	param: struct gameState *test - game state to compare with
**	param: int actionCards[] - action cards used in the game
**	param: int cardChanges[] - changes to the action card supply
**  param: int *passed - tracks passed tests
**	param: int *tests - tracks tests conducted
*******************************************************************************/
void testKingdomCardPiles(struct gameState *game, struct gameState *test,
		int actionCards[], int cardChanges[], int *passed, int *tests){

	for(int i = 0; i < NUM_K_CARDS; i++){

		char name[MAX_STRING_LENGTH];
		cardNumToName(actionCards[i], name);

		strcat(name, " Cards Remaining");

		assertTrue(supplyCount(actionCards[i], game) + cardChanges[i],
		           supplyCount(actionCards[i], test),
		           name, passed, tests);
	}
}

/*******************************************************************************
**  Function: testKingdomCardPilesNoChange
**  Description: Check if the kingdom card piles were modified or not, prints
**  the results to the console and updates the test trackers.
**
**  param: struct gameState *game - game state to compare against
**	param: struct gameState *test - game state to compare with
**	param: int actionCards[] - action cards used in the game
**  param: int *passed - tracks passed tests
**	param: int *tests - tracks tests conducted
*******************************************************************************/
void testKingdomCardPilesNoChange(struct gameState *game, struct gameState *test,
                                  int actionCards[], int *passed, int *tests){

	int cardChanges[NUM_K_CARDS];

	// Make no changes to all the cards
	for(int i = 0; i < NUM_K_CARDS; i++){

		cardChanges[i] = NO_CHANGE;
	}

	testKingdomCardPiles(game, test, actionCards, cardChanges, passed, tests);
}

/*******************************************************************************
**  Function: testVictoryCardPiles
**  Description: Checks the victory pile modifications, prints the
**  results to the console and updates the test trackers
**
**  param: struct gameState *game - game state to compare against
**	param: struct gameState *test - game state to compare with
**	param: int copperChange - changes to the copper supply
**	param: int silverChange - changes to the silver supply
**	param: int goldChange - changes to the gold supply
**  param: int *passed - tracks passed tests
**	param: int *tests - tracks tests conducted
*******************************************************************************/
void testVictoryCardPiles(struct gameState *game, struct gameState *test,
                          int estateChange, int duchyChange, int provinceChange,
                          int *passed, int *tests){

	assertTrue(supplyCount(estate, game) + estateChange,
	           supplyCount(estate, test),
	           "Estate Cards Remaining", passed, tests);

	assertTrue(supplyCount(duchy, game) + duchyChange,
	           supplyCount(duchy, test),
	           "Duchy Cards Remaining", passed, tests);

	assertTrue(supplyCount(province, game) + provinceChange,
	           supplyCount(province, test),
	           "Province Cards Remaining", passed, tests);
}

/*******************************************************************************
**  Function: testVictoryCardPilesNoChange
**  Description: Check if the victory card piles were modified or not, prints
**  the results to the console and updates the test trackers.
**
**  param: struct gameState *game - game state to compare against
**	param: struct gameState *test - game state to compare with
**  param: int *passed - tracks passed tests
**	param: int *tests - tracks tests conducted
*******************************************************************************/
void testVictoryCardPilesNoChange(struct gameState *game, struct gameState *test,
								  int *passed, int *tests){

	testVictoryCardPiles(game, test, NO_CHANGE, NO_CHANGE, NO_CHANGE, passed,
						 tests);
}

/*******************************************************************************
**  Function: testTreasureCardPiles
**  Description: Checks the treasure card pile modifications, prints the
**  results to the console and updates the test trackers
**
**  param: struct gameState *game - game state to compare against
**	param: struct gameState *test - game state to compare with
**	param: int copperChange - changes to the copper supply
**	param: int silverChange - changes to the silver supply
**	param: int goldChange - changes to the gold supply
**  param: int *passed - tracks passed tests
**	param: int *tests - tracks tests conducted
*******************************************************************************/
void testTreasureCardPiles(struct gameState *game, struct gameState *test,
		                   int copperChange, int silverChange, int goldChange,
		                   int *passed, int *tests){

	assertTrue(supplyCount(copper, game) + copperChange, supplyCount(copper, test),
	           "Copper Cards Remaining", passed, tests);

	assertTrue(supplyCount(silver, game) + silverChange, supplyCount(silver, test),
	           "Silver Cards Remaining", passed, tests);

	assertTrue(supplyCount(gold, game) + goldChange, supplyCount(gold, test),
	           "Gold Cards Remaining", passed, tests);
}

/*******************************************************************************
**  Function: testTreasureCardPilesNoChange
**  Description: Check if the treasure card piles was modified or not, prints
**  the results to the console and updates the test trackers.
**
**  param: struct gameState *game - game state to compare against
**	param: struct gameState *test - game state to compare with
**  param: int *passed - tracks passed tests
**	param: int *tests - tracks tests conducted
*******************************************************************************/
void testTreasureCardPilesNoChange(struct gameState *game, struct gameState *test,
								   int *passed, int *tests){

	testTreasureCardPiles(game, test, NO_CHANGE, NO_CHANGE, NO_CHANGE, passed,
	                      tests);
}

/*******************************************************************************
**  Function: printTestHeader
**  Description: Prints a test heading that includes the name and type.
**
**  param: char type[] - type of test conducted.
**	param: char name[] - name of test conducted.
*******************************************************************************/
void printTestHeader(char type[], char name[]){

	printf("\n>>> Testing %s: %s >>>\n", type, name);
}

/*******************************************************************************
**  Function: printTestSummary
**  Description: Prints a summary of the total tests conducted on a function
**	including number of passed and failed.
**
**  param: int passed - number of tests that passed.
**	param: int tests - number of total tests conducted.
*******************************************************************************/
void printTestSummary(int passed, int tests){

	printf("\n>>> Summary >>>\n\nTests Conducted = %d, PASSED = %d, "
		   "FAILED = %d\n\n", tests, passed, (tests - passed));
}

int* generateRandomActionCards(){

	int actionCards[NUM_A_CARDS] = {adventurer, council_room, feast, gardens, mine,
						 remodel, smithy, village, baron, great_hall, minion,
						 steward, tribute, ambassador, cutpurse, embargo,
						 outpost, salvager, sea_hag, treasure_map};

	int* cards = malloc(10 * sizeof(int));
	int i = 0;

	while(i < NUM_K_CARDS){

		int randomCardIndex = rand() % NUM_A_CARDS;

		if(actionCards[randomCardIndex] != -1){

			cards[i] = actionCards[randomCardIndex];
			actionCards[randomCardIndex] = -1;
			i++;
		}
	}

	return cards;
}

int getTotalCardsInSupply(struct gameState *game){

	int count = 0;

	for(int i = 0; i <= game->supplyCount[treasure_map]; i++){

		count = count + game->supplyCount[i];
	}

	return count;

}

void generateRandomGameState(struct gameState *game){

	int allCards[] = {curse, estate, duchy, province, copper, silver, gold,
				      adventurer, council_room, feast, gardens, mine,
	                  remodel, smithy, village, baron, great_hall, minion,
	                  steward, tribute, ambassador, cutpurse, embargo,
	                  outpost, salvager, sea_hag, treasure_map};

	game = newGame();

	// Generate random # of players
	int numberOfPlayers = rand() % (MAX_PLAYERS - MIN_PLAYERS) + MIN_PLAYERS;

	printf("# of players%d\n", numberOfPlayers);

	// Generate random action cards
	int *cards = generateRandomActionCards();

	// Initialize the game instance for the test
	initializeGame(numberOfPlayers, cards, SEED, game);

	// Randomly select the first player
	game->whoseTurn = rand() % numberOfPlayers;

	int deck = 0;

	// Get a count for all cards in the game
	for(int i = 0; i < 27; i++){

		int supply = supplyCount(allCards[i], game);

		if(supply >= 0){
			deck += supply;
		}
	}

	deck += numberOfPlayers * 10;   // add the cards in the players hand

	int remainingDeck = deck;

	// Randomly assign deck counts
	// Randomly assign decks
	// Randomly assign discard for selected player
	// Randomly assign hands for selected player
	// All must be less than deck

	for(int i = 0; i < 5000; i++){

		if(remainingDeck <= 0 || remainingDeck >= deck){
			printf("Remaining Deck: %d\n", remainingDeck);
		}

		remainingDeck = rand() % (deck + 1);
	}

	// Randomly assign deck counts
	for(int i = 0; i < numberOfPlayers; i++){

		remainingDeck -= rand() % (remainingDeck + 1);
		game->deckCount[i] = remainingDeck;
	}

	//for(int i = 0; )




	//printf("Remaining Deck: %d\n", remainingDeck);

	//game->deckCount[game->whoseTurn] = remainingDeck;

	// Set the other player's deck hand and discard
			/*
	for(int i = 0; i < numberOfPlayers; i++){

		int temp = rand() % (remainingDeck + 1);
		game->deckCount[i] = temp;
		remainingDeck -= temp;
		//printf("Remaining Deck: %d\n", remainingDeck);

		game->handCount[i] = 0;
		game->discardCount[i] = 0;
	}

	int totalCardCount = 0;

	for(int i = 0; i < numberOfPlayers; i++){

		totalCardCount += game->deckCount[i];
	}

	if(totalCardCount <= 0 || totalCardCount < MAX_HAND){
		printf("Total Card Count: %d\n", totalCardCount);
	}*/

	//int totalDeck =
	/*
	for(int i = 0; i < game->numPlayers; i++){

		printf("Player %d deckCount = %d\n", i, game->deckCount[i]);
		printf("Player %d handCount = %d\n", i, game->handCount[i]);
		printf("Player %d discardCount = %d\n", i, game->discardCount[i]);
	}*/



	//printf("Supply Count = %d\n", getTotalCardsInSupply(game));

	/*
	game->handCount[game->whoseTurn] = rand() % game->deckCount[game->whoseTurn];

	//Moved draw cards to here, only drawing at the start of a turn
	for (int i = 0; i < game->handCount[game->whoseTurn]; i++){
		drawCard(game->whoseTurn, game);
	}

	updateCoins(game->whoseTurn, game, 0);*/
}


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



/*
int* kingdomCards(int k1, int k2, int k3, int k4, int k5, int k6, int k7,
				  int k8, int k9, int k10) {
	int* k = malloc(10 * sizeof(int));
	k[0] = k1;
	k[1] = k2;
	k[2] = k3;
	k[3] = k4;
	k[4] = k5;
	k[5] = k6;
	k[6] = k7;
	k[7] = k8;
	k[8] = k9;
	k[9] = k10;
	return k;
}*/


int generateRandomHand(struct gameState *game, int player, int max, const int actionCards[]){

	game->handCount[player] = max;

	for(int i = 0; i < max; i++){

		game->hand[player][i] = actionCards[rand() % max];
	}
}


int generateRandomDecks(struct gameState *game, int max, const int actionCards[]){


	int remainingDeck = max;

	// Assign random
	for(int i = 0; i < game->numPlayers; i++){

		int numberOfCards = rand() % (remainingDeck + 1);

		remainingDeck -= numberOfCards;
		game->deckCount[i] = numberOfCards;
	}

	for(int i = 0; i < game->numPlayers; i++){

	}

	return remainingDeck;
}

void generateRandomDiscards(struct gameState *game, int player, int max, const int actionCards[]){

	game->discardCount[player] = max;

	for(int i = 0; i < max; i++){

		game->discard[player][i] = actionCards[rand() % max];
	}
}

void generateRandomPlayedCards(struct gameState *game, int max, int actionCards[]){

	game->playedCardCount = max;

	for(int i = 0; i < max; i++){

		game->playedCards[i] = actionCards[rand() % max];
	}
}


/*
struct gameState {
	int numPlayers; //number of players
	int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
	int embargoTokens[treasure_map+1];
	int outpostPlayed;
	int outpostTurn;
	int whoseTurn;
	int phase;*/
	//int numActions; /* Starts at 1 each turn */
	//int coins; /* Use as you see fit! */
	//int numBuys; /* Starts at 1 each turn */
	//int hand[MAX_PLAYERS][MAX_HAND];
	//int handCount[MAX_PLAYERS];
	//int deck[MAX_PLAYERS][MAX_DECK];
	//int deckCount[MAX_PLAYERS];
	//int discard[MAX_PLAYERS][MAX_DECK];
	//int discardCount[MAX_PLAYERS];
	//int playedCards[MAX_DECK];
	//int playedCardCount;
//};

