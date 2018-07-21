/*******************************************************************************
** Assignment: CS362 - Assignment 3
** Filename: cardtest4.c
** Author: Seth Dovgan
** Date: 10 July 2017
**
** Description: Tests the Council Room Card.
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "tester.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CARD "Council Room"
#define TYPE "Card"
#define HAND_POS 4 		    // Position the Council Room card is in the players hand
#define CARDS_DRAWN 4 	    // Number of cards drawn by the Council Room card
#define CARDS_PLAYED 1 	    // Council Room card played
#define BUY_GAIN 1          // Buys gained playing Council Room card
#define OTHER_CARDS_DRAWN 1 // Cards drawn by other players

/*******************************************************************************
**  Function: main
**  Description: Tests the Council Room effect on the state of the game.
*******************************************************************************/
int main() {

    struct gameState game, test;

    int actionCards[NUM_K_CARDS] = {smithy, adventurer, salvager, steward, baron,
                                    village, minion, feast, embargo, outpost};

    int tests = 0;
    int passed = 0;

    // Initialize the game instance for the test
    initializeGame(NUM_PLAYERS, actionCards, SEED, &game);

    // Place Council Room card in hand
    game.hand[CURRENT_PLAYER][HAND_POS] = council_room;

    // Copy a test instance
    memcpy(&test, &game, sizeof(struct gameState));

    // Call Council Room function
    councilRoomCardEffect(&test, CURRENT_PLAYER, HAND_POS);

    // Print Test Header
    printTestHeader(CARD, TYPE);

    // Check the effects the Council Room card has on the game state for the current player.
    printf("\n* Testing Current Player Playing %s card...\n\n", CARD);
    testCurrentPlayerState(&game, &test, CURRENT_PLAYER,
                           (CARDS_DRAWN - CARDS_PLAYED),
                           (-CARDS_DRAWN), CARDS_PLAYED, NO_CHANGE, NO_CHANGE,
                           BUY_GAIN, NO_CHANGE, NO_CHANGE, council_room, &passed, &tests);

    // Check if the card was actually played
    testCardPlayed(&game, &test, CURRENT_PLAYER, HAND_POS, &passed, &tests);

    // Check the effects the Council Room has on the game state for the other player.
    printf("\n* Testing Other Player...\n\n");
    testOtherPlayerState(&game, &test, OTHER_PLAYER, OTHER_CARDS_DRAWN, (- OTHER_CARDS_DRAWN),
                         NO_CHANGE, NO_CHANGE, &passed, &tests);

    // Verify no victory card piles were effected.
    printf("\n* Testing Victory Card Piles...\n\n");
    testVictoryCardPilesNoChange(&game, &test, &passed, &tests);

    // Verify no treasure card piles were affected
    printf("\n* Testing Treasure Card Piles...\n\n");
    testTreasureCardPilesNoChange(&game, &test, &passed, &tests);

    // Verify no kingdom card piles were affected
    printf("\n* Testing Kingdom Card Piles...\n\n");
    testKingdomCardPilesNoChange(&game, &test, actionCards, &passed, &tests);

    // Print Test Summary
    printTestSummary(passed, tests);
}


