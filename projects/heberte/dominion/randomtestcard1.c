// Author: Elise Hebert
// Date: 5/17/2019
// File: randomtestcard.c
// Description: This will test the Smithy card via random testing. Note: used the
// betterTestDrawCard.c as a guide

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"


int main() {
  //Setting exected drawn cards and the current player
  int cards = 3, currplayer;
  gameState *G;
  int handBefore, deckBefore, discardBefore, result;
  int totalerror = 0, handerr = 0, deckerr = 0, discarderr = 0, returnerror = 0;  //Count the number of fails in random tests

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  printf("-----------Random Testing of Smithy Card----------------\n");

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
    deckBefore = G.deckCount[currPlayer];
    G.discardCount[currplayer] = floor(Random() * MAX_DECK);
    discardBefore = G.discardCount[currplayer];
    G.handCount[currplayer] = floor(Random() * MAX_HAND);
    handBefore = G.handCount[currplayer]+1;
    //To account for the smithy card, add 1 to the hand in case they have 0
    G.handCount[currplayer]++;
    G.hand[currplayer][G.handCount-1] = smithy;
    result = smithyCard(currplayer, G, G.handCount-1);
    //Expecting the hand to have 2 more than previous (because you gain 3 and discard 1)
    if (G.handCount[currplayer] != handBefore+card-1) {
      printf("--FAIL Handcount is not increased by 2\n");
      error++;
      handerr++;
    }
    if (G.deckCount[currplayer] != deckBefore-card) {
      printf("--FAIL Deck is not 3 less than before play\n");
      error++;
      deckerr++;

    }
    if (G.discardCount[currplayer] != discardBefore+1) {
      printf("--FAIL Discard count does not have Smithy\n");
      error++;
      discarderr++;
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
    printf("Total number of times handcount was incorrect: %d\n", handerr);
    printf("Total number of times deck was incorrect: %d\n", deckerr);
    printf("Total number of times discard was incorrect: %d\n", discarderr);
    printf("Total number of incorrect returns: %d\n", returnerror);
  }

  printf("----------------Smithy Complete------------------\n");

  return 0;
}
