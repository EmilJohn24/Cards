#ifndef HAND_H_INCLUDED
#define HAND_H_INCLUDED
#include "deck.h"
#include "card.h"
#include <stdio.h>
typedef struct Hand {
    card_t **cards;
    int count;
    int filled;
} hand_t;

typedef struct Deck deck_t;
hand_t *get_hand(int size, deck_t *deck);
hand_t *create_empty_hand(int size);
void add_to_hand(card_t *card, hand_t *hand);
char *get_hand_text(hand_t* hand);
#endif // HAND_H_INCLUDED
