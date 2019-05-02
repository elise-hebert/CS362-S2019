/*
 * Author: Elise Hebert
 * CardTest: Adventurer card Function
 * File: unittest1.c
 * Note: Used cardtest4.c from the professor as a guide as well as referenced the testupdatecoins.c.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"


int main() {
  int  discarded = 1;
  int treasureCards;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0; //Set up for the adventurer
  int seed = 1000;
  int players = 2;
  int currPlayer = 0;
  int passedCard;
  int temp[MAX_HAND];
  int z = 0;
  int i;
  int errors = 0;  //For asserts, if there are no errors, then it passed all tests
  struct gameState game, testgame;
  int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                   sea_hag, tribute, smithy, council_room};

  //Start the game
  initializeGame(players, cards, seed, &game);

  printf("\t\t\tTesting adventurerCard Function\n");

  printf("Test 1 - treasureCards = 0, expecting 2 treasure cards in hand\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  drawntreasure = 0;
  adventurerCard(drawntreasure, &testgame, currPlayer, passedCard, temp, z);

  printf("Treasure cards in hand = %d\n", (testgame.handCount[currPlayer] - game.handCount[currPlayer]));
  if ((testgame.handCount[currPlayer] - game.handCount[currPlayer]) != 2) {
    printf("Test 1 - Fail\n");
    error++;
  }

  printf("Test 2 - treasureCards = 1, expecting 1 treasure card in hand\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  drawntreasure = 1;
  adventurerCard(drawntreasure, &testgame, currPlayer, passedCard, temp, z);

  printf("Treasure cards in hand = %d\n", (testgame.handCount[currPlayer] - game.handCount[currPlayer]));
  if ((testgame.handCount[currPlayer] - game.handCount[currPlayer]) != 1) {
    printf("Test 2 - Fail\n");
    error++;
  }

  printf("Test 3 - treasureCards = 2, expecting 0 treasure cards in hand\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  drawntreasure = 2;
  adventurerCard(drawntreasure, &testgame, currPlayer, passedCard, temp, z);

  printf("Treasure cards in hand = %d\n", (testgame.handCount[currPlayer] - game.handCount[currPlayer]));
  if ((testgame.handCount[currPlayer] - game.handCount[currPlayer]) != 0) {
    printf("Test 3 - Fail\n");
    error++;
  }

  printf("Test 4 - treasureCards = -1, expecting 0 treasure cards in hand\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  drawntreasure = -1;
  adventurerCard(drawntreasure, &testgame, currPlayer, passedCard, temp, z);

  printf("Treasure cards in hand = %d\n", (testgame.handCount[currPlayer] - game.handCount[currPlayer]));
  if ((testgame.handCount[currPlayer] - game.handCount[currPlayer]) != 0) {
    printf("Test 4 - Fail\n");
    error++;
  }

  //Check if any errors occurred, if not, it passed the tests
  if (error == 0) {
    printf("Passed all tests for adventurerCard Function\n");
  } else {
    printf("Total errors = %d\n", errors);
  }

  return 0;
}
