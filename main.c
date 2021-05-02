#include <stdio.h>
#include <string.h>

#include "postfix.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define RED(str) ANSI_COLOR_RED str ANSI_COLOR_RESET

int
main(void){
    char input[BUFSIZ];
    char *postfix = NULL;

    fprintf(stderr,
        "itop: convert mathematical expressions in infix format to postfix\n"
        RED("WARNING") "\n"
        "- Multi-character identifier/numbers aren't supported "
        "don't use expressions like \"412 + 231\"\n"
        "- Don't use spaces between operators and operands\n");

    printf("[I]: ");
    while (fgets(input, BUFSIZ, stdin)){
        size_t len = strlen(input) - 1;
        input[len] = 0;
        postfix = infix_to_postfix(input, len);

        printf("[P]: %s\n", postfix);
        printf("[I]: ");
    }
    return 0;
}