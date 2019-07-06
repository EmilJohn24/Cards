#include "deck.h"
int main(){
    deck_t *deck = generate_std_deck();
    hand_t *my_hand = get_hand(5, deck);

    printf("%s", get_hand_text(my_hand));
    //printf("%s", get_deck_text(deck));
    return 0;
}
