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
**  Function: testDrawnTreasureCards
**  Description: Tests if both drawn cards are treasure cards
*******************************************************************************/
void testDrawnTreasureCards(struct gameState test, int player, int *passed,
                            int *tests){

    // Verify both drawn cards were treasure cards.
    printf("\n* Testing both cards drawn were treasure cards...\n\n");

    int i = 0;
    int j = test.handCount[player] - 3;

    if(j <= 1){
        assertTrue(FALSE, TRUE, "No treasure card", passed, tests);
    }

    if (j <= 0){
        assertTrue(FALSE, TRUE, "No treasure card", passed, tests);
    }

    while(i < 2 && j >= 0){

        char name[MAX_STRING_LENGTH];
        cardNumToName(test.hand[CURRENT_PLAYER][j + i], name);

        strcat(name, " Card Drawn");

        assertTrue(TRUE, (test.hand[CURRENT_PLAYER][j + i] == copper
                          || test.hand[CURRENT_PLAYER][j + i] == silver
                          || test.hand[CURRENT_PLAYER][j + i] == gold),
                   name, passed, tests);
        i++;
    }
}

/*******************************************************************************
**  Function: testGameState
**  Description: Tests the entire gameState
*******************************************************************************/
void testGameState(struct gameState game, struct gameState test, int actionCards[], int hand,
                   int deck, int played, int discard, int *passed, int *tests){

    // Call Adventurer function
    adventurerEffect(&test);

    // Test the state of the game
    testCurrentPlayerState(&game, &test, CURRENT_PLAYER, hand, deck, played,
                           discard, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE,
                           passed, tests);

    // Check if the card was actually played
    testCardPlayed(&game, &test, CURRENT_PLAYER, HAND_POS, passed, tests);

    // Check the effects the Adventurer card has on the game state for the other player.
    printf("\n* Testing Other Player...\n\n");
    testOtherPlayerNoStateChange(&game, &test, OTHER_PLAYER, passed, tests);

    // Verify no victory card piles were effected.
    printf("\n* Testing Victory Card Piles...\n\n");
    testVictoryCardPilesNoChange(&game, &test, passed, tests);

    // Verify no treasure card piles were affected
    printf("\n* Testing Treasure Card Piles...\n\n");
    testTreasureCardPilesNoChange(&game, &test, passed, tests);

    // Verify no kingdom card piles were affected
    printf("\n* Testing Kingdom Card Piles...\n\n");
    testKingdomCardPilesNoChange(&game, &test, actionCards, passed, tests);

    testDrawnTreasureCards(test, CURRENT_PLAYER, passed, tests);
}

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
    game.whoseTurn = CURRENT_PLAYER;

    // Print Test Header
    printTestHeader(TYPE, CARD);

    // Check the effects the Adventurer card has on the game state for the current player.
    printf("\n* Testing Current Player Playing %s card with treasure cards at top of deck...\n\n", CARD);

    // Place Adventurer card in hand and place treasure card at top of deck
    game.hand[CURRENT_PLAYER][HAND_POS] = adventurer;
    game.deck[CURRENT_PLAYER][game.deckCount[CURRENT_PLAYER] - 1] = copper;
    game.deck[CURRENT_PLAYER][game.deckCount[CURRENT_PLAYER] - 2] = silver;

    // Copy a test instance
    memcpy(&test, &game, sizeof(struct gameState));

    // Run test case
    testGameState(game, test, actionCards, (CARDS_DRAWN - CARDS_PLAYED),
                  (-CARDS_DRAWN), CARDS_PLAYED, NO_CHANGE, &passed, &tests);


    // Check the effects the Adventurer card has on the game state for the current player.
    printf("\n* Testing Current Player Playing %s card with treasure cards at bottom of deck...\n\n", CARD);

    const int DECK_CHANGE = -5;
    const int DISCARD_CHANGE = 3;

    // Place Adventurer card in hand and place treasure card at top of deck
    game.hand[CURRENT_PLAYER][HAND_POS] = adventurer;
    game.deckCount[CURRENT_PLAYER] = 5;
    game.deck[CURRENT_PLAYER][0] = copper;
    game.deck[CURRENT_PLAYER][1] = silver;
    game.deck[CURRENT_PLAYER][2] = estate;
    game.deck[CURRENT_PLAYER][3] = estate;
    game.deck[CURRENT_PLAYER][4] = duchy;

    // Copy a test instance
    memcpy(&test, &game, sizeof(struct gameState));

    // Run test case
    testGameState(game, test, actionCards, (CARDS_DRAWN - CARDS_PLAYED),
                  (DECK_CHANGE), CARDS_PLAYED, DISCARD_CHANGE, &passed, &tests);


    // Check the effects the Adventurer card has on the game state for the current player.
    printf("\n* Testing Current Player Playing %s card with empty deck...\n\n", CARD);

    const int DECK_CARDS_DRAWN = 2;
    const int DISCARD_COUNT = 5;

    // Place Adventurer card in hand and place treasure card at top of deck
    game.hand[CURRENT_PLAYER][HAND_POS] = adventurer;
    game.deckCount[CURRENT_PLAYER] = 0;
    game.discardCount[CURRENT_PLAYER] = DISCARD_COUNT;
    game.discard[CURRENT_PLAYER][0] = silver;
    game.discard[CURRENT_PLAYER][1] = silver;
    game.discard[CURRENT_PLAYER][2] = silver;
    game.discard[CURRENT_PLAYER][3] = silver;
    game.discard[CURRENT_PLAYER][4] = silver;

    // Copy a test instance
    memcpy(&test, &game, sizeof(struct gameState));

    // Run test case
    testGameState(game, test, actionCards, (CARDS_DRAWN - CARDS_PLAYED),
                  (DISCARD_COUNT - DECK_CARDS_DRAWN), CARDS_PLAYED, (-DISCARD_COUNT), &passed, &tests);


	// Check the effects the Adventurer card has on the game state for the
	// current player with no treasure cards to draw.
	printf("\n* Testing Current Player Playing %s card with NO treasure cards...\n\n", CARD);

    const int DISCARD_PILE = 5;

    game.deckCount[CURRENT_PLAYER] = 5;

    // Make all cards in deck Adventurer cards
    for(int i = 0; i < game.deckCount[CURRENT_PLAYER]; i++){
        game.deck[CURRENT_PLAYER][i] = adventurer;
    }

    game.discardCount[CURRENT_PLAYER] = 0;
    game.playedCardCount = 0;

    game.handCount[CURRENT_PLAYER] = 5;

    // Make all cards in hand Council Room cards
    for(int i = 0; i < game.handCount[CURRENT_PLAYER]; i++){

        game.hand[CURRENT_PLAYER][i] = council_room;
    }

    // Copy a test instance
    memcpy(&test, &game, sizeof(struct gameState));

    // Run test case
    testGameState(game, test, actionCards, (-CARDS_PLAYED),
                  (-DISCARD_PILE), CARDS_PLAYED, DISCARD_PILE, &passed, &tests);

    // Print Summary and Footer
    printTestSummary(passed, tests);
}






