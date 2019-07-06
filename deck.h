#ifndef DECK_H_INCLUDED
#define DECK_H_INCLUDED
#include "card.h"
#include "hand.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define STD_DECK_SIZE 52

typedef struct Deck{
    card_t **cards;
    int count;
    int filled;
} deck_t;

struct Card;
typedef struct Card card_t;
deck_t *generate_std_deck(); //returns a standard 52-card deck
deck_t *generate_clean_deck(int slots);
card_t *get_rnd_card(deck_t *deck); //picks a random card from the deck
card_t *get_card(deck_t *deck, int index); //safe card getter (does null checking)
int push_card(card_t *card, deck_t *deck);
bool is_full(deck_t *deck);
char *get_deck_text(deck_t *deck);

#endif // DECK_H_INCLUDED
