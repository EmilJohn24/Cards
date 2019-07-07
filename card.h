#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#define SUIT_COUNT 4
typedef unsigned char Suit;
typedef int Number;

extern const Suit CLOVER;
extern const Suit SPADE;
extern const Suit HEART;
extern const Suit DIAMOND;


#define _CLOVER 0
#define _SPADE 1
#define _HEART 2
#define _DIAMOND 3

extern Number ACE; //may be changed to 1 depending on the game mode
extern const Number JACK;
extern const Number QUEEN;
extern const Number KING;

#define _JACK 11
#define _QUEEN 12
#define _KING 13
#define _ACE 14
typedef struct Hand hand_t;

typedef struct Card{
    Suit suit;
    Number num;
    hand_t *curr_holder;
} card_t;




int get_sorting_num(const card_t *card);
int compare_cards(const void *a, const void *b);
card_t *new_card(Number num, Suit suit);
char *get_card_text(const card_t *card);
char *card_num_to_text(const card_t* card, char *number);
char *card_suit_to_text(const card_t* card, char *suit);
#endif // CARD_H_INCLUDED
