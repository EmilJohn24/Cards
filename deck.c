#include "deck.h"



deck_t *generate_clean_deck(int slots){
    deck_t *new_deck = (deck_t *) malloc(sizeof(deck_t));
    new_deck -> cards = (card_t **) malloc(sizeof(card_t*) * slots);
    for (int i = 0; i != slots; i++)
        new_deck -> cards[i] = (card_t *) malloc(sizeof(card_t));
    new_deck -> count = slots;
    new_deck -> filled = 0;
    return new_deck;
}


deck_t *generate_std_deck(){
    deck_t *std_deck = generate_clean_deck(STD_DECK_SIZE);
    for (Number num = 2; num <= KING; num++){
        for (Suit suit = CLOVER; suit <= DIAMOND; suit++){
            if (push_card(new_card(num, suit), std_deck) == -1) break;
        }
    }

    for (Suit suit = CLOVER; suit <= DIAMOND; suit++)
        if (push_card(new_card(ACE, suit), std_deck) == -1) break;

    return std_deck;

} //returns a standard 52-card deck
bool is_full(deck_t *deck){
    return deck->count == deck->filled;
}

card_t *get_rnd_card(deck_t *deck){
    register int size = deck -> count;
    register int index = rand() % size;
    card_t *card;
    while ((card = get_card(deck, index)) == NULL){
        index = rand() % size;
    }

    return card;
} //picks a random card from the deck
card_t *get_card(deck_t *deck, int index){
    card_t *temp = deck -> cards[index];
    if (index < deck -> count){
        deck -> cards[index] = NULL;
        return temp;
    }
    else return NULL;

} //safe card getter (empties deck slot after taking the card)

int push_card(card_t *card, deck_t *deck){
    if (is_full(deck)) return -1;
    deck->cards[deck->filled] = card;
    deck->filled += 1;
    return 1;
}

char *get_deck_text(deck_t *deck){
    hand_t *deck_hand = (hand_t*) deck;
    return get_hand_text(deck_hand);

}
void swap_cards(deck_t *deck, int first, int second){
    card_t *tmp;
    tmp = deck->cards[first];
    deck->cards[first] = deck->cards[second];
    deck->cards[second] = tmp;

}
void shuffle_deck(deck_t *deck, int swaps){
    int size = deck->filled;
    int first, second;
    for (int i = 0; i != swaps; i++){
        first = rand() % size;
        second = rand() % size;
        swap_cards(deck, first, second);
    }


}


