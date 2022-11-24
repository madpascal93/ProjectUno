#include <stdlib.h>
#include "cards.h"


#ifndef plot_h
#define plot_h

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define RED(string) ANSI_COLOR_RED string ANSI_COLOR_RESET
#define GREEN(string) ANSI_COLOR_GREEN string ANSI_COLOR_RESET
#define YELLOW(string) ANSI_COLOR_YELLOW string ANSI_COLOR_RESET
#define BLUE(string) ANSI_COLOR_CYAN string ANSI_COLOR_RESET

#ifdef WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

int test(int a) { return 0;}

int plot_printvalue(char value) {
    char values[13][10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "\U000020E0", "\U000021CC", "+2"};
    if (value & COLOR_BLACKMASK) {
        switch ((value & COLOR_MASK) >> 5) {
            case 1:
                printf((value & RANK_MASK) == 1 ? RED("change\t") : RED("+4"));
                break;
            case 2:
                printf((value & RANK_MASK) == 1 ? GREEN("change\t") : GREEN("+4"));
                break;
            case 3:
                printf((value & RANK_MASK) == 1 ? BLUE("change\t") : BLUE("+4"));
                break;
            case 4:
                printf((value & RANK_MASK) == 1 ? YELLOW("change\t") : YELLOW("+4"));
                break;
            default:
                printf((value & RANK_MASK) == 1 ? "change\t" : "+4\t");
        }
    } else {
        switch ((value & COLOR_MASK) >> 5) {
            case 1:
                printf(RED("%s\t"), values[value & RANK_MASK]);
                break;
            case 2:
                printf(GREEN("%s\t"), values[value & RANK_MASK]);
                break;
            case 3:
                printf(BLUE("%s\t"), values[value & RANK_MASK]);
                break;
            case 4:
                printf(YELLOW("%s\t"), values[value & RANK_MASK]);
                break;
            default:
                printf((value & RANK_MASK) == 1 ? "change\t" : "+4\t");
        }
    }
    return EXIT_SUCCESS;
}

int plot_hand(card *player) {
    while (player != NULL) {
        plot_printvalue(player->value);
        player = player->next;
    }
    return EXIT_SUCCESS;
}

int plot(card **stacks) {
    //system(CLEAR);
    printf("%d\n", card_count(stacks[0]));
    printf("Ablagestapel: %d, ", card_count(stacks[5]));
    plot_printvalue(stacks[5]->value);
    printf("\n");
    plot_hand(stacks[1]);
    printf("\n");
    plot_hand(stacks[2]);
    printf("\n");
    plot_hand(stacks[3]);
    printf("\n");
    plot_hand(stacks[4]);
    printf("\n");
    /*printf("\U000021CC");
    printf("\U000020E0");*/
    return EXIT_SUCCESS;
}

#endif