/*
 * Author: Elise Hebert
 * File: randomtestadventurer.c
 * Date: 5/31/2019
 * Description: This is a random test of the card Adventurer in the Dominion
 * game. It will generate 2000 tests and randomly create a game state each time
 * and check to see if the expected plays occur. Note: used betterTestDrawCard.c
 * as a guide. This is Kyle's rendition of Adventurer
 *
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rngs.h"


int main() {
  //Setting treasure and index to 0 because the assumption is this would be called
  //in cardEffect which does set these to 0. If it doesn't that is beyond the
  //scope of this random test so I will set them as is expected.
  int currplayer, index = 0;
  struct gameState G;
  int seed = 1000;
  int players = 2;
  int handBefore;
  int error = 0, handerror = 0, holdingerror = 0;  //Count the number of fails in random tests

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  printf("-----------Random Testing of Adventurer Card----------------\n");
  initializeGame(players, k, seed, &G);

  for(int t = 0; t < 2000; t++) {
    //Randomize who the player is
    currplayer = floor(Random() * 2);
    //Randomize the player's hand and deck
    G.deckCount[currplayer] = floor(Random() * MAX_DECK);
    G.discardCount[currplayer] = floor(Random() * MAX_DECK);
    G.handCount[currplayer] = floor(Random() * MAX_HAND);
    handBefore = G.handCount[currplayer]+1;
    //To account for the adventurer card, add 1 to the hand in case they have 0
    G.handCount[currplayer]++;
    adventurerCard(&G);
    if (G.handCount[currplayer] != handBefore+2) {
      printf("--FAIL Handcount is not increased by 2\n");
      error++;
      handerror++;
    }
    if (G.hand[currplayer][G.handCount[currplayer]-1] != copper || G.hand[currplayer][G.handCount[currplayer]-1] != gold || G.hand[currplayer][G.handCount[currplayer]-1] != silver) {
      printf("--FAIL Last card is not treasure\n");
      error++;
      holdingerror++;

    }

  }

  printf("Total number of Failed Tests: %d\n", error);
  if (error == 0) {
    printf("Random Test Passed\n");
  } else {
    printf("Total number of times handcount was incorrect: %d\n", handerror);
    printf("Total number of times the last card was not treasure: %d\n", holdingerror);
  }

  printf("----------------Adventurer Complete------------------\n");

  return 0;
}
