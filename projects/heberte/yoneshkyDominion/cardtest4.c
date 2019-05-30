/*
 * Author: Elise Hebert
 * CardTest: Council Room card
 * File: cardtest4.c
 * Note: Used cardtest4.c from the professor as a guide for how to set up, changed all
 * variables and states as applied to the card itself.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

#define TESTCARD "Council Room"

int main() {
  int addedCards = 4;  //Expected to have 3 more cards in the player's hand
  int discarded = 1;  //For discarding the Council Room at the end
  int playersAdd = 1; //For the card each player gets to their hands
  int addedBuy = 1; //For the buy the current player should get
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0; //Set up for the smithy has no choices and no bonus
  int seed = 1000;
  int players = 2;
  int currPlayer = 0;
  int otherPlayer = 1;
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
  returnstate = cardEffect(council_room, choice1, choice2, choice3, &testgame, handpos, &bonus);

  //Test if the person has 3 new cards in their hands
  printf("Test 1 - Current Player drew 4 cards in hand\n");
  printf("Number of cards in hand = %d,  expected number = %d\n", testgame.handCount[currPlayer], game.handCount[currPlayer] + addedCards - discarded);

  //Test if the current player received an additional buy
  printf("Test 2 - Current player has an additional buy\n");
  printf("Number of buys = %d, expected number of buys = %d\n", testgame.numBuys, game.numBuys + addedBuy);

  //Test if each player received an additional card
  printf("Test 3 - Other player also has an additional card in their hand\n");
  printf("Player 2 has %d cards, expected to have %d cards\n", testgame.handCount[otherPlayer], game.handCount[otherPlayer] + playersAdd);

  //Test if the curren player's deck count is correct
  printf("Test 4 - Current Player's deck count is accurate\n");
  printf("Deck Count = %d,  expected deck count = %d\n", testgame.deckCount[currPlayer], game.deckCount[currPlayer] - addedCards);

  //Test if the other player's deck count is correct
  printf("Test 5 - Other Player's deck count is accurate\n");
  printf("Deck Count = %d,  expected deck count = %d\n", testgame.deckCount[otherPlayer], game.deckCount[otherPlayer] - playersAdd);


  //My version of asserts - each fail will tally up and print out what the fail was without exiting (since there could be multiple)
  if (testgame.handCount[currPlayer] != (game.handCount[currPlayer] + addedCards - discarded)) {
    printf("Fail - not the right number of cards in hand\n");
    error++;
  }
  if (returnstate != 0) {
    printf("Fail - return state not 0\n");
    error++;
  }
  if (testgame.numBuys != (game.numBuys + addedBuy)) {
    printf("Fail - number of buys inconsistent\n");
    error++;
  }
  if (testgame.handCount[otherPlayer] != (game.handCount[otherPlayer] + playersAdd)) {
    printf("Fail - other player did not get an additional card in hand\n");
    error++;
  }
  if (testgame.deckCount[currPlayer] != (game.deckCount[currPlayer] - addedCards)) {
    printf("Fail - current player's deck count is incorrect\n");
    error++;
  }
  if (testgame.deckCount[otherPlayer] != (game.deckCount[otherPlayer] - playersAdd)) {
    printf("Fail - other player's deck count is incorrect\n");
    error++;
  }

  if (error == 0) {
    printf("Passed all tests for %s\n", TESTCARD);
  } else {
    printf("Total errors = %d\n", error);
  }

  return 0;
}
