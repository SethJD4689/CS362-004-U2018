Bugs

Adventurer Card Effect 
	
-	Copper comparison value was not included in the condition statement making sure the player was drawing a treasure card. I fixed this bug since it would produce an endless loop in the event the player doesn’t have two copper cards in their deck to draw. The fix was necessary in order to be able to run my entire unit testing.
-	Shuffling the deck never takes place after called. Since the deck is always empty, the discarded cards must first be places in the deck, then the shuffle function can be called to shuffle the deck. 
-	A condition statement needs to be included with the results of drawCard. If no card is drawn, the player’s hand count still gets decremented creating an endless loop and making the player’s hand count below zero.
-	The adventurer card is never discarded. A discardCard function call should be included in the in this function.

Salvager Card Effect

-	Trash Card option will not let the player trash the first card in their hand. A condition statement should be included making choice1 >= 0 to trash a card. 
-	The trashed card option is trashing the players played card versus the card they want to trash. In the trash choice conditional statement, the discard function needs to be called with choice1 and not handPos.
-	In the event the player doesn’t have any cards to trash, the game state gets altered unexpectedly.

Smithy Card Effect

-	Calling smithy card effect is drawing 4 cards instead of three. The conditional statement needs to be changed to < 3 versus <= 3.
-	The Smithy card is not being placed in the played pile of cards. This is because the card is being trashed instead being placed in the played pile. The discard function call should have a 0 in place of a 1 so the card is played and not trashed.

scoreFor Function

-	In the scoreFor function, the loop uses discardCount for the conditional termination versus deckCount.
