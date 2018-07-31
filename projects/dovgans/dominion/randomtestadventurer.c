/*******************************************************************************
** Assignment: CS362 - Assignment 4
** Filename: randomtestadventurer.c
** Author: Seth Dovgan
** Date: 23 JUL 2018
**
** Description: Tests the Adventurer card with random testing.
*******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "tester.h"

#define CARD "Adventurer"
#define TYPE "Card"
#define CARDS_DRAWN 2 	// Number of cards drawn by the Adventurer card
#define CARDS_PLAYED 1 	// Adventurer card played
#define NUM_OF_TESTS 100000

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
int getNumberOfTreasureCardsInDeck(int deck[][MAX_DECK], const int deckCount[],
                                   int player){

    int treasureCardCount = 0;

    for(int i = 0; i < deckCount[player]; i++){

        if(deck[player][i] == copper || deck[player][i] == silver
           || deck[player][i] == gold){

            treasureCardCount++;
        }
    }

    return treasureCardCount;
}

/*******************************************************************************
**  Function: testDrawnTreasureCards
**  Description: Tests if treasure cards are drawn
*******************************************************************************/
void testDrawnTreasureCards(struct gameState test, int player, int *passed,
                            int *tests, int cardsDrawn){

    // Verify both drawn cards were treasure cards.
    printf("\n* Testing both cards drawn were treasure cards...\n\n");

    int count = cardsDrawn;

    while(count > 0){

        if(test.handCount[player] >= count){

            int cardPosition = test.handCount[player] - count;
            char name[MAX_STRING_LENGTH];
            cardNumToName(test.hand[player][cardPosition], name);

            strcat(name, " Card Drawn");

            assertTrue(TRUE, (test.hand[player][cardPosition] == copper
                              || test.hand[player][cardPosition] == silver
                              || test.hand[player][cardPosition] == gold),
                       name, passed, tests);

        } else {
            assertTrue(FALSE, TRUE, "No treasure card", passed, tests);
        }

        count--;
    }
}


/*******************************************************************************
**  Function: main
**  Description: Tests the Adventurer card effect on the state of the game with
**  random testing.
*******************************************************************************/
int main() {

    srand(time(NULL));

    struct gameState game, test;

    int tests = 0;
    int passed = 0;
    int handPos;
    long randomTests = NUM_OF_TESTS;

    // Print Test Header
    printTestHeader(CARD, TYPE);

    while(randomTests > 0){

        int *actionCards = generateRandomGameState(&game, smithy, &handPos);
        int selectedPlayer = game.whoseTurn;
	    int deckCount = getNumberOfTreasureCardsInDeck(game.deck, game.deckCount, selectedPlayer);
	    int discardCount = getNumberOfTreasureCardsInDeck(game.discard, game.discardCount, selectedPlayer);

	    printf("\n* Preconditions for Player %d Playing %s card...\n\n", selectedPlayer, CARD);
	    printf("Hand Count: %d\n", game.handCount[selectedPlayer]);
	    printf("Deck Count: %d\n", game.deckCount[selectedPlayer]);
	    printf("Discard Count: %d\n", game.discardCount[selectedPlayer]);
	    printf("Treasurer Cards in Deck: %d\n", deckCount);
	    printf("Treasurer Cards in Discard: %d\n", discardCount);

	    // Copy a test instance
	    memcpy(&test, &game, sizeof(struct gameState));

        // Call smithy function
        adventurerCardEffect(&test, selectedPlayer);

        // Check the effects the Adventurer card has on the game state for player.
        printf("\n* Testing Player %d Playing %s card...\n\n", selectedPlayer, CARD);

        printf("Adventurer Card Hand Position: %d\n", handPos);

        // Calculate expected outcomes for various deck and discard counts
        // Deck has less than the amount of cards treasure cards to draw
        if(deckCount < CARDS_DRAWN && discardCount >= CARDS_DRAWN){

	        testCurrentPlayerStateModified(&game, &test, selectedPlayer,
	                                       (CARDS_DRAWN - CARDS_PLAYED),
	                                       CARDS_PLAYED, NO_CHANGE, NO_CHANGE,
	                                       NO_CHANGE, NO_CHANGE, &passed, &tests);

            testDrawnTreasureCards(test, selectedPlayer, &passed, &tests,
                                   CARDS_DRAWN);

            // Deck and discard have less than the amount of cards to draw
            // but combined they both do
        } else if(deckCount < CARDS_DRAWN && discardCount < CARDS_DRAWN
                  && (deckCount + discardCount) >= CARDS_DRAWN){

	        testCurrentPlayerStateModified(&game, &test, selectedPlayer,
	                                       (CARDS_DRAWN - CARDS_PLAYED),
	                                       CARDS_PLAYED, NO_CHANGE, NO_CHANGE,
	                                       NO_CHANGE, NO_CHANGE, &passed, &tests);

            testDrawnTreasureCards(test, selectedPlayer, &passed, &tests,
                                   CARDS_DRAWN);

            // Deck and discard have less than the amount of cards to draw
            // and combined they still do not have enough
        } else if(deckCount < CARDS_DRAWN && discardCount < CARDS_DRAWN
                  && (deckCount + discardCount) < CARDS_DRAWN){

	        testCurrentPlayerStateModified(&game, &test, selectedPlayer,
	                                       (deckCount + discardCount - CARDS_PLAYED),
	                                       CARDS_PLAYED, NO_CHANGE, NO_CHANGE,
	                                       NO_CHANGE, NO_CHANGE, &passed, &tests);

            testDrawnTreasureCards(test, selectedPlayer, &passed, &tests,
                                   (deckCount + discardCount));

        } else { // Deck has enough cards to draw.

            testCurrentPlayerState(&game, &test, selectedPlayer, (CARDS_DRAWN - CARDS_PLAYED),
                                   (-CARDS_DRAWN), CARDS_PLAYED, NO_CHANGE,
                                   NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE,
                                   &passed, &tests);

            testDrawnTreasureCards(test, selectedPlayer, &passed, &tests,
                                   CARDS_DRAWN);
        }

        // Check if the card was actually played
        testCardPlayed(&game, &test, selectedPlayer, handPos, &passed, &tests);

        // Check the effects the Smithy card has on the game state for a non current player
        for(int i = 0; i < test.numPlayers; i++){

            if(i != selectedPlayer){

                printf("\n* Testing Player %d...\n\n", i);
                testOtherPlayerNoStateChange(&game, &test, i, &passed, &tests);
            }
        }

        // Verify no victory card piles were effected.
        printf("\n* Testing Victory Card Piles...\n\n");
        testVictoryCardPilesNoChange(&game, &test, &passed, &tests);

        // Verify no treasure card piles were affected
        printf("\n* Testing Treasure Card Piles...\n\n");
        testTreasureCardPilesNoChange(&game, &test, &passed, &tests);

        // Verify no kingdom card piles were affected
        printf("\n* Testing Kingdom Card Piles...\n\n");
        testKingdomCardPilesNoChange(&game, &test, actionCards, &passed, &tests);

        randomTests--;
    }

    // Print Test Summary
    printTestSummary(passed, tests);
}


