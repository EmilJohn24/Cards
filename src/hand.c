#include "hand.h"

//hand types
const HandType HIGH_CARD = 0;
const HandType PAIR = 1;
const HandType TWO_PAIR = 2;
const HandType TRIO = 4;
const HandType STRAIGHT = 8;
const HandType FLUSH = 16;
const HandType FULL_HOUSE = 32;
const HandType QUADRO = 64;
const HandType STRAIGHT_FLUSH = FLUSH | STRAIGHT;

void remove_status(const HandType type, HandType *status){
	*status &= ~type;
}

typedef struct Repeat {
	Number card_number;
	int repeats;
} repeat_t;


char *get_hand_type_text(hand_t *hand){
    int hand_id = get_hand_type(hand);
    char *type = (char *) malloc(sizeof(char) * strlen("Straight Flush "));

    switch(hand_id){
        case 0:
            strcpy(type, "HIGH CARD");
            break;
        case 1:
            strcpy(type, "ONE PAIR");
            break;
        case 2:
            strcpy(type, "TWO PAIR");
            break;
        case 4:
            strcpy(type, "TRIO");
            break;
        case 8:
            strcpy(type, "STRAIGHT");
            break;
        case 16:
            strcpy(type, "FLUSH");
            break;
        case 32:
            strcpy(type, "FULL HOUSE");
            break;
        case 64:
            strcpy(type, "STRAIGHT FLUSH");
            break;


    }

    return type;
}
//TODO: Finish function
HandType get_hand_type(hand_t *hand){
	sort_hand(hand);
	card_t **cards = hand->cards;
	const int size = hand->filled;
    register int repeat_track = 0;
	repeat_t repeaters[size];
    repeaters[repeat_track].card_number = cards[0]->num;
    repeaters[repeat_track].repeats = 1;
	const Number straight_track = cards[0]->num;
    const Suit suit_track = cards[0]->suit;
	HandType status = 0xFF;

	for (int i = 1; i != size; i++){
		if (cards[i]->suit != suit_track) remove_status(FLUSH, &status); //FLUSH CHECKING
		if (cards[i]->num == cards[i-1]->num) repeaters[repeat_track].repeats += 1;
		else {
            repeat_track += 1;
            repeaters[repeat_track].repeats = 1;
            repeaters[repeat_track].card_number = cards[i]->num;
        }

		if (cards[i]->num != straight_track + i) remove_status(STRAIGHT, &status);

	}
    HandType exclude = ~(PAIR | TRIO | QUADRO | FULL_HOUSE | TWO_PAIR);
    status = status & exclude;


	int pair_count = 0;
    //this part will only work for 5-card hands
    for (int j = 0; j != repeat_track; j++){
            switch (repeaters[j].repeats){
                case 2:
                    status |= PAIR;
                    pair_count++;
                    break;
                case 3:
                    status |= TRIO;
                    break;
                case 4:
                    status |= QUADRO;
                    break;
        }


    }
        if (pair_count == 2) status |= TWO_PAIR;
        if ((status & (PAIR | TRIO)) == (PAIR | TRIO)) status |= FULL_HOUSE;


    HandType hand_type;
    for (hand_type = QUADRO; hand_type != HIGH_CARD; hand_type >>= 1){
        if ((hand_type & status) > 0) break;

    }
    //printBin(status);

    return hand_type;

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
