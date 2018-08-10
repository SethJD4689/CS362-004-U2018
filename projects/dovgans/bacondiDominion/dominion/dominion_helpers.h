#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);
int smithyCardEffect(struct gameState *state, const int currentPlayer,
					 const int handPos);
int salvagerCardEffect(struct gameState *state, const int currentPlayer,
					   const int handPos, const int choice1);
int adventurerCardEffect(struct gameState *state, const int currentPlayer);
int stewardCardEffect(struct gameState *state, const int currentPlayer,
					  const int handPos, const int choice1, const int choice2,
					  const int choice3);
int baronCardEffect(struct gameState *state, const int currentPlayer, const int choice1);
int councilRoomCardEffect(struct gameState *state, const int currentPlayer, int handPos);

#endif
