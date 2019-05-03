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
  int i;
  int errors = 0;  //For asserts, if there are no errors, then it passed all tests
  struct gameState game, testgame;
  int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                   sea_hag, tribute, smithy, council_room};

  //Start the game
  initializeGame(players, cards, seed, &game);

  printf("\t\t\tTesting cutpurseCard Function\n");

  printf("Test 1 - Other player has 1 copper which we expect to be gone\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  testgame.hand[otherPlayer][0] = copper;
  testgame.hand[otherPlayer][1] = estate;
  cutpurseCard(&testgame, currPlayer, handPos);

  printf("Card count in hand = %d, card in hand = %d\n", testgame.handCount[otherPlayer], testgame.hand[otherPlayer][0]);
  if (testgame.handCount[otherPlayer] != 1) {
    printf("Test 1 - Fail\n");
    error++;
  }

  printf("Test 2 - Other player has no copper, so no change occurs\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  testgame.hand[otherPlayer][0] = estate;
  testgame.hand[otherPlayer][1] = NULL;
  cutpurseCard(&testgame, currPlayer, handPos);

  printf("Card count in other hand = %d, card in other hand = %d\n", testgame.handCount[otherPlayer], testgame.hand[otherPlayer][0]);
  if (testgame.handCount[otherPlayer] != 1) {
    printf("Test 2 - Fail\n");
    error++;
  }

  printf("Test 3 - Other player has 1 gold which we expect to have no change in hand\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  testgame.hand[otherPlayer][0] = gold;
  testgame.hand[otherPlayer][1] = estate;
  cutpurseCard(&testgame, currPlayer, handPos);

  printf("Card count in hand = %d, cards in hand = %d %d\n", testgame.handCount[otherPlayer], testgame.hand[otherPlayer][0], testgame.hand[otherPlayer][1]);
  if (testgame.handCount[otherPlayer] != 2) {
    printf("Test 3 - Fail\n");
    error++;
  }

  printf("Test 4 - Other player has 1 silver which we expect to have no change in hand\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  testgame.hand[otherPlayer][0] = silver;
  testgame.hand[otherPlayer][1] = estate;
  cutpurseCard(&testgame, currPlayer, handPos);

  printf("Card count in hand = %d, cards in hand = %d %d\n", testgame.handCount[otherPlayer], testgame.hand[otherPlayer][0], testgame.hand[otherPlayer][1]);
  if (testgame.handCount[otherPlayer] != 2) {
    printf("Test 4 - Fail\n");
    error++;
  }

  printf("Test 5 - Other player has no cards in hand\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  testgame.hand[otherPlayer][0] = NULL;
  testgame.hand[otherPlayer][1] = NULL;
  cutpurseCard(&testgame, currPlayer, handPos);

  printf("Card count in hand = %d\n", testgame.handCount[otherPlayer]);
  if (testgame.handCount[otherPlayer] != 0) {
    printf("Test 5 - Fail\n");
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
