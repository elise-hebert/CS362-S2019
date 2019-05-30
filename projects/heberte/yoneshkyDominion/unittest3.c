/*
 * Author: Elise Hebert
 * CardTest: Cutpurse card Function
 * File: unittest3.c
 * Note: Used cardtest4.c from the professor as a guide as well as referenced the testupdatecoins.c.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"


int main() {
  int handpos = 0;
  int seed = 1000;
  int players = 2;
  int currPlayer = 0;
  int otherPlayer = 1;
  int error = 0;  //For asserts, if there are no errors, then it passed all tests
  struct gameState game, testgame;
  int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                   sea_hag, tribute, smithy, council_room};

  //Start the game
  initializeGame(players, cards, seed, &game);

  printf("\t\t\tTesting cutpurseCard Function\n");
  printf("For reference: Gold = %d, Silver = %d, Copper = %d\n", gold, silver, copper);

  //Test 1 - Other player has a copper in their hand
  printf("Test 1 - Other player has 1 copper which we expect to be gone. Should show 1 & -1\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  testgame.hand[otherPlayer][0] = copper;
  testgame.hand[otherPlayer][1] = estate;
  testgame.handCount[otherPlayer] = 2;
  cutpurseCard(&testgame, currPlayer, handpos);

  printf("Card count in hand = %d, cards  in hand = %d %d\n", testgame.handCount[otherPlayer], testgame.hand[otherPlayer][0], testgame.hand[otherPlayer][1]);
  if (testgame.handCount[otherPlayer] != 1) {
    printf("Test 1 - Fail\n");
    error++;
  }

  //Test 2 - Other player has cards, but no copper/coins
  printf("Test 2 - Other player has no copper, so no change occurs\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  testgame.hand[otherPlayer][0] = estate;
  testgame.hand[otherPlayer][1] = -500;
  testgame.handCount[otherPlayer] = 1;
  cutpurseCard(&testgame, currPlayer, handpos);

  printf("Card count in other hand = %d, card in other hand = %d\n", testgame.handCount[otherPlayer], testgame.hand[otherPlayer][0]);
  if (testgame.handCount[otherPlayer] != 1) {
    printf("Test 2 - Fail\n");
    error++;
  }

  //Test 3 - Player has a gold card, no copper
  printf("Test 3 - Other player has 1 gold which we expect to have no change in hand\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  testgame.hand[otherPlayer][0] = gold;
  testgame.hand[otherPlayer][1] = estate;
  testgame.handCount[otherPlayer] = 2;
  cutpurseCard(&testgame, currPlayer, handpos);

  printf("Card count in hand = %d, cards in hand = %d %d\n", testgame.handCount[otherPlayer], testgame.hand[otherPlayer][0], testgame.hand[otherPlayer][1]);
  if (testgame.handCount[otherPlayer] != 2) {
    printf("Test 3 - Fail\n");
    error++;
  }

  //Test 4 - Player has silver, no copper
  printf("Test 4 - Other player has 1 silver which we expect to have no change in hand\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  testgame.hand[otherPlayer][0] = silver;
  testgame.hand[otherPlayer][1] = estate;
  testgame.handCount[otherPlayer] = 2;
  cutpurseCard(&testgame, currPlayer, handpos);

  printf("Card count in hand = %d, cards in hand = %d %d\n", testgame.handCount[otherPlayer], testgame.hand[otherPlayer][0], testgame.hand[otherPlayer][1]);
  if (testgame.handCount[otherPlayer] != 2) {
    printf("Test 4 - Fail\n");
    error++;
  }

  //Test 5 - player has no cards at all
  printf("Test 5 - Other player has no cards in hand\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  testgame.hand[otherPlayer][0] = -500;
  testgame.hand[otherPlayer][1] = -500;
  testgame.handCount[otherPlayer] = 0;
  cutpurseCard(&testgame, currPlayer, handpos);

  printf("Card count in hand = %d\n", testgame.handCount[otherPlayer]);
  if (testgame.handCount[otherPlayer] != 0) {
    printf("Test 5 - Fail\n");
    error++;
  }

  //Check if any errors occurred, if not, it passed the tests
  if (error == 0) {
    printf("Passed all tests for cutpurseCard Function\n");
  } else {
    printf("Total errors = %d\n", error);
  }

  return 0;
}
