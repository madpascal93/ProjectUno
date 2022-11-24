#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "game.h"
#include "plot.h"

//defining color outputs for terminal
/*#define ANSI_COLOR_RED     "\x1b[41m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define RED(string) ANSI_COLOR_RED string ANSI_COLOR_RESET
#define GREEN(string) ANSI_COLOR_GREEN "\x1b[41m" string ANSI_COLOR_RESET
#define YELLOW(string) ANSI_COLOR_YELLOW string ANSI_COLOR_RESET
#define BLUE(string) ANSI_COLOR_CYAN string ANSI_COLOR_RESET*/


int main() {
    //printf(GREEN("P")RED("E")YELLOW("N")BLUE("I")GREEN("S\n"));
    //printf("%d", (3 << 5 | 3 % 13 + (3 > 12)) == (COLOR_GREEN | RANK_THREE));
    //card *a = card_initialize();
    //card *b = card_initialize();
    //card_swap(a->next->next->next->next, 4);
    //card_shuffle(a);
    //a = card_pop(a);
    //card_draw(&a, &b);
    //a = card_push(a, 5);
    //b = card_createStack(&a);
    //card_draw(&b, &a);
    /*testprint(a);
    b = card_nth(a, 5);
    printf("\n%d", b->value);
    //testprint(b);
    printf("\n%d\n", card_count(a));*/
    game_menu();
    return EXIT_SUCCESS;
}