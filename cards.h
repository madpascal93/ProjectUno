//defining cards
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef cards_h
#define cards_h

#define COLOR_MASK      0b11100000
#define COLOR_BLACKMASK 0b00010000
#define COLOR_RED       0b00100000
#define COLOR_GREEN     0b01000000
#define COLOR_BLUE      0b01100000
#define COLOR_YELLOW    0b10000000 //64 69
//unsigned char a = 0b10000011;
#define RANK_MASK       0b00001111
#define RANK_ZERO       0b00000000
#define RANK_ONE        0b00000001
#define RANK_TWO        0b00000010
#define RANK_THREE      0b00000011
#define RANK_FOUR       0b00000100
#define RANK_FIVE       0b00000101
#define RANK_SIX        0b00000110
#define RANK_SEVEN      0b00000111
#define RANK_EIGHT      0b00001000
#define RANK_NINE       0b00001001
#define RANK_SKIP       0b00001010 //10 Aussetzen
#define RANK_REVERSE    0b00001011 //11 Richtungswechsel
#define RANK_DRAWTWO    0b00001100 //12 +2
#define RANK_CHANGE     0b00010001 //13 Farbwechsel
#define RANK_DRAWFOUR   0b00010010 //14 +4

struct _card;
typedef struct _card {
    unsigned char value;
    struct _card *prev;
    struct _card *next;
} card;

//typedef struct _card card;
card *card_allocate(void) {
    card *new_card;
    new_card = (card *) malloc(sizeof(card));
    return new_card;
}

card *card_initialize() {
    card *prev_card, *new_card;
    prev_card = card_allocate();
    prev_card->next = NULL;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 25; j++) {
            new_card = card_allocate();
            prev_card->value = (i + 1) << 5 | j % 13 + (j > 12);
            prev_card->prev = new_card;
            new_card->next = prev_card;
            prev_card = new_card;
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            new_card = card_allocate();
            prev_card->value = 1 << 4 | i + 1;
            prev_card->prev = new_card;
            new_card->next = prev_card;
            prev_card = new_card;
        }
    }
    new_card = new_card->next;
    new_card->prev = NULL;
    return new_card;
}

int card_count(card *new_card) {
    if (new_card == NULL)
        return 0;
    /*if (new_card->next == NULL)
        return 1;*/
    return 1 + card_count(new_card->next);
}

card *card_swap(card *first, int n) {
    card *swap_card = card_allocate();
    swap_card = first;
    while (n) {
        swap_card = swap_card->next;
        n--;
    }
    card *helper_card = card_allocate();

    helper_card->value = swap_card->value;
    swap_card->value = first->value;
    first->value = helper_card->value;
    //free(helper_card);
    //free(swap_card);

    return first;
}

int card_shuffle(card *first_card) {
    srand(time(NULL));
    card *nth_card = card_allocate();
    nth_card = first_card;
    while(nth_card->next != NULL) {
        nth_card = card_swap(nth_card, rand() % card_count(nth_card));
        nth_card = nth_card->next;
    }
    return EXIT_SUCCESS;
}

card *card_pop(card *first) {
    if (first->next == NULL)
        return NULL;
    card *new_card = card_allocate();
    new_card = first->next;
    new_card->prev = NULL;
    free(first);
    return new_card;
}

card *card_push(card *first, char value) {
    card *helper_card = card_allocate();
    first->prev = helper_card;
    helper_card->next = first;
    helper_card->prev = NULL;
    helper_card->value = value;
    return helper_card;
}

card *card_nth(card *first, int n) {
    if (n == 1)
        return first;
    return card_nth(first->next, n - 1);
}

int card_sort(card *hand) {
    card *n_card = hand;
    
    while (n_card->next != NULL) {
        if (n_card->value & COLOR_BLACKMASK)
            n_card->value = n_card->value | COLOR_YELLOW;
        int min = 1;
        for(int i = 2; i <= card_count(n_card); i++) {
            if (!(card_nth(n_card, i)->value & COLOR_BLACKMASK)) {
                if (card_nth(n_card, min)->value > card_nth(n_card, i)->value)
                    min = i;
            }
            //printf("%u %u\n", card_nth(n_card, min)->value, card_nth(n_card, i)->value);
            //sleep(1);
        }
        if (n_card->value & COLOR_BLACKMASK)
            n_card->value = n_card->value & (COLOR_BLACKMASK | RANK_MASK);
        n_card = card_swap(n_card, min-1);

        n_card = n_card->next;
    }
    return EXIT_SUCCESS;
}

int card_draw(card **player, card **deck) {
    *player = card_push(*player, (**deck).value);
    *deck = card_pop(*deck);
    //card_sort(*player);
    return EXIT_SUCCESS;
}

card *card_createStack(card **deck) {
    card *player = card_allocate();
    card_draw(&player, deck);
    player->next = NULL;
    return player;
}

int card_lay(card **player, card **stack) {
    *stack = card_push(*stack, (*player)->value);
    printf("%d\n", (*player)->value);
    if ((*player)->prev != NULL) {
        (*player)->prev->next = (*player)->next;
    } 
    if ((*player)->next != NULL)
        (*player)->next->prev = (*player)->prev;
    free(*player);
    
    return EXIT_SUCCESS;
}

int card_compatible(char p_value, char s_value) {
    if (p_value & COLOR_BLACKMASK)
        return s_value & COLOR_BLACKMASK ? 0 : 1;
    if (s_value & COLOR_BLACKMASK)
        return (p_value & COLOR_MASK) ==(s_value & COLOR_MASK);
    return (p_value & COLOR_MASK) == (s_value & COLOR_MASK) || (p_value & RANK_MASK) == (s_value & RANK_MASK);
}

void testprint(card *deck) {
    card *cards = deck;
    do {
        printf("%d\n", cards->value);
        cards = cards->next;
    } while (cards != NULL);
}

#endif