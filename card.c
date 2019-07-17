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
    return (card->num * SUIT_COUNT) + card->suit;

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
    char *number = (char*) malloc(sizeof(char) * 30);
    char *suit = (char*) malloc(sizeof(char) * 30);
    card_num_to_text(card, number);
    card_suit_to_text(card, suit);
    sprintf(text, "%s-%s", number, suit);
    return text;
}

int compare_cards(const void *a, const void *b){
    const card_t *card_a = *(card_t**)a;
    const card_t *card_b = *(card_t**)b;
    if (card_a == NULL) return 1;
    if (card_b == NULL) return -1;

    return get_sorting_num(card_a) - get_sorting_num(card_b);
}

card_t text_to_card(const char *str){
    char *number_txt = (char*) malloc(sizeof(char) * 5);
    char *suit_txt = (char*) malloc(sizeof(char) * 5);
    card_t card;
    char separator = '-';
    int i = 0;
    char check;
    for(; check != separator; i++){
        check = str[i];
        if (str[i] == '\0') return card;
        //printf("%s", number_txt);
        //printf("%c", str[i]);
        number_txt[i] = str[i];
    }
    number_txt[i-1] = '\0';
    int num_len = i;
    //printf("====%s", number_txt);
    if (strcmp(number_txt, "JACK") == 0) card.num = _JACK;
    else if (strcmp(number_txt, "QUEEN") == 0) card.num = _QUEEN;
    else if (strcmp(number_txt, "KING") == 0) card.num = _KING;
    else if (strcmp(number_txt, "ACE") == 0) card.num = _ACE;
    else sscanf(number_txt, "%d", &(card.num));

    while(str[i] != '\0') {
        suit_txt[i-num_len] = str[i];
        i++;
    }
    //printf("%s", suit_txt);
    if (strcmp(suit_txt, "SPADE") == 0) card.suit = _SPADE;
    else if (strcmp(suit_txt, "DIAMOND") == 0) card.suit = _DIAMOND;
    else if (strcmp(suit_txt, "HEART") == 0) card.suit = _HEART;
    else if (strcmp(suit_txt, "CLOVER") == 0) card.suit = _CLOVER;
    else return card;
    return card;











}
