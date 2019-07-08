#include "hand.h"

//hand types
const HandType NORMAL = 0;
const HandType PAIR = 1;
const HandType TWO_PAIR = 2;
const HandType TRIO = 4;
const HandType STRAIGHT = 8;
const HandType FLUSH = 16;
const HandType FULL_HOUSE = 32;
const HandType QUADRO = 64;
const HandType STRAIGHT_FLUSH = FLUSH | STRAIGHT; 

void remove_status(const HandType type, HandType *status){
	*status |= ~type;
}

typedef struct Repeat {
	Number card_number;
	int repeats;
} repeat_t;


//TODO: Finish function
HandType get_hand_type(hand_t *hand){
	sort_hand(hand);
	card_t **cards = hand->cards;
	const int size = hand->filled;
	repeat_t repeaters[size];
	register repeat_track = 0;
	register const Number straight_track = cards[0]->num;
	register const Suit suit_track = cards[0]->suit;
	HandType status = 0xFF;
	for (int i = 0; i != size; i++){
		if (cards[i]->suit != suit_track) remove_status(FLUSH, &status); //FLUSH CHECKING
		if (i != 0 && cards[i]->num == cards[i-1]->num) repeater[repeat_track].repeats += 1;
		if (i != 0 && cards[i]->num != cards[i-1]->num) repeat_track += 1;
		if (cards[i]->num != straight_track + i) remove_status(STRAIGHT, &status);
	}
	
	return status;
	//check from the top
	
	
}

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
