/*******************************************************************************
** Assignment: CS362 - Assignment 3
** Filename: cardtest1.c
** Author: Seth Dovgan
** Date: 10 July 2017
**
** Description: Tests the Smithy Card.
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TEST_CARD "Steward"
#define NUM_PLAYERS 2
#define CURRENT_PLAYER 0
#define OTHER_PLAYER 1

#define MAX_STRING_LENGTH 32
#define TRUE 1
#define FALSE 0

#ifndef EQ
#define EQ(A, B) ((A) == (B))
#endif


/*******************************************************************************
**  Function: assertTrue
**  Description:
**
**  param:
**	param:
**
**	pre:
**	post:
**	post:
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

    const int HAND_POS = 0;
    const int CARDS_DRAWN = 2;
    const int CARDS_PLAYED = 1;
    const int COIN_GAIN = 2;
    const int TRASHED_CARDS = 2;

    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;

    int bonus = 0;
    int tests = 0;
    int passed = 0;

    // Initialize test game
    initializeGame(NUM_PLAYERS, actionCards, SEED, &game);


    printf("\n-------------------- Testing Card: %s --------------------\n", TEST_CARD);


    printf("\n# Testing Current Player Playing %s card with drawn card option...\n\n", TEST_CARD);

    choice1 = 1;
    memcpy(&test, &game, sizeof(struct gameState));
    cardEffect(steward, choice1, choice2, choice3, &test, HAND_POS, &bonus);

    // Test changes to the current players hand
    assertTrue(game.handCount[CURRENT_PLAYER] + CARDS_DRAWN - CARDS_PLAYED,
               test.handCount[CURRENT_PLAYER], "Cards in Hand", &passed, &tests);

    // Test changes to the current players deck
    assertTrue(game.deckCount[CURRENT_PLAYER] - CARDS_DRAWN,
               test.deckCount[CURRENT_PLAYER], "Cards in Deck", &passed, &tests);

    // Test changes to the cards played
    assertTrue(game.playedCardCount + CARDS_PLAYED,
               test.playedCardCount, "Cards Played", &passed, &tests);

    // Test changes to the discard pile
    assertTrue(game.discardCount[CURRENT_PLAYER],
               test.discardCount[CURRENT_PLAYER], "Discard Pile", &passed, &tests);

    // Test changes to the coins remaining
    assertTrue(game.coins, test.coins, "Coins Remaining", &passed, &tests);

    // Test changes to the remaining buys
    assertTrue(game.numBuys, test.numBuys, "Buys Remaining", &passed, &tests);

    // Test changes to the remaining action cards
    assertTrue(game.numActions, test.numActions, "Actions Remaining", &passed, &tests);

    // Test is outpost was played
    assertTrue(game.outpostPlayed, test.outpostPlayed, "Outpost Played", &passed, &tests);

    // Test changes to the score
    assertTrue(scoreFor(CURRENT_PLAYER, &game),
               scoreFor(CURRENT_PLAYER, &test), "Player Score", &passed, &tests);

    choice1 = 0;
    choice2 = 2;
    memcpy(&test, &game, sizeof(struct gameState));
    cardEffect(steward, choice1, choice2, choice3, &test, HAND_POS, &bonus);

    printf("\n# Testing Current Player Playing %s card with coin gain option...\n\n", TEST_CARD);

    // Test changes to the current players hand
    assertTrue(game.handCount[CURRENT_PLAYER] - CARDS_PLAYED,
               test.handCount[CURRENT_PLAYER], "Cards in Hand", &passed, &tests);

    // Test changes to the current players deck
    assertTrue(game.deckCount[CURRENT_PLAYER],
               test.deckCount[CURRENT_PLAYER], "Cards in Deck", &passed, &tests);

    // Test changes to the cards played
    assertTrue(game.playedCardCount + CARDS_PLAYED,
               test.playedCardCount, "Cards Played", &passed, &tests);

    // Test changes to the discard pile
    assertTrue(game.discardCount[CURRENT_PLAYER],
               test.discardCount[CURRENT_PLAYER], "Discard Pile", &passed, &tests);

    // Test changes to the coins remaining
    assertTrue(game.coins + COIN_GAIN, test.coins, "Coins Remaining", &passed, &tests);

    // Test changes to the remaining buys
    assertTrue(game.numBuys, test.numBuys, "Buys Remaining", &passed, &tests);

    // Test changes to the remaining action cards
    assertTrue(game.numActions, test.numActions, "Actions Remaining", &passed, &tests);

    // Test is outpost was played
    assertTrue(game.outpostPlayed, test.outpostPlayed, "Outpost Played", &passed, &tests);

    // Test changes to the score
    assertTrue(scoreFor(CURRENT_PLAYER, &game),
               scoreFor(CURRENT_PLAYER, &test), "Player Score", &passed, &tests);

    choice1 = 3;
    choice2 = 0;
    choice3 = 0;

    memcpy(&test, &game, sizeof(struct gameState));
    cardEffect(steward, choice1, choice2, choice3, &test, HAND_POS, &bonus);

    printf("\n# Testing Current Player Playing %s card with trash card option...\n\n", TEST_CARD);

    // Test changes to the current players hand
    assertTrue(game.handCount[CURRENT_PLAYER] - CARDS_PLAYED - TRASHED_CARDS,
               test.handCount[CURRENT_PLAYER], "Cards in Hand", &passed, &tests);

    // Test changes to the current players deck
    assertTrue(game.deckCount[CURRENT_PLAYER],
               test.deckCount[CURRENT_PLAYER], "Cards in Deck", &passed, &tests);

    // Test changes to the cards played
    assertTrue(game.playedCardCount + CARDS_PLAYED + TRASHED_CARDS,
               test.playedCardCount, "Cards Played", &passed, &tests);

    // Test changes to the discard pile
    assertTrue(game.discardCount[CURRENT_PLAYER],
               test.discardCount[CURRENT_PLAYER], "Discard Pile", &passed, &tests);

    // Test changes to the coins remaining
    assertTrue(game.coins, test.coins, "Coins Remaining", &passed, &tests);

    // Test changes to the remaining buys
    assertTrue(game.numBuys, test.numBuys, "Buys Remaining", &passed, &tests);

    // Test changes to the remaining action cards
    assertTrue(game.numActions, test.numActions, "Actions Remaining", &passed, &tests);

    // Test is outpost was played
    assertTrue(game.outpostPlayed, test.outpostPlayed, "Outpost Played", &passed, &tests);

    // Test changes to the score
    assertTrue(scoreFor(CURRENT_PLAYER, &game),
               scoreFor(CURRENT_PLAYER, &test), "Player Score", &passed, &tests);


    printf("\n# Testing Other Player...\n\n");

    // Test changes to the current players hand
    assertTrue(game.handCount[OTHER_PLAYER],
               test.handCount[OTHER_PLAYER], "Cards in Hand", &passed, &tests);

    // Test changes to the current players deck
    assertTrue(game.deckCount[OTHER_PLAYER],
               test.deckCount[OTHER_PLAYER], "Cards in Deck", &passed, &tests);

    // Test changes to the discard pile
    assertTrue(game.discardCount[OTHER_PLAYER],
               test.discardCount[OTHER_PLAYER], "Discard Pile", &passed, &tests);

    assertTrue(scoreFor(OTHER_PLAYER, &game),
               scoreFor(OTHER_PLAYER, &test), "Player Score", &passed, &tests);


    printf("\n# Testing Victory Card Piles...\n\n");

    assertTrue(supplyCount(estate, &game), supplyCount(estate, &test),
               "Estate Cards Remaining", &passed, &tests);

    assertTrue(supplyCount(duchy, &game), supplyCount(duchy, &test),
               "Duchy Cards Remaining", &passed, &tests);

    assertTrue(supplyCount(province, &game), supplyCount(province, &test),
               "Province Cards Remaining", &passed, &tests);


    printf("\n# Testing Treasure Card Piles...\n\n");

    assertTrue(supplyCount(copper, &game), supplyCount(copper, &test),
               "Copper Cards Remaining", &passed, &tests);

    assertTrue(supplyCount(silver, &game), supplyCount(silver, &test),
               "Silver Cards Remaining", &passed, &tests);

    assertTrue(supplyCount(gold, &game), supplyCount(gold, &test),
               "Gold Cards Remaining", &passed, &tests);



    printf("\n# Testing Kingdom Card Piles...\n\n");

    for(int i = 0; i < sizeof(actionCards) / sizeof(int); i++){

        char name[MAX_STRING_LENGTH];
        cardNumToName(actionCards[i], name);

        strcat(name, " Cards Remaining");

        assertTrue(supplyCount(actionCards[i], &game), supplyCount(actionCards[i], &test),
                   name, &passed, &tests);
    }

    printf("\n# Summary\n\nTests Conducted = %d, PASSED = %d, FAILED = %d\n",
           tests, passed, (tests - passed));

    printf("\n--------------------------------------------------------------\n");

}



