/*******************************************************************************
** Assignment: CS362 - Assignment 3
** Filename: cardtest3.c
** Author: Seth Dovgan
** Date: 10 July 2017
**
** Description: Tests the Salvager Card.
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "tester.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CARD "Salvager"
#define TYPE "Card"
#define NO_TRASH_OPTION -1   // No Card is Trashed Option
#define CARDS_PLAYED 1      // Salavager card played
#define CARDS_TRASHED 1     // Number of Card trashed using Salvager card
#define EXTRA_BUY 1         // Extra buys granted by Salvager card
#define HAND_POS 0

/*******************************************************************************
**  Function: getScoreForCard
**  Description: Returns the score for a specified card.
*******************************************************************************/
int getScoreForCard(struct gameState *game, int player, int card){

    int score = 0;

    if (card == curse) {
        score = score - 1;
    } else if (card == estate) {
        score = score + 1;
    } else if (card == duchy) {
        score = score + 3;
    } else if (card == province) {
        score = score + 6;
    } else if (card == great_hall) {
        score = score + 1;
    } else if (card == gardens) {
        score = score + ( fullDeckCount(player, 0, game) / 10 );
    };

    return score;
}

/*******************************************************************************
**  Function: main
**  Description: Tests the Salvager card effect on the state of the game.
*******************************************************************************/
int main() {

    struct gameState game, test, base;

    int actionCards[10] = {smithy, adventurer, salvager, steward, baron,
                           village, minion, feast, embargo, outpost};

    int tests = 0;
    int passed = 0;

    // Initialize the game instance for the test
    initializeGame(NUM_PLAYERS, actionCards, SEED, &base);

    // Print Test Header
    printTestHeader(TYPE, CARD);

    memcpy(&game, &base, sizeof(struct gameState));

    // Test trashing each card in the players hand
    for(int trashPos = 0; trashPos < game.handCount[CURRENT_PLAYER]; trashPos++){

        int salvagerPos;
        int previousCard;

        // Make sure the trash card is not the salvager card
        if(trashPos < game.handCount[CURRENT_PLAYER] - 1){

            salvagerPos = trashPos + 1;
            previousCard = game.hand[CURRENT_PLAYER][salvagerPos];
            game.hand[CURRENT_PLAYER][salvagerPos] = salvager;

        } else {

            salvagerPos = trashPos - 1;
            previousCard = game.hand[CURRENT_PLAYER][salvagerPos];
            game.hand[CURRENT_PLAYER][salvagerPos] = salvager;
        }

        // Copy a test instance
        memcpy(&test, &game, sizeof(struct gameState));

        // Check the effects the Salvager card has on the game state for the current player.
        printf("\n* Testing Current Player Playing %s card using trash option for card %d...\n\n", CARD, trashPos);

        // Call Salvager function
        salvagerCardEffect(&test, CURRENT_PLAYER, salvagerPos, trashPos);

        testCurrentPlayerState(&game, &test, CURRENT_PLAYER,
                               (- CARDS_PLAYED - CARDS_TRASHED), NO_CHANGE,
                               CARDS_PLAYED, NO_CHANGE,
                               getCost(handCard(trashPos, &game)), EXTRA_BUY,
                               NO_CHANGE, (- getScoreForCard(&game, CURRENT_PLAYER, game.hand[CURRENT_PLAYER][trashPos])),
                               salvager, &passed, &tests);

        // Check if the card was actually played
        testCardPlayed(&game, &test, CURRENT_PLAYER, salvagerPos, &passed, &tests);

        // Check the effects the Smithy card has on the game state for the other player.
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

        memcpy(&game, &base, sizeof(struct gameState));
    }

    printf("\n* Testing Current Player Playing %s card NOT using trash option...\n\n", CARD);

    // Setup test condition
    game.handCount[CURRENT_PLAYER] = 1;
    game.hand[CURRENT_PLAYER][HAND_POS] = salvager;

    // Copy a test instance
    memcpy(&test, &game, sizeof(struct gameState));

    // Call Salvager function
    salvagerCardEffect(&test, CURRENT_PLAYER, HAND_POS, NO_TRASH_OPTION);

	testCurrentPlayerState(&game, &test, CURRENT_PLAYER,
	                       (- CARDS_PLAYED), NO_CHANGE,
	                       CARDS_PLAYED, NO_CHANGE, NO_CHANGE, EXTRA_BUY,
	                       NO_CHANGE, NO_CHANGE, salvager, &passed, &tests);

    // Check if the card was actually played
    testCardPlayed(&game, &test, CURRENT_PLAYER, HAND_POS, &passed, &tests);

    // Check the effects the Smithy card has on the game state for the other player.
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


    printTestSummary(passed, tests);
}




