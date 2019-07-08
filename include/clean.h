#ifndef CLEAN_H_INCLUDED
#define CLEAN_H_INCLUDED
#include "deck.h"
#include "card.h"
#include "hand.h"
typedef struct Deck deck_t;
typedef struct Hand hand_t;
typedef struct Card card_t;


int clean_deck(deck_t *deck);
int clean_hand(hand_t *hand);
#endif // CLEAN_H_INCLUDED
