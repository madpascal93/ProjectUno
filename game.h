#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "plot.h"
#ifndef game_h
#define game_h


#define MAX_PLAYERS 4

card *stacks[6];

int game_start() {
    system(CLEAR);
    printf("Spieler Anzahl: ");
    int players;
    scanf("%d", &players);
    card *deck = card_initialize();
    card_shuffle(deck);
    //deck = card_initialize();
    stacks[0] = deck;
    for (int i = 1; i < 5; i++) {
        //deck = card_allocate();
        stacks[i] = i <= players ? card_createStack(&stacks[0]) : NULL;
        //stacks[i] = deck;
    }
    //deck = card_allocate();
    stacks[5] = card_createStack(&stacks[0]);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < players; j++) {
            card_draw(&stacks[j + 1], &stacks[0]);
        }
    }
    return players;
}

int game_PlayerChooseColor(card **stack) {
    printf("Wähle eine Farbe (" RED("1") ", " GREEN("2") ", " BLUE("3") ", " YELLOW("4") " : ");
    int input;
    scanf("%d", &input);
    (*stack)->value = (input << 5) | ((*stack)->value & RANK_MASK) | COLOR_BLACKMASK;  
    return EXIT_SUCCESS; 
}

int game_ComputerChooseColor(card *player, card **stack) {
    int color[4] = {0, 0, 0, 0};
    while (player != NULL) {
        if (!(player->value & COLOR_BLACKMASK))
            color[((player->value & COLOR_MASK) >> 5) - 1] += 1;
        player = player->next;
    }
    int max = 0;
    for (int i = 0; i < 4; i++) {
        if (color[i] > color[max])
            max = i;
    }
    (*stack)->value = ((max + 1) << 5) | ((*stack)->value & RANK_MASK) | COLOR_BLACKMASK;
    return EXIT_SUCCESS;
}

int game_computermove(card **player, card **stack) {
    card *hand = card_allocate();
    hand = *player;
    do {
        if (card_compatible(hand->value, (*stack)->value)) {
            if (hand == *player) {
                *stack = card_push(*stack, (*player)->value);
                *player = (card_pop(*player));
            } else {
                card_lay(&hand, stack);
            }
            /*if ((*stack)->value & COLOR_BLACKMASK)
                game_ComputerChooseColor(*player, stack);*/
            break;
        }
        hand = hand->next;
    } while (hand != NULL);
    if (hand == NULL)
        card_draw(player, &stacks[0]);
    return EXIT_SUCCESS;
}

int game_playermove(card **player, card**stack) {
    printf("was willst du tun");
    int input;
    scanf("\n%d", &input);
    if (!input) {
        card_draw(player, &stacks[0]);
    } else {
        if (card_compatible((card_nth(*player, input))->value, (*stack)->value)) {
            card *moveCard = card_nth(*player, input);
            //printf("%d\n", moveCard->value);
            if (input == 1) {
                *stack = card_push(*stack, (*player)->value);
                *player = (card_pop(*player));
            } else {
                card_lay(&moveCard, stack);
            }
            /*if ((*stack)->value & COLOR_BLACKMASK)
                game_PlayerChooseColor(stack);*/
        } else {
            printf("Move not possible!\n");
            game_playermove(player, stack);
        }
    }
    return EXIT_SUCCESS;
}

int game_computermoveDrawTwo(card **player, card **stack) {
    card *hand = card_allocate();
    hand = *player;
    do {
        if (card_compatible(hand->value, RANK_DRAWTWO)) {
            if (hand == *player) {
                *stack = card_push(*stack, (*player)->value);
                *player = (card_pop(*player));
                return 1;
            } else {
                card_lay(&hand, stack);
                return 1;
            }
            break;
        }
        hand = hand->next;
    } while (hand != NULL);
    return 0;
}

int game_playermoveDrawTwo(card **player, card**stack) {
    printf("was willst du tun");
    int input;
    scanf("\n%d", &input);
    if (!input) {
        return 0;
    } else {
        if (card_compatible((card_nth(*player, input))->value, RANK_DRAWTWO)) {
            card *moveCard = card_nth(*player, input);
            if (input == 1) {
                *stack = card_push(*stack, (*player)->value);
                *player = (card_pop(*player));
            } else {
                card_lay(&moveCard, stack);
            }
        } else {
            printf("Move not possible, lay a +2 or enter '0' to draw cards!\n");
            return game_playermoveDrawTwo(player, stack);
        }
    }
    return 1;
}

int game_won(card *stack) {
    return stack == NULL;
}

int game_drawTwo(int order, int direction) {
    int drawCards = 2;
    while (1) {
        plot(stacks);
        order = order % MAX_PLAYERS + direction + (order % MAX_PLAYERS <= 1 && direction < 0 ? 4 : 0);
        int count_pre = card_count(stacks[5]);
        if (order == 1) {
            if (game_playermoveDrawTwo(&stacks[order], &stacks[5])) {
                drawCards += 2;
            } else {
                for (int i = 0; i < drawCards; i++) {
                    card_draw(&stacks[order], &stacks[0]);
                    if (stacks[0]->next == NULL) {
                        stacks[0]->next = stacks[5]->next;
                        stacks[5]->next = NULL;
                        card_shuffle(stacks[0]->next);
                    }
                }
                return order;
            }
        } else {
            if (!game_won(stacks[order])) {
                if (game_computermoveDrawTwo(&stacks[order], &stacks[5])) {
                    drawCards += 2;
                } else {
                    for (int i = 0; i < drawCards; i++) {
                        card_draw(&stacks[order], &stacks[0]);
                        if (stacks[0]->next == NULL) {
                            stacks[0]->next = stacks[5]->next;
                            stacks[5]->next = NULL;
                            card_shuffle(stacks[0]->next);
                        }
                    }
                    return order;
                }
            }
        }
    }
}

int game_menu() {
    int players = game_start();
    //plot(stacks);

    int order = 0;
    int direction = 1;
    while (stacks[1] != NULL) {
        plot(stacks);
        order = order % MAX_PLAYERS + direction + (order % MAX_PLAYERS <= 1 && direction < 0 ? 4 : 0);
        int count_pre = card_count(stacks[5]);
        if (order == 1) {
            game_playermove(&stacks[order], &stacks[5]);
        } else {
            if (!game_won(stacks[order]))
                game_computermove(&stacks[order], &stacks[5]);
                //if (stacks[5]->value & COLOR_BLACKMASK)
                  //  game_ComputerChooseColor(stacks[order], &stacks[5]);
        }
        /*if (stacks[5]->value & COLOR_BLACKMASK) {
            if (order == 1) {
                game_PlayerChooseColor(&stacks[5]);
            } else {
                game_ComputerChooseColor(stacks[order], &stacks[5]);
            }
        }*/
        if (card_count(stacks[5]) > count_pre) {
            if (stacks[5]->value & COLOR_BLACKMASK) {
                order == 1 ? game_PlayerChooseColor(&stacks[5]) : game_ComputerChooseColor(stacks[order], &stacks[5]);
                if ((stacks[5]->value & (RANK_MASK | COLOR_BLACKMASK)) == RANK_DRAWFOUR) {
                    for (int i = 0; i < 4; i++) {
                        printf("++\n");
                        while (stacks[order % MAX_PLAYERS + direction + (order % MAX_PLAYERS <= 1 && direction < 0 ? 4 : 0)] == NULL)
                            order = order % MAX_PLAYERS + direction + (order % MAX_PLAYERS <= 1 && direction < 0 ? 4 : 0);
                        card_draw(&stacks[order % MAX_PLAYERS + direction + (order % MAX_PLAYERS <= 1 && direction < 0 ? 4 : 0)], &stacks[0]);
                        if (stacks[0]->next == NULL) {
                            stacks[0]->next = stacks[5]->next;
                            stacks[5]->next = NULL;
                            card_shuffle(stacks[0]->next);
                        }
                    }
                    order = order % MAX_PLAYERS + direction + (order % MAX_PLAYERS <= 1 && direction < 0 ? 4 : 0);
                }
            } else {
                if ((stacks[5]->value & RANK_MASK) > 9) {
                    switch (stacks[5]->value & RANK_MASK) {
                        case 10:
                            order = order % MAX_PLAYERS + direction + (order % MAX_PLAYERS <= 1 && direction < 0 ? 4 : 0);
                            break;
                        case 11:
                            direction *= -1;
                            break;
                        case 12:
                            order = game_drawTwo(order, direction);
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        if (stacks[0]->next == NULL) {
            stacks[0]->next = stacks[5]->next;
            stacks[5]->next = NULL;
            card_shuffle(stacks[0]->next);
        }
    }
    printf("Herzlichen Glückwunsch, du hast gewonnen.\n");
        return EXIT_SUCCESS;
}

#endif