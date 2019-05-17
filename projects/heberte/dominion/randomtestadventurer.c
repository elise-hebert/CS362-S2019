/*
 * Author: Elise Hebert
 * File: randomtestadventurer.c
 * Date: 5/17/2019
 * Description: This is a random test of the card Adventurer in the Dominion
 * game. It will generate 2000 tests and randomly create a game state each time
 * and check to see if the expected plays occur. Note: used betterTestDrawCard.c
 * as a guide
 *
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int main() {
  int tr, currplayer, index;
  gameState *G;
  int* tmp;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  printf("Random Testing of Adventurer Card\n");

  SelectStream(2);
  PutSeed(3);

  for(int t = 0; t < 2000; t++) {
    for(int i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    currplayer = floor(Random() * 2);

  }

  return 0;
}
