/*
 * Author: Elise Hebert
 * CardTest: Council Room card Function
 * File: unittest4.c
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
  int addedCards = 4;
  int handpos = 0;
  int seed = 1000;
  int players = 2;
  int currPlayer;
  int otherPlayer;
  int error = 0;  //For asserts, if there are no errors, then it passed all tests
  struct gameState game, testgame;
  int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                   sea_hag, tribute, smithy, council_room};

  //Start the game
  initializeGame(players, cards, seed, &game);

  printf("\t\t\tTesting council_roomCard Function\n");

  //Test 1 - Both players are indexed within array bounds
  printf("Test 1 - Current Player and Other Player in bounds\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  currPlayer = 0;
  otherPlayer = 1;
  printf("Before play, Current Player has %d cards, other player has %d cards\n", testgame.handCount[currPlayer], testgame.handCount[otherPlayer]);
  council_roomCard(&testgame, currPlayer, handpos);

  printf("Cards for current player = %d,  expected number = %d\n", testgame.handCount[currPlayer], game.handCount[currPlayer] + addedCards - discarded);
  printf("Cards for other player = %d,  expected number = %d\n", testgame.handCount[otherPlayer], game.handCount[otherPlayer] + discarded);

  if (testgame.handCount[currPlayer] != (game.handCount[currPlayer]+addedCards - discarded)) {
    printf("Test 1 - Fail, current player does not have expected hand count\n");
    error++;
  }
  if (testgame.handCount[otherPlayer] != (game.handCount[otherPlayer]+discarded)){
    printf("Test 1 - Fail, other player does not have expected hand count\n");
    error++;
  }

  //Test 2 - Current player is a negative number, other player in array bounds
  printf("Test 2 - Current Player is a negative number, so should have null results\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  currPlayer = -1;
  otherPlayer = 1;
  printf("Before play, Current Player has %d cards, other player has %d cards\n", testgame.handCount[currPlayer], testgame.handCount[otherPlayer]);
  council_roomCard(&testgame, currPlayer, handpos);

  printf("Cards for current player = %d,  expected number = %d\n", testgame.handCount[currPlayer], -1);
  printf("Cards for other player = %d,  expected number = %d\n", testgame.handCount[otherPlayer], game.handCount[otherPlayer]);

  if (testgame.handCount[currPlayer] != -1) {
    printf("Test 2 - Fail, current player should have no cards\n");
    error++;
  }
  if (testgame.handCount[otherPlayer] != game.handCount[otherPlayer]){
    printf("Test 2 - Fail, other player does not have expected hand count\n");
    error++;
  }

  //Test 3 - Current player assigned positive number outside array bounds, other player in bounds
  printf("Test 3 - Current Player assigned positive number beyond bounds, so count should be null\n");
  //Copy game state to the test game
  memcpy(&testgame, &game, sizeof(struct gameState));
  currPlayer = 2;
  otherPlayer = 1;
  printf("Before play, Current Player has %d cards, other player has %d cards\n", testgame.handCount[currPlayer], testgame.handCount[otherPlayer]);
  council_roomCard(&testgame, currPlayer, handpos);

  printf("Cards for current player = %d,  expected number = %d\n", testgame.handCount[currPlayer], -1);
  printf("Cards for other player = %d,  expected number = %d\n", testgame.handCount[otherPlayer], game.handCount[otherPlayer]);

  if (testgame.handCount[currPlayer] != -1) {
    printf("Test 3 - Fail, current player should have zero cards\n");
    error++;
  }
  if (testgame.handCount[otherPlayer] != (game.handCount[otherPlayer])){
    printf("Test 3 - Fail, other player does not have expected hand count\n");
    error++;
  }


  //Check if any errors occurred, if not, it passed the tests
  if (error == 0) {
    printf("Passed all tests for council_roomCard Function\n");
  } else {
    printf("Total errors = %d\n", error);
  }

  return 0;
}
