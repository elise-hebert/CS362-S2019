/*
 * Author: Elise Hebert
 * CardTest: Minion card Function
 * File: unittest2.c
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
  int handpos = 0, choice1 = 0, choice2 = 0, bonus = 0; //Set up for the adventurer
  int seed = 1000;
  int players = 2;
  int currPlayer = 0;
  int otherPlayer = 1;
  int i;
  int error = 0;  //For asserts, if there are no errors, then it passed all tests
  struct gameState game, testgame;
  int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                   sea_hag, tribute, smithy, council_room};

  //Start the game
  initializeGame(players, cards, seed, &game);

  printf("\t\t\tTesting minionCard Function\n");

  //Test 1 - choice 1 is chosen
  printf("Test 1 - choice 1 indicated, so 2 coins added\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  choice1 = 1;
  choice2 = 0;
  printf("Coins before = %d\n", testgame.coins);
  cardEffect(minion, choice1, choice2, 0, &testgame, handpos, &bonus);

  printf("Coins = %d\n", testgame.coins);
  if (testgame.coins != (game.coins + 2)) {
    printf("Test 1 - Fail\n");
    error++;
  }

  //Test 2 - choice 2 is selected and choice 1 with other player having less than 5 cards
  printf("Test 2 - choice 2 indicated, current player should have 4 cards and other player no change\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  choice1 = 0;
  choice2 = 1;
  //Have the other player have 3 gold cards
  for (i = 0; i < 3; i++) {
    testgame.hand[otherPlayer][i] = gold;
  }
  cardEffect(minion, choice1, choice2, 0, &testgame, handpos, &bonus);

  printf("Cards in hand = %d, Other player card count = %d\n", testgame.handCount[currPlayer], testgame.handCount[otherPlayer]);
  if (testgame.handCount[currPlayer] != 4) {
    printf("Test 2 - Fail, current player doesn't have 4 cards\n");
    error++;
  }
  if (testgame.handCount[otherPlayer] != 3) {
    printf("Test 2 - Fail, other player doest not have 3 cards\n");
    error++;
  }

  //Test 3 - choice 2 is selected and choice 1 with other player having more than 5 cards
  printf("Test 3 - choice 2 indicated, current player should have 4 cards and other player 4 cards\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  choice1 = 0;
  choice2 = 1;
  //Have the other player have 6 gold cards
  for (i = 0; i < 6; i++) {
    testgame.hand[otherPlayer][i] = gold;
  }
  cardEffect(minion, choice1, choice2, 0, &testgame, handpos, &bonus);

  printf("Cards in hand = %d, Other player card count = %d\n", testgame.handCount[currPlayer], testgame.handCount[otherPlayer]);
  if (testgame.handCount[currPlayer] != 4) {
    printf("Test 3 - Fail, current player doesn't have 4 cards\n");
    error++;
  }
  if (testgame.handCount[otherPlayer] != 4) {
    printf("Test 3 - Fail, other player doest not have 4 cards\n");
    error++;
  }

  //Test 4 - both choices are selected
  printf("Test 4 - choice 1 indicated and choice 2 indicated, no change is expected\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  choice1 = 1;
  choice2 = 1;
  cardEffect(minion, choice1, choice2, 0, &testgame, handpos, &bonus);

  printf("Coins = %d, expected coins = %d\n", testgame.coins, game.coins);
  printf("Cards = %d, expected cards = %d\n", testgame.handCount[currPlayer], game.handCount[currPlayer]-discarded);
  if (testgame.coins != game.coins) {
    printf("Test 4 - Fail, coins have been added\n");
    error++;
  }
  if ((testgame.handCount[currPlayer]) != (game.handCount[currPlayer]-discarded)) {
    printf("Test 4 - Fail, card count has changed\n");
    error++;
  }

  //Test 5 - neither choice is selected
  printf("Test 5 - choice 1 not indicated, and choice 2 not indicated, no change is expected\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  choice1 = 0;
  choice2 = 0;
  cardEffect(minion, choice1, choice2, 0, &testgame, handpos, &bonus);

  printf("Coins = %d, expected coins = %d\n", testgame.coins, game.coins);
  printf("Cards = %d, expected cards = %d\n", testgame.handCount[currPlayer]-discarded, game.handCount[currPlayer]-discarded);
  if (testgame.coins != game.coins) {
    printf("Test 5 - Fail, coins have been added\n");
    error++;
  }
  if ((testgame.handCount[currPlayer]) != (game.handCount[currPlayer]-discarded)) {
    printf("Test 5 - Fail, card count has changed\n");
    error++;
  }

  //Check if any errors occurred, if not, it passed the tests
  if (error == 0) {
    printf("Passed all tests for minionCard Function\n");
  } else {
    printf("Total errors = %d\n", error);
  }

  return 0;
}
