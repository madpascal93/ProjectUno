#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define RED(string) ANSI_COLOR_RED string ANSI_COLOR_RESET
#define GREEN(string) ANSI_COLOR_GREEN string ANSI_COLOR_RESET
#define YELLOW(string) ANSI_COLOR_YELLOW string ANSI_COLOR_RESET
#define BLUE(string) ANSI_COLOR_CYAN string ANSI_COLOR_RESET


int main() {
    printf(GREEN("P")RED("E")YELLOW("N")BLUE("I")GREEN("S\n"));
    return EXIT_SUCCESS;
}