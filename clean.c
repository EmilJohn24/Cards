#include "clean.h"

int clean_deck(deck_t *deck){
    int count = deck->count;
    for (int i = 0; i != count; i++){
        free(deck->cards[i]);
    }
    free(deck->cards);
    free(deck);
    return 0;
}

int clean_hand(hand_t *hand){
    deck_t *hand_deck = (deck_t*) hand;
    clean_deck(hand_deck);
    return 0;
}
