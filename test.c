#include "deck.h"
#include "clean.h"
int main(){
    deck_t *deck = generate_std_deck();
    hand_t *my_hand = get_hand(10, deck);
    hand_t *enemy_hand = get_hand(10, deck);
    printf("My hand: \n%s\n", get_hand_text(my_hand));
    printf("Enemy hand: \n%s", get_hand_text(enemy_hand));
    clean_hand(my_hand);
    clean_hand(enemy_hand);
    clean_deck(deck);
    //printf("%s", get_deck_text(deck));
    return 0;
}
