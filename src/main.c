#include "vm.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    const char *source = "if (6 + 7 == 67) number = 67; else number = 0; //fajny kod";
    Token *tokens = lex(source);
    print_tokens(tokens, source);
    free(tokens);
    return 0;
}