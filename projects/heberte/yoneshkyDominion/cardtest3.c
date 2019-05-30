/*
 * Author: Elise Hebert
 * CardTest: Village card
 * File: cardtest3.c
 * Note: Used cardtest4.c from the professor as a guide for how to set up, changed all
 * variables and states as applied to the card itself.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

#define TESTCARD "Village"

int main() {
  int addedCards = 1;  //Expected to draw 1 card
  int discarded = 1;  //For discarding the village at the end
  int addedAction = 2; //Gain 2 actions from village
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0; //Set up for the smithy has no choices and no bonus
  int seed = 1000;
  int players = 2;
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
  returnstate = cardEffect(village, choice1, choice2, choice3, &testgame, handpos, &bonus);

  //Test if the person has 1 new card in their hands
  printf("Test 1 - Drew 1 card in hand\n");
  printf("Number of cards in hand = %d,  expected number = %d\n", testgame.handCount[currPlayer], game.handCount[currPlayer] + addedCards - discarded);

  //Test if the player now has 2 additional Actions
  printf("Test 2 - Two actions added for current player\n");
  printf("Actions = %d,  expected actions = %d\n", testgame.numActions, game.numActions + addedAction);

  //Test if the deckCount is accurate
  printf("Test 3 - Deck Count is correct\n");
  printf("Deck Count = %d,  expected deck count = %d\n", testgame.deckCount[currPlayer], game.deckCount[currPlayer] - addedCards);


  //Assert tests for handcount, number of actions, return, and deckcount
  if (testgame.handCount[currPlayer] != (game.handCount[currPlayer] + addedCards - discarded)) {
    printf("Fail - not the right number of cards in hand\n");
    error++;
  }
  if (testgame.numActions != (game.numActions + addedAction)) {
    printf("Fail - actions incorrect\n");
    error++;
  }
  if (returnstate != 0) {
    printf("Fail - return state not 0\n");
    error++;
  }
  if (testgame.deckCount[currPlayer] != (game.deckCount[currPlayer] - addedCards)) {
    printf("Fail - deck count incorrect\n");
    error++;
  }

  if (error == 0) {
    printf("Passed all tests for %s\n", TESTCARD);
  } else {
    printf("Total errors = %d\n", error);
  }

  return 0;
}
