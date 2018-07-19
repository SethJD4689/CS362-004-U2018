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

#define EQ(A, B) ((A) == (B))

void assertTrue(int expected, int actual, char *message, int *passed, int *tests);

void testCurrentPlayerState(struct gameState *game, struct gameState *test,
                            int player,
                            int hand, int deck, int played, int discard,
                            int coins, int buys, int actions, int score,
                            int *passed, int *tests);

void testOtherPlayerState(struct gameState *game, struct gameState *test,
                          int player, int hand, int deck, int discard,
                          int score, int *passed, int *tests);

void testTreasureCardPiles(struct gameState *game, struct gameState *test,
                           int copperChange, int silverChange, int goldChange,
                           int *passed, int *tests);

void testVictoryCardPiles(struct gameState *game, struct gameState *test,
                          int estateChange, int duchyChange, int provinceChange,
                          int *passed, int *tests);

void testKingdomCardPiles(struct gameState *game, struct gameState *test,
                          int actionCards[], int cardChanges[], int *passed,
                          int *tests);

void printTestSummary(int passed, int tests);

void printTestHeader(char type[], char name[]);

#endif //_TESTER_H
