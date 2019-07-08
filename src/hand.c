#include "hand.h"


hand_t *get_hand(int size, deck_t *deck){
    hand_t *hand = create_empty_hand(size);
    for (int i = 0; i != size; i++){
        add_to_hand(get_rnd_card(deck), hand);
    }
    return hand;

}

hand_t *create_empty_hand(int size){
    hand_t *empty_hand = (hand_t*) malloc(sizeof(hand_t));
    empty_hand->cards = (card_t**) malloc(sizeof(card_t*) * size);
    for (int i = 0; i != size; i++)
        empty_hand->cards[i] = (card_t*) malloc(sizeof(card_t));
    return empty_hand;

}


void add_to_hand(card_t *card, hand_t *hand){
    hand->cards[hand->filled] = card;
    card->curr_holder = hand;
    hand->filled++;

}

//returns text version of all the cards in the hand separated by new lines
char *get_hand_text(hand_t* hand){
    char *text = (char *) malloc(sizeof(char) * 100);
    *text = '\0';
    int size = hand->filled;
    for (int i = 0; i != size; i++){
        if (hand->cards[i] == NULL) continue;
        strcat(text, get_card_text(hand->cards[i]));
        strcat(text, "\n");
    }

    return text;
}

void sort_hand(hand_t *hand){
    qsort(hand->cards, hand->filled, sizeof(hand_t*), compare_cards);
}
