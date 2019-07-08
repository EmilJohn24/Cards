#ifndef HAND_H_INCLUDED
#define HAND_H_INCLUDED
#include "deck.h"
#include "card.h"
#include <stdio.h>
#include <stdlib.h>

typedef int HandType;
//hand types
extern const HandType NORMAL;
extern const HandType PAIR;
extern const HandType TWO_PAIR;
extern const HandType TRIO;
extern const HandType STRAIGHT;
extern const HandType FLUSH;
extern const HandType FULL_HOUSE;
extern const HandType QUADRO;
extern const HandType STRAIGHT_FLUSH; 


typedef struct Hand {
    card_t **cards;
    int count;
    int filled;
} hand_t;

typedef struct Repeat repeat_t;
typedef struct Deck deck_t;
void remove_status(const HandType type, HandType *status);
HandType get_hand_type(hand_t *hand);
hand_t *get_hand(int size, deck_t *deck);
hand_t *create_empty_hand(int size);
void add_to_hand(card_t *card, hand_t *hand);
char *get_hand_text(hand_t* hand);
void sort_hand(hand_t *hand);
#endif // HAND_H_INCLUDED
