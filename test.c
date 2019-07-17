#include "deck.h"
#include "clean.h"
#include <stdlib.h>
#include <stdio.h>
int test_main(){
    srand(time(NULL));
    for (int i = 0; i != 10000; i++){
        deck_t *deck = generate_std_deck();
        hand_t *my_hand = get_hand(5, deck);
        hand_t *enemy_hand = get_hand(5, deck);
        shuffle_deck(deck, 100);
        //sort_hand((hand_t*)deck);
        //printf("Deck:\n%s\n\n\n", get_deck_text(deck));
        sort_hand(my_hand);
        sort_hand(enemy_hand);
        //printf("My hand: \n%s\n", get_hand_text(my_hand));
        //printf("Hand Type ID: %s\n\n", get_hand_type_text(my_hand));
        //printf("Enemy Hand: \n%s\n", get_hand_text(enemy_hand));
        //printf("Hand Type ID: %s\n\n", get_hand_type_text(enemy_hand));
        //printf("Results: %d\n", compare_hands(my_hand, enemy_hand));
        //printf("---------------------------------\n\n\n");
        //printf("Enemy hand: \n%s\n\n", get_hand_text(enemy_hand));
        clean_hand(my_hand);
        clean_hand(enemy_hand);
        clean_deck(deck);
    //
    }

    char test_card[20];
    scanf("%s", test_card);
    //printf("%s", test_card);
    card_t card = text_to_card(test_card);
    printf("Test Card: %s ", get_card_text(&card));
    return 0;
}
