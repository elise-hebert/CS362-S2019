/*
 * Author: Elise Hebert
 * CardTest: Adventurer card
 * File: cardtest1.c
 * Note: Used cardtest4.c from the professor as a guide for how to set up, changed all
 * variables and states as applied to the card itself.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

#define TESTCARD "Adventurer"

int main() {
  int  discarded = 1;
  int treasureCards = 2;  //Expected treasure Cards
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0; //Set up for the adventurer
  int seed = 1000;
  int players = 2;
  int currPlayer = 0;
  int returnstate;
  int i;
  int error = 0;  //For asserts, if there are no errors, then it passed all tests
  struct gameState game, testgame;
  int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                   sea_hag, tribute, smithy, council_room};

  //Start the game
  initializeGame(players, cards, seed, &game);

  printf("\t\t\tTesting %s Card\n", TESTCARD);

  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  returnstate = cardEffect(adventurer, choice1, choice2, choice3, &testgame, handpos, &bonus);

  //Show expected and resulting hands, expected being hand+2
  printf("Test 1 - Handcount\n");
  printf("Handcount = %d,  Expected handcount = %d\n", testgame.handCount[currPlayer], game.handCount[currPlayer] + treasureCards - discarded);

  //Test if the "top" two cards in the player's hand are treasure
  printf("Test 2 - Last two cards are treasure cards in hand\n");
  printf("Gold = %d, Silver = %d, Copper = %d\n", gold, silver, copper);
  printf("Last two cards = %d %d\n", testgame.hand[currPlayer][testgame.handCount[currPlayer]], testgame.hand[currPlayer][testgame.handCount[currPlayer] - 1]);


  //My assert tests, if it falls into any if statement, I add an error and print the problem
  if (testgame.handCount[currPlayer] != (game.handCount[currPlayer] + treasureCards - discarded)) {
    printf("Fail - expected hand count and actual hand count are not the same\n");
    error++;
  }
  if (testgame.hand[currPlayer][testgame.handCount[currPlayer]] != copper || testgame.hand[currPlayer][testgame.handCount[currPlayer]] != gold || testgame.hand[currPlayer][testgame.handCount[currPlayer]] != silver) {
    printf("Fail - last card is not treasure\n");
    error++;
  }
  if (testgame.hand[currPlayer][testgame.handCount[currPlayer]-1] != copper || testgame.hand[currPlayer][testgame.handCount[currPlayer]-1] != gold || testgame.hand[currPlayer][testgame.handCount[currPlayer]-1] != silver) {
    printf("Fail - second to last card is not treasure\n");
    error++;
  }
  if (returnstate != 0) {
    printf("Fail - Return did not equal zero\n");
    error++;
  }

  //Check if any errors occurred, if not, it passed the tests
  if (error == 0) {
    printf("Passed all tests for %s\n", TESTCARD);
  } else {
    printf("Total errors = %d\n", error);
  }

  return 0;
}
