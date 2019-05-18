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
  //Setting treasure and index to 0 because the assumption is this would be called
  //in cardEffect which does set these to 0. If it doesn't that is beyond the
  //scope of this random test so I will set them as is expected.
  int tr = 0, currplayer, index = 0;
  gameState *G;
  int tmp[MAX_HAND];
  int handBefore, result;
  int totalerror = 0, handerror = 0, holdingerror = 0, returnerror = 0;  //Count the number of fails in random tests

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  printf("-----------Random Testing of Adventurer Card----------------\n");

  SelectStream(2);
  PutSeed(3);

  for(int t = 0; t < 2000; t++) {
    for(int i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    //Randomize who the player is
    currplayer = floor(Random() * 2);
    //Randomize the player's hand and deck
    G.deckCount[currplayer] = floor(Random() * MAX_DECK);
    G.discardCount[currplayer] = floor(Random() * MAX_DECK);
    G.handCount[currplayer] = floor(Random() * MAX_HAND);
    handBefore = G.handCount[currplayer]+1;
    //To account for the adventurer card, add 1 to the hand in case they have 0
    G.handCount[currplayer]++;
    result = adventurerCard(tr, G, currplayer, tmp, index);
    if (G.handCount[currplayer] != handBefore+2) {
      printf("--FAIL Handcount is not increased by 2\n");
      error++;
      handerror++;
    }
    if (G.hand[currlayer][currplayer.handCount-1] != copper || G.hand[currlayer][currplayer.handCount-1] != gold || G.hand[currlayer][currplayer.handCount-1] != silver) {
      printf("--FAIL Last card is not treasure\n");
      error++;
      holdingerror++;

    }
    if (G.hand[currlayer][currplayer.handCount-2] != copper || G.hand[currlayer][currplayer.handCount-2] != gold || G.hand[currlayer][currplayer.handCount-2] != silver) {
      printf("--FAIL Second to last card is not treasure\n");
      error++;
      holdingerror++;
    }
    if (result != 0) {
      printf("--FAIL Return is not 0\n");
      error++;
      returnerror++;
    }

  }

  printf("Total number of Failed Tests: %d\n", error);
  if (error == 0) {
    printf("Random Test Passed\n");
  } else {
    printf("Total number of times handcount was incorrect: %d\n", handerror);
    printf("Total number of times the last or second to last card was not treasure: %d\n", holdingerror);
    printf("Total number of incorrect returns: %d\n", returnerror);
  }

  printf("----------------Adventurer Complete------------------\n");

  return 0;
}
