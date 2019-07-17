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


char *get_hand_type_text(hand_t *hand){
    int hand_id = get_hand_type(hand).type;
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
            strcpy(type, "QUADRO");
            break;


    }

    return type;
}
//TODO: Finish function

Number get_high_number(hand_t *hand){
    Number max = 0;
    int count = hand->filled;
    for (int i = 0; i != count; i++){
        if (hand->cards[i]->num > max) max = hand->cards[i]->num;
    }

    return max;

}

Number *get_pivot(hand_t *hand, HandType type, repeat_t repeaters[], int repeater_count){
    card_t **cards = hand->cards;
	const int size = hand->filled;
	Number *pivot = (Number *) malloc(sizeof(Number) * hand->filled);
    for (int i = 0; i != hand->filled; i++) pivot[i] = 0;
    int tracker = 0;

	switch(type){
        case 0: case 8: case 16:
            sort_hand(hand);
            for (int i = size - 1; i >= 0; i--)
                pivot[i] = cards[i]->num;
            break;
        case 1: case 2: //PAIR AND TWO-PAIR
            for (int i = repeater_count - 1; i >= 0; i--){
                pivot[i] = repeaters[i].card_number;
            }
            break;
        case 4: case 32: case 64:
            for (int rep = 4; rep >= 1; rep--){
                for (int i = 0; i != repeater_count; i++){
                    if (rep == repeaters[i].repeats){
                        pivot[tracker] = repeaters[i].card_number;
                    }
                }
            }
            break;
	}

	return pivot;

}
comparator_t get_hand_type(hand_t *hand){
    comparator_t comparator;
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
		if (cards[i]->suit != suit_track)
            remove_status(FLUSH, &status); //FLUSH CHECKING
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
    for (int j = 0; j <= repeat_track; j++){
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
    //printBin(status);'
    comparator.type = hand_type;
    comparator.pivot = get_pivot(hand, hand_type, repeaters, repeat_track);
    comparator.pivot_count = hand->filled;
    return comparator;

	//check from the top


}

hand_t *get_hand(int size, deck_t *deck){
    hand_t *hand = create_empty_hand(size);
    for (int i = 0; i != size; i++){
        add_to_hand(get_rnd_card(deck), hand);
    }
    return hand;

}

void complete_hand(hand_t *hand, deck_t *deck){
    for (int i = hand->filled; i != hand->count; i++){
        add_to_hand(get_rnd_card(deck), hand);
    }

}

hand_t *create_empty_hand(int size){
    hand_t *empty_hand = (hand_t*) malloc(sizeof(hand_t));
    empty_hand->cards = (card_t**) malloc(sizeof(card_t*) * size);
    empty_hand->count = size;
    empty_hand->filled = 0;
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

int compare_hands(hand_t *a, hand_t *b){
    comparator_t cmp_a = get_hand_type(a);
    comparator_t cmp_b = get_hand_type(b);

    if (cmp_a.type != cmp_b.type) return cmp_a.type - cmp_b.type;
    else {
        for (int i = 0; i != cmp_a.pivot_count; i++){
            if (cmp_a.pivot[i] != cmp_b.pivot[i]) return cmp_a.pivot[i] - cmp_b.pivot[i];
        }
    }

    return 0;
}

int text_card_request(char *request, deck_t *deck, hand_t *dst){
    return request_card_from_deck(text_to_card(request), deck, dst);
}



int request_card_from_deck(card_t card, deck_t *deck, hand_t *dst){
    for (int i = 0; i != deck->filled; i++){
        if (deck->cards[i] != NULL){
            if (card.num == deck->cards[i]->num && card.suit == deck->cards[i]->suit) {
                add_to_hand(get_card(deck, i), dst);
                return 1;
            }
        }
    }

    return 0;

}
