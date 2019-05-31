// Author: Elise Hebert
// Date: 5/17/2019
// File: randomtestcard2.c
// Description: This creates a random test for Council Room card/function. Note: I
// used the betterTestDrawCard.c file as reference.

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"

int main() {
  //Setting exected drawn cards and the current player
  int cards = 4, currplayer, bonus = 0;
  struct gameState G;
  int seed = 1000;
  int players = 2;
  int handBefore, deckBefore, discardBefore, result, buysBefore, otherdeck, otherhand;
  //Count the number of fails in random tests
  int error = 0, handerr = 0, deckerr = 0, discarderr = 0, returnerror = 0,
      buyerr = 0, otherDerr = 0, otherHerr = 0;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  printf("-----------Random Testing of Council Room Card----------------\n");

  initializeGame(players, k, seed, &G);

  for(int t = 0; t < 2000; t++) {
    //Randomize who the player is
    currplayer = floor(Random() * 2);
    //Randomize the player's hand and deck
    G.deckCount[currplayer] = floor(Random() * MAX_DECK);
    deckBefore = G.deckCount[currplayer];
    G.discardCount[currplayer] = floor(Random() * MAX_DECK);
    discardBefore = G.discardCount[currplayer];
    G.handCount[currplayer] = floor(Random() * MAX_HAND);
    handBefore = G.handCount[currplayer]+1;
    buysBefore = G.numBuys;
    if (currplayer == 1) {
      otherdeck = G.deckCount[0];
      otherhand = G.handCount[0];
    } else if (currplayer == 0) {
      otherdeck = G.deckCount[1];
      otherhand = G.handCount[1];
    }
    //To account for the smithy card, add 1 to the hand in case they have 0
    G.handCount[currplayer]++;
    G.hand[currplayer][G.handCount[currplayer]-1] = council_room;
    result = cardEffect(council_room, 0, 0, 0, &G,G.handCount[currplayer]-1, &bonus);
    //Expecting the hand to have 2 more than previous (because you gain 3 and discard 1)
    if (G.handCount[currplayer] != handBefore+cards-1) {
      printf("--FAIL Handcount is not increased by 3\n");
      error++;
      handerr++;
    }
    if (G.numBuys != buysBefore+1) {
      printf("--FAIL Number of buys is not increased by 1\n");
      error++;
      buyerr++;
    }
    if (G.deckCount[currplayer] != deckBefore-cards) {
      printf("--FAIL Deck is not 4 less than before play\n");
      error++;
      deckerr++;
    }
    if (currplayer == 0) {
      if (G.deckCount[1] != otherdeck-1) {
        printf("--FAIL Other player deck isn't 1 less than before play\n");
        error++;
        otherDerr++;
      }
      if (G.handCount[1] != otherhand+1) {
        printf("--FAIL Other player hand isn't 1 more than before play\n");
        error++;
        otherHerr++;
      }
    } else if (currplayer == 1) {
      if (G.deckCount[0] != otherdeck-1) {
        printf("--FAIL Other player deck isn't 1 less than before play\n");
        error++;
        otherDerr++;
      }
      if (G.handCount[0] != otherhand+1) {
        printf("--FAIL Other player hand isn't 1 more than before play\n");
        error++;
        otherHerr++;
      }
    }
    if (G.discardCount[currplayer] != discardBefore+1) {
      printf("--FAIL Discard count wrong\n");
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
    printf("Number of buys incorrect: %d\n", buyerr);
    printf("Total number of times deck was incorrect: %d\n", deckerr);
    printf("Total number of times discard was incorrect: %d\n", discarderr);
    printf("Total number of times other player's hand incorrect: %d\n", otherHerr);
    printf("Total number of times other player's deck incorrect: %d\n", otherDerr);
    printf("Total number of incorrect returns: %d\n", returnerror);
  }

  printf("----------------Council Room Complete------------------\n");

  return 0;
}
