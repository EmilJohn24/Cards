#include "display.h"

void init(){
    Deck = generate_std_deck();
    shuffle_deck(Deck, 1000);
    Player = get_hand(5, Deck);
    Enemy = get_hand(5, Deck);
}

void println(const char* s){
    printf("%s\n", s);
}

void print_deck(){
    printf("\nDeck: \n%s", get_deck_text(Deck));
}

void regenerate(){
    init();
}

void custom_card(){
    init();
    Player = create_empty_hand(5);
    Enemy = create_empty_hand(5);
    char card_name[20];
    printf("Type LAST if you are done.\n");
    printf("Player Hand: ");
    while (Player->filled != Player->count){
        scanf("%s", card_name);
        if(strcmp(card_name, "LAST") == 0) break;
        if(text_card_request(card_name, Deck, Player) == 0){
            printf("Card is already in use\n");

        };
    }

    printf("Enemy hand: ");
    card_name[0] = 'A'; //reset
    while (Enemy->filled != Enemy->count){
        scanf("%s", card_name);
        if(strcmp(card_name, "LAST") == 0) break;
        if(text_card_request(card_name, Deck, Enemy) == 0){
            printf("Card is already in use\n");

        };
    }
}


void generate_from_incomplete(){
    custom_card();
    complete_hand(Player, Deck);
    complete_hand(Enemy, Deck);
}

void identify_hands(){
    printf("My hand: \n%s\n", get_hand_text(Player));
    printf("Hand Type ID: %s\n\n", get_hand_type_text(Player));
    printf("Enemy Hand: \n%s\n", get_hand_text(Enemy));
    printf("Hand Type ID: %s\n\n", get_hand_type_text(Enemy));

}

void compare_hand_display(){
    identify_hands();
    if (compare_hands(Player, Enemy) > 0)
        printf("Results: %s\n", "Player wins.\n");
    else printf("Results: %s\n", "Enemy wins.\n");

}

void sort_deck(){
    sort_hand((hand_t*)Deck);
    print_deck();
}

void sort_hands(){
    sort_hand(Player);
    sort_hand(Enemy);
}

void simulator(){
    int trials;
    printf("How many games would you like to simulate? \n");
    scanf("%d", &trials);
    for (int i = 0; i != trials; i++){
        init();
        print_deck();
        compare_hand_display();

    }


}
void main_menu(){
    int choice = -1;
    printf("\n---------------------------------\nHand #1: \n %s", get_hand_text(Player));
    printf("\nHand #2: \n %s", get_hand_text(Enemy));
    printf("Some guidelines: \n");
    printf("** To specify special cards, type ACE, KING, QUEEN, and JACK\n");
    println("** Type numbers in number form (e.g. 1, 2, 3)");
    println("** To specify the suit, use the following keywords: DIAMOND, HEART,SPADE, and CLOVER");
    println("** Always type in capital letters");
    println("** To specify a card, use the following format: NUMBER-SUIT without spaces (example: 4-HEART, ACE-SPADE\n\n\n");

    println("Pick one of the following options");
    println("\t 0. Print the randomly generated deck");
    println("\t 1. Regenerate the hands randomly");
    println("\t 2. Customize two hands (autocompleted randomly if incomplete)");
    println("\t 3. Compare the strength of two hands");
    println("\t 4. Identify the type of the hands");
    println("\t 5. Sort the deck");
    println("\t 6. Sort the hands");
    println("\t 7. Simulate games");
    println("\t 8. Exit");
    while (choice < 0 || choice > 7) {
        printf("\nTake your pick: \n");
        scanf("%d", &choice);
    }

    switch(choice){
        case 0:
            print_deck();
            break;
        case 1:
            regenerate();
            break;
        case 2:
            generate_from_incomplete();
            break;
        case 3:
            compare_hand_display();
            break;
        case 4:
            identify_hands();
            break;
        case 5:
            sort_deck();
            break;
        case 6:
            sort_hands();
            break;
        case 7:
            simulator();
            break;
        case 8:
            clean_deck(Deck);
            clean_hand(Enemy);
            clean_hand(Player);
            exit(0);
    }
    fflush(stdin);
    printf("Click ENTER to continue...\n");
    getchar();
    main_menu();


}

int main(){
    init();
    main_menu();

}
