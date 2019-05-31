/*
 * Author: Elise Hebert
 * CardTest: Adventurer card Function for Kyle's Dominion
 * File: unittest1.c
 * Note: Used cardtest4.c from the professor as a guide as well as referenced the testupdatecoins.c.
 * Note 2: Because Kyle's code only allowed game state, my drawn Treasure variable that I
 * tested is obsolete. I kept the tests but took out the changing variable. Comments show what
 * the original test was before I had to update 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"


int main() {
  int  discarded = 1;
  int seed = 1000;
  int players = 2;
  int currPlayer = 0;
  int error = 0;  //For asserts, if there are no errors, then it passed all tests
  struct gameState game, testgame;
  int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                   sea_hag, tribute, smithy, council_room};

  //Start the game
  initializeGame(players, cards, seed, &game);

  printf("\t\t\tTesting adventurerCard Function\n");

  //Test 1 - expected input is 0 for drawn treasure, so 2 treasure should be added to player's hand
  printf("Test 1 - expecting 2 treasure cards in hand\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  adventurerCard(&testgame);

  printf("Treasure cards in hand = %d\n", (testgame.handCount[currPlayer] - game.handCount[currPlayer]));
  if ((testgame.handCount[currPlayer] - game.handCount[currPlayer]) != 2) {
    printf("Test 1 - Fail\n");
    error++;
  }

  //Test 2 - set drawn treasure to 1, expecting 2 treasure card in hand
  printf("Test 2 - expecting 2 treasure card in hand\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  adventurerCard(&testgame);

  printf("Treasure cards in hand = %d\n", (testgame.handCount[currPlayer] - game.handCount[currPlayer]));
  if ((testgame.handCount[currPlayer] - game.handCount[currPlayer]) != 2) {
    printf("Test 2 - Fail\n");
    error++;
  }

  //Test 3 - set drawn treasure to 2, expecting no additional cards in hand
  printf("Test 3 - expecting 2 treasure cards in hand\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  adventurerCard(&testgame);

  printf("Treasure cards in hand = %d\n", (testgame.handCount[currPlayer] - game.handCount[currPlayer]));
  if ((testgame.handCount[currPlayer] - game.handCount[currPlayer]) != 2) {
    printf("Test 3 - Fail\n");
    error++;
  }

  //Test 4 - Set treasure drawn to a negative number
  printf("Test 4 - expecting 2 treasure cards in hand\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  adventurerCard(&testgame);

  printf("Treasure cards in hand = %d\n", (testgame.handCount[currPlayer] - game.handCount[currPlayer]));
  if ((testgame.handCount[currPlayer] - game.handCount[currPlayer]) != 2) {
    printf("Test 4 - Fail\n");
    error++;
  }

  //Check if any errors occurred, if not, it passed the tests
  if (error == 0) {
    printf("Passed all tests for adventurerCard Function\n");
  } else {
    printf("Total errors = %d\n", error);
  }

  return 0;
}
