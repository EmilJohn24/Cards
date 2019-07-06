#include "card.h"

const Suit CLOVER = 0;
const Suit SPADE = 1;
const Suit HEART = 2;
const Suit DIAMOND = 3;

Number ACE = 14; //may be changed to 1 depending on the game mode
const Number JACK = 11;
const Number QUEEN = 12;
const Number KING  = 13;

int get_sorting_num(const card_t *card){
    return card->num * SUIT_COUNT + card->suit;

}

card_t *new_card(Number num, Suit suit){
    card_t *new_crd = (card_t*) malloc(sizeof(card_t));
    new_crd -> num = num;
    new_crd -> suit = suit;
    new_crd -> curr_holder = NULL;
    return new_crd;

}

char *card_num_to_text(const card_t* card, char *number){
    Number num = card -> num;
    switch(num){
        case _JACK:
            strcpy(number, "JACK");
            break;
        case _QUEEN:
            strcpy(number, "QUEEN");
            break;
        case _KING:
            strcpy(number, "KING");
            break;
        case _ACE:
            strcpy(number, "ACE");
            break;
        default:
            sprintf(number, "%d", card->num);
            break;
    }

    return number;
}

char *card_suit_to_text(const card_t* card, char *suit){
    Suit _suit = card->suit;
    switch(_suit){
            case _CLOVER:
                strcpy(suit, "CLOVER");
                break;
            case _SPADE:
                strcpy(suit, "SPADE");
                break;
            case _HEART:
                strcpy(suit, "HEART");
                break;
            case _DIAMOND:
                strcpy(suit, "DIAMOND");
                break;
        }

    return suit;

}
char *get_card_text(const card_t *card){
    char *text = (char*) malloc(sizeof(char) * 30);
    char *number = (char*) malloc(sizeof(char) * 10);
    char *suit = (char*) malloc(sizeof(char) * 10);

    card_num_to_text(card, number);
    card_suit_to_text(card, suit);
    sprintf(text, "%s-%s", number, suit);
    free(number);
    free(suit);
    return text;


}
