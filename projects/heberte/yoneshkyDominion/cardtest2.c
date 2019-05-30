/*
 * Author: Elise Hebert
 * CardTest: Smithy card
 * File: cardtest2.c
 * Note: Used cardtest4.c from the professor as a guide for how to set up, changed all
 * variables and states as applied to the card itself.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

#define TESTCARD "Smithy"

int main() {
  int addedCards = 3;  //Expected to have 3 more cards in the player's hand
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0; //Set up for the smithy has no choices and no bonus
  int seed = 1000;
  int players = 2;
  int discarded = 1;
  int currPlayer = 0;
  int returnstate;
  int error = 0;
  struct gameState game, testgame;
  int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                   sea_hag, tribute, smithy, council_room};

  //Start the game
  initializeGame(players, cards, seed, &game);

  printf("\t\t\tTesting %s Card\n", TESTCARD);

  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  returnstate = cardEffect(smithy, choice1, choice2, choice3, &testgame, handpos, &bonus);

  //Test if the person has 3 new cards in their hands
  printf("Test 1 - Drew 3 cards in hand\n");
  printf("Number of cards in hand = %d,  expected number = %d\n", testgame.handCount[currPlayer], game.handCount[currPlayer] + addedCards - discarded);

  //Test if only 3 cards have been removed from deck.
  printf("Test 2 - If the deck is missing 3 cards only\n");
  printf("Deck count = %d,  expected deck count = %d\n", testgame.deckCount[currPlayer], game.deckCount[currPlayer] - addedCards);

  //My assert tests, checking if the player drew 3 cards,
  if (testgame.handCount[currPlayer] != (game.handCount[currPlayer] + addedCards - discarded)) {
    printf("Fail - not the right number of cards in hand\n");
    error++;
  }
  if (returnstate != 0) {
    printf("Fail - return state not 0\n");
    error++;
  }
  if (testgame.deckCount[currPlayer] != (game.deckCount[currPlayer] - addedCards)) {
    printf("Fail - deck counts do not match\n");
    error++;
  }

  if (error == 0) {
    printf("Passed all tests for %s\n", TESTCARD);
  } else {
    printf("Total errors = %d\n", error);
  }

  return 0;
}
