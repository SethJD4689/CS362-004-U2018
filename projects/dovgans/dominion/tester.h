//
// Created by Seth Dovgan on 7/17/18.
//

#ifndef _TESTER_H
#define _TESTER_H

#define TEST_FUNCTION "scoreFor"
#define TEST_TYPE "Function"
#define NUM_PLAYERS 2
#define CURRENT_PLAYER 0
#define OTHER_PLAYER 1
#define NO_CHANGE 0
#define NUM_K_CARDS 10
#define SEED 100
#define MAX_STRING_LENGTH 32


#define EQ(A, B) ((A) == (B))

void assertTrue(int expected, int actual, char *message, int *passed, int *tests);

void testCurrentPlayerState(struct gameState *game, struct gameState *test,
							int player, int hand, int deck, int played,
							int discard, int coins, int buys, int actions,
							int score, int card, int *passed, int *tests);

void testCardPlayed(struct gameState *game, struct gameState *test, int player,
					int handPos, int *passed, int *tests);

void testCurrentPlayerNoStateChange(struct gameState *game, struct gameState *test,
                                    int player, int *passed, int *tests);

void testOtherPlayerState(struct gameState *game, struct gameState *test,
                          int player, int hand, int deck, int discard,
                          int score, int *passed, int *tests);

void testOtherPlayerNoStateChange(struct gameState *game, struct gameState *test,
                          int player, int *passed, int *tests);

void testTreasureCardPiles(struct gameState *game, struct gameState *test,
                           int copperChange, int silverChange, int goldChange,
                           int *passed, int *tests);

void testTreasureCardPilesNoChange(struct gameState *game, struct gameState *test,
	int *passed, int *tests);

void testVictoryCardPiles(struct gameState *game, struct gameState *test,
                          int estateChange, int duchyChange, int provinceChange,
                          int *passed, int *tests);

void testVictoryCardPilesNoChange(struct gameState *game, struct gameState *test,
                          int *passed, int *tests);

void testKingdomCardPiles(struct gameState *game, struct gameState *test,
                          int actionCards[], int cardChanges[], int *passed,
                          int *tests);

void testKingdomCardPilesNoChange(struct gameState *game, struct gameState *test,
                          int actionCards[], int *passed, int *tests);

void compareCards(int game[][MAX_DECK], int gameCount, int test[][MAX_DECK],
				  int testCount, int player, char name[], int *passed, int *tests);

void printTestSummary(int passed, int tests);

void printTestHeader(char type[], char name[]);

#endif //_TESTER_H
