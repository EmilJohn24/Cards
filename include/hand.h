#ifndef HAND_H_INCLUDED
#define HAND_H_INCLUDED
#include "deck.h"
#include "card.h"
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char HandType;
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

typedef struct Repeat {
       Number card_number;
       int repeats;
} repeat_t;

typedef struct Comparator {
    HandType type;
    Suit suit;
    Number* pivot;
    int pivot_count;
} comparator_t;


typedef struct Deck deck_t;
char *get_hand_type_text(hand_t *hand);
void remove_status(const HandType type, HandType *status);
comparator_t get_hand_type(hand_t *hand);
hand_t *get_hand(int size, deck_t *deck);
hand_t *create_empty_hand(int size);
void add_to_hand(card_t *card, hand_t *hand);
char *get_hand_text(hand_t* hand);
void sort_hand(hand_t *hand);
Number get_high_number(hand_t *hand);
Number *get_pivot(hand_t *hand, HandType type, repeat_t repeaters[], int repeater_count);
#endif // HAND_H_INCLUDED
