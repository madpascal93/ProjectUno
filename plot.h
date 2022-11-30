#include <stdlib.h>
#include <unistd.h>
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
#define AUSSETZEN "  X  "
#define RICHTUNGSWECHSEL " <-> "
#else
#define CLEAR "clear"
#define AUSSETZEN "  \U000020E0  "
#define RICHTUNGSWECHSEL "  \U000021CC  "
#endif

int test(int a) { return 0;}

int plot_printvalue(char value) {
    char values[13][10] = {"  0  ", "  1  ", "  2  ", "  3  ", "  4  ", "  5  ", "  6  ", "  7  ", "  8  ", "  9  ", AUSSETZEN, RICHTUNGSWECHSEL, "  +2 "};
    if (value & COLOR_BLACKMASK) {
        switch ((value & COLOR_MASK) >> 5) {
            case 1:
                printf((value & RANK_MASK) == 1 ? RED("color") : RED("  +4 "));
                break;
            case 2:
                printf((value & RANK_MASK) == 1 ? GREEN("color") : GREEN("  +4 "));
                break;
            case 3:
                printf((value & RANK_MASK) == 1 ? BLUE("color") : BLUE("  +4 "));
                break;
            case 4:
                printf((value & RANK_MASK) == 1 ? YELLOW("color") : YELLOW("  +4 "));
                break;
            default:
                printf((value & RANK_MASK) == 1 ? "color" : "  +4 ");
        }
    } else {
        switch ((value & COLOR_MASK) >> 5) {
            case 1:
                printf(RED("%s"), values[value & RANK_MASK]);
                break;
            case 2:
                printf(GREEN("%s"), values[value & RANK_MASK]);
                break;
            case 3:
                printf(BLUE("%s"), values[value & RANK_MASK]);
                break;
            case 4:
                printf(YELLOW("%s"), values[value & RANK_MASK]);
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
    sleep(1);
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

int plot_new(card **stacks, int players, int playerturn, int direction) {
    system(CLEAR);
    //Gegner Namen
    for(int i = 1; i < players; i++) {
        printf("\tSpieler %d:", i);    
    }
    printf("\n");

    //Gegner Karten
    for(int i = 0; i < 5; i++) {
        for(int j = 1; j < players; j++) {
            printf("\t");
            for(int k = 0; k < 7; k++) {
                if (i ==2 && (k == 2 || k == 3)) {
                    if (k == 3)
                        printf("%2d", card_count(stacks[j+1]));
                } else {
                    printf("%c", (i % 4) ? ((k % 6) ? ' ' : '|') : ((k % 6) ? '-' : '+'));
                }
            }
            if (j + 1 < players) printf("\t");
        }
        printf("\n");
    }
    printf("\t");
    for(int i = 2; i < playerturn; i++) {
        printf("\t\t");
    }
    printf(playerturn - 1 ? (direction > 0 ? "-> ^ ->\n\n" : "<- ^ <-\n\n") : "\n\n");

    //Ablagestapel und Deck
    printf("\tAblagestapel:\t\tDeck:\n");
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 2; j++) {
            printf("\t");
            for(int k = 0; k < 7; k++) {
                if (i==2 && k%6) {
                    if (k == 1) {
                        if (j) {
                            printf(" %2d  ", card_count(stacks[0]));
                        } else {
                            plot_printvalue(stacks[5]->value);
                        }
                    }
                } else {
                    printf("%c", (i % 4) ? ((k % 6) ? ' ' : '|') : ((k % 6) ? '-' : '+'));
                }
            }
            printf("\t\t");
        }
        printf("\n");  
    }
    printf("\n\n");

    //Spieler Karten
    printf("Deine Karten:\n");
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < card_count(stacks[1]); j++) {
            printf("\t");
            for(int k = 0; k < 7; k++) {
                if (i==2 && k%6) {
                    if (k == 1)
                        plot_printvalue(card_nth(stacks[1], j + 1)->value);
                } else {
                    printf("%c", (i % 4) ? ((k % 6) ? ' ' : '|') : ((k % 6) ? '-' : '+'));
                }
            }
        }
        printf("\n");
    }

    //Karten Nummerierung
    for(int i = 0; i < card_count(stacks[1]); i++) {
        printf("\t  %2d", i+1);
    }
    printf("\n");

    sleep(1);
    return EXIT_SUCCESS;
}

#endif