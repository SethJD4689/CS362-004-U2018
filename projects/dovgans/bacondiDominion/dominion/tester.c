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
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"

#define EQ(A, B) ((A) == (B))
#define NO_CHANGE 0
#define NUM_PLAYERS 2
#define MAX_PLAYERS 4
#define MIN_PLAYERS 2
#define SEED 100
#define NUM_A_CARDS 20
#define NUM_ALL_CARDS 27
#define LIMIT_PRINT 1

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

		if(LIMIT_PRINT){
			printf("PASSED: %s = %d, expected = %d\n", message, actual, expected);
		}
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

			if(LIMIT_PRINT){
				printf("   - PASSED: %s Card %d - %s, expected = %s\n", name, i,
				       card2, card1);
			}

			(*passed)++;

		} else {

			printf("   - FAILED: %s Card %d - %s, expected = %s\n", name, i,
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
                            int score, int *passed, int *tests) {

	char title[100];

	// Test changes to the player's hand
	sprintf(title, "Current Player %d - Cards in Hand", player);
	assertTrue(game->handCount[player] + hand,
	           test->handCount[player],
	           title, passed, tests);

	// Test changes to the player's deck
	sprintf(title, "Current Player %d - Cards in Deck", player);
	assertTrue(game->deckCount[player] + deck,
	           test->deckCount[player],
	           title, passed, tests);

	// Test changes to the cards played
	sprintf(title, "Current Player %d - Cards Played", player);
	assertTrue(game->playedCardCount + played,
	           test->playedCardCount,
	           title, passed, tests);

	// Test changes to the discard pile
	sprintf(title, "Current Player %d - Discard Pile", player);
	assertTrue(game->discardCount[player] + discard,
	           test->discardCount[player],
	           title, passed, tests);

	// Test changes to the coins remaining
	sprintf(title, "Current Player %d - Coins Remaining", player);
	assertTrue(game->coins + coins, test->coins,
	           title, passed, tests);

	// Test changes to the remaining buys
	sprintf(title, "Current Player %d - Buys Remaining", player);
	assertTrue(game->numBuys + buys, test->numBuys,
	           title, passed, tests);

	// Test changes to the remaining action cards
	sprintf(title, "Current Player %d - Actions Remaining", player);
	assertTrue(game->numActions + actions, test->numActions,
	           title, passed, tests);

	// Test is outpost was played
	sprintf(title, "Current Player %d - Outpost Played", player);
	assertTrue(game->outpostPlayed, test->outpostPlayed,
	           title, passed, tests);

	// Test changes to the score
	sprintf(title, "Current Player %d - Score", player);
	assertTrue(scoreFor(player, game) + score,
	           scoreFor(player, test),
	           title, passed, tests);
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
void testCurrentPlayerStateModified(struct gameState *game, struct gameState *test,
									int player, int hand, int played, int coins,
                                    int buys, int actions, int score,
                                    int *passed, int *tests) {

	char title[100];

	// Test changes to the player's hand
	sprintf(title, "Current Player %d - Cards in Hand", player);
	assertTrue(game->handCount[player] + hand,
	           test->handCount[player],
	           title, passed, tests);

	// Test changes to the cards played
	sprintf(title, "Current Player %d - Cards Played", player);
	assertTrue(game->playedCardCount + played,
	           test->playedCardCount,
	           title, passed, tests);

	// Test changes to the coins remaining
	sprintf(title, "Current Player %d - Coins Remaining", player);
	assertTrue(game->coins + coins, test->coins,
	           title, passed, tests);

	// Test changes to the remaining buys
	sprintf(title, "Current Player %d - Buys Remaining", player);
	assertTrue(game->numBuys + buys, test->numBuys,
	           title, passed, tests);

	// Test changes to the remaining action cards
	sprintf(title, "Current Player %d - Actions Remaining", player);
	assertTrue(game->numActions + actions, test->numActions,
	           title, passed, tests);

	// Test is outpost was played
	sprintf(title, "Current Player %d - Outpost Played", player);
	assertTrue(game->outpostPlayed, test->outpostPlayed,
	           title, passed, tests);

	// Test changes to the score
	sprintf(title, "Current Player %d - Score", player);
	assertTrue(scoreFor(player, game) + score,
	           scoreFor(player, test),
	           title, passed, tests);
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

			if(LIMIT_PRINT){
				printf("PASSED: Current Player %d - Card Played = %s, expected = %s\n", player, aName, eName);
			}

			(*passed)++;

		} else {

			printf("FAILED: Current Player %d - Card Played = %s, expected = %s\n", player, aName, eName);
		}

		(*tests)++;

	} else {

		printf("FAILED: Current Player %d - Card Played = none, expected = %s\n", player, eName);
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

	testCurrentPlayerState(game, test, player, NO_CHANGE, NO_CHANGE, NO_CHANGE,
	                       NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE,
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

	char title[100];

	// Test changes to the player's hand
	sprintf(title, "Player %d Cards in Hand", player);
	assertTrue(game->handCount[player] + hand,
	           test->handCount[player],
	           title, passed, tests);

	// Compare each card in player's hand
	sprintf(title, "Player %d Hand", player);
	compareCards(game->hand, game->handCount[player], test->hand,
				 test->handCount[player], player, title, passed, tests);

	// Test changes to the player's deck
	sprintf(title, "Player %d Cards in Deck", player);
	assertTrue(game->deckCount[player] + deck,
	           test->deckCount[player],
	           title, passed, tests);

	// Compare each card in player's deck
	sprintf(title, "Player %d Deck", player);
	compareCards(game->deck, game->deckCount[player], test->deck,
				 test->deckCount[player], player, title, passed, tests);

	// Test changes to the discard pile
	sprintf(title, "Player %d Cards in Discard Pile", player);
	assertTrue(game->discardCount[player] + discard,
	           test->discardCount[player],
	           title, passed, tests);

	// Compare each card in player's discard
	sprintf(title, "Player %d Discard", player);
	compareCards(game->discard, game->discardCount[player], test->discard,
				 test->discardCount[player], player, title, passed, tests);

	// Test changes to the score
	sprintf(title, "Player %d Score", player);
	assertTrue(scoreFor(player, game) + score,
	           scoreFor(player, test),
	           title, passed, tests);
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

	if(LIMIT_PRINT){
		printf("###------------------------------------------------------------"
		 "--------------###\n");
		printf("###    Testing %s: %s \n", type, name);
		printf("###------------------------------------------------------------"
		 "--------------###\n");
	} else {
		printf("###------------------------------------------------------------"
		 "--------------###\n");
		printf("###   Testing %s: %s (Showing Fail Results Only)\n", type, name);
		printf("###------------------------------------------------------------"
		 "--------------###\n\n");
	}
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

	if(passed == tests && !LIMIT_PRINT){
		printf("\nAll Tests Passed\n");
	}

	printf("\n>>> Summary >>>\n\nTests Conducted = %d, PASSED = %d, "
	       "FAILED = %d\n\n", tests, passed, (tests - passed));
}


/*******************************************************************************
**  Function: generateRandomActionCards
**  Description: Randomly selects the action cards for the game and returns
**  the selected cards
**
**  return:	randomly selected action cards
*******************************************************************************/
int* generateRandomActionCards(int playedCard){

	int actionCards[NUM_A_CARDS] = {adventurer, council_room, feast, gardens, mine,
									remodel, smithy, village, baron, great_hall, minion,
									steward, tribute, ambassador, cutpurse, embargo,
									outpost, salvager, sea_hag, treasure_map};

	int* cards = malloc(NUM_A_CARDS * sizeof(int));
	int i = 0;

	while(i < NUM_A_CARDS - 1){

		int randomCardIndex = rand() % NUM_A_CARDS;

		if(actionCards[randomCardIndex] != -1){

			cards[i] = actionCards[randomCardIndex];
			actionCards[randomCardIndex] = -1;
			i++;
		}
	}

	cards[i] = playedCard;

	return cards;
}


/*******************************************************************************
**  Function: getTotalCardsInGame
**  Description: Returns the total number of cards present in the game.
**
**  return:	randomly selected action cards
*******************************************************************************/
int getTotalCardsInGame(struct gameState *game, int allCards[]){

	int deck = 0; // Count of all cards in the game

	// Get a count for all cards in the supply piles
	for(int i = 0; i < NUM_ALL_CARDS; i++){

		int supply = supplyCount(allCards[i], game);

		if(supply > 0){

			deck += supply;
		}
	}

	// Get a count for all cards in the player's hand, deck and discard
	for(int i = 0; i < game->numPlayers; i++){

		deck += game->deckCount[i];
		deck += game->discardCount[i];
		deck += game->handCount[i];
	}

	return deck;
}


/*******************************************************************************
**  Function: randomlyAssignDiscards
**  Description: Randomly assigns cards in each of the player's deck.
**
**  param:	struct gameState *game - game state to randomly assign decks to
**	param:  int allCards[] - all possible cards in the game
**	param:	int totalCards - number of cards in the game
**
**  return:	total number of cards assigned to all the players
*******************************************************************************/
int randomlyAssignDeck(struct gameState *game, int deck[][MAX_DECK],
	                   int deckCount[], int allCards[], int totalCards){

	SelectStream(1);
	PutSeed(time(NULL));

	double random = Random();
	int remainingDeck = floor(random * totalCards);
	int totalDeckCount = 0;

	// Randomly assign deck counts
	for(int i = 0; i < game->numPlayers; i++){

		int count = rand() % (remainingDeck + 1);
		deckCount[i] = count;
		totalDeckCount += deckCount[i];
		remainingDeck = remainingDeck - count;
	}

	// Randomly assign deck
	for(int i = 0; i < game->numPlayers; i++){

		int cardsInDeck = 0;

		while(cardsInDeck < deckCount[i]){

			int randomCard = rand() % 27;

			if(game->supplyCount[allCards[randomCard]] > 0){

				deck[i][cardsInDeck] = allCards[randomCard];
				game->supplyCount[allCards[randomCard]]--;

				cardsInDeck++;
			}
		}
	}

	return totalDeckCount;
}


/*******************************************************************************
**  Function: generateRandomGameState
**  Description: Randomly generates a game state with varying players, cards
**	deck, discard and hand counts.
**
**  param:	struct gameState *game - game state to randomly generate
**	param:  int played card - card to be played/tested
**	param:	int *handPos - position the card will be randomly placed
**
**  return:	total number of cards assigned to all the players
*******************************************************************************/
int* generateRandomGameState(struct gameState *game, int playedCard, int *handPos){

	int allCards[] = {curse, estate, duchy, province, copper, silver, gold,
				      adventurer, council_room, feast, gardens, mine,
	                  remodel, smithy, village, baron, great_hall, minion,
	                  steward, tribute, ambassador, cutpurse, embargo,
	                  outpost, salvager, sea_hag, treasure_map};

	// Generate random # of players
	int numberOfPlayers = rand() % (MAX_PLAYERS - 1) + MIN_PLAYERS;

	// Generate random action cards
	int *cards = generateRandomActionCards(playedCard);

	// Initialize the game instance for the test
	initializeGame(numberOfPlayers, cards, SEED, game);

	// Randomly select the first player
	game->whoseTurn = rand() % numberOfPlayers;

	// Add deck cards to the supply
	game->supplyCount[estate] += 3 * numberOfPlayers;
	game->supplyCount[copper] += 7 * numberOfPlayers;

	// Zero out all cards in play before randomly assigning cards
	for (int i = 0; i < game->numPlayers; i++) {

		game->deckCount[i] = 0;
		game->handCount[i] = 0;
		game->discardCount[i] = 0;
	}

	int remainingCards = getTotalCardsInGame(game, allCards);

	// Randomly assign deck cards
	remainingCards -= randomlyAssignDeck(game, game->deck, game->deckCount,
		                                 allCards, remainingCards);

	// Randomly assign discard cards
	randomlyAssignDeck(game, game->discard, game->discardCount,
		                                 allCards, remainingCards);

	int cardsToDraw = 0;

	// Get total cards in deck
	if(game->deckCount[game->whoseTurn] > 0){

		cardsToDraw += rand() % game->deckCount[game->whoseTurn];
	}

	// Get total cards in discard
	if(game->discardCount[game->whoseTurn] > 0){

		cardsToDraw += rand() % game->discardCount[game->whoseTurn];
	}

	// Randomly assign hand cards
	// Place the played card in hand since, no cards can be drawn
	if(game->deckCount[game->whoseTurn] == 0
	   && game->discardCount[game->whoseTurn] == 0){

		game->handCount[game->whoseTurn] = 1;
		game->hand[game->whoseTurn][0] = playedCard;
		(*handPos) = 0;

	} else { // Draw cards from the deck and discard

		// Draw cards from the deck and discard, since some are available
		if(cardsToDraw > 0){

			while(cardsToDraw > 0){

				drawCard(game->whoseTurn, game);
				cardsToDraw--;
			}

			(*handPos) = rand() % game->handCount[game->whoseTurn];
			game->hand[game->whoseTurn][(*handPos)] = playedCard;

		} else { // Place the played card in hand since, no cards are drawn

			game->handCount[game->whoseTurn] = 1;
			game->hand[game->whoseTurn][0] = playedCard;
			(*handPos) = 0;
		}
	}

	return cards;
}